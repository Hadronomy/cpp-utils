#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <thread>

#include "info.h"

namespace utils {

#ifndef UTILS_INSTRUMENTOR
#define UTILS_INSTRUMENTOR utils::ChromeInstrumentor
#endif

#ifdef  UTILS_PROFILE
#define UTILS_PROFILE_BEGIN_SESSION(name, filepath) UTILS_INSTRUMENTOR::Get().BeginSession(name, filepath)
#define UTILS_PROFILE_END_SESSION() UTILS_INSTRUMENTOR::Get().EndSession()
#define UTILS_PROFILE_SCOPE(name) utils::InstrumentationTimer timer##__LINE__(name)
#define UTILS_PROFILE_FUNCTION() UTILS_PROFILE_SCOPE(UTILS_FUNCSIG)
#else
#define UTILS_PROFILE_BEGIN_SESSION()
#define UTILS_PROFILE_END_SESSION()
#define UTILS_PROFILE_SCOPE(name)
#define UTILS_PROFILE_FUNCTION()
#endif

/**
 * Stores the resulting information of a profile
 */
struct ProfileResult {
  std::string name;
  long long start, end;
  uint32_t threadID;
};

/**
 * Stores the name of the InstrumentationSession
 */
struct InstrumentationSession {
  std::string name;
};

/**
 * Base class for implementing Intrumentors.
 * This class doesn't implement virtual functions to avoid performance overhead.
 * You can inherit from it normally, but take into account that to "implement"
 * functions you will have to overshadow them.
 * @tparam TInstrumentator The type of the inheriting class
 */
template<typename TInstrumentator>
class BaseInstrumentor {
 public:
  BaseInstrumentor() : current_session_(nullptr), output_stream_(), profile_count_(0) {
    AssertIsInheritor();
  }

  /**
   * Begins a new instrumentation session
   * @param name The name of the session
   * @param file_path File where to save the session profile
   */
  void BeginSession(const std::string &name, const std::string &file_path);

  /**
   * Ends the current instrumentation session
   */
  void EndSession();

  /**
   * VIRTUAL
   * Writes the header of the profile session file
   */
  inline void WriteHeader() { GetDerivedPointer()->WriteHeader(); }

  /**
   * VIRTUAL
   * Writes a new profile to the profile session file
   * @param result The profile to write
   */
  inline void WriteProfile(const ProfileResult& result) { GetDerivedPointer()->WriteProfile(result); }

  /**
   * VIRTUAL
   * Writes the footer of the profile session file
   */
  inline void WriteFooter() { GetDerivedPointer()->WriteFooter(); }

  /**
   * Gets the current instance of the Instrumentor
   * @return
   */
  static TInstrumentator& Get() {
    static TInstrumentator instance;
    return instance;
  }

 protected:
  InstrumentationSession *current_session_;
  std::ofstream output_stream_;
  int profile_count_;

 private:
  constexpr void AssertIsInheritor() {
    static_assert(std::is_base_of<BaseInstrumentor, TInstrumentator>::value,
                  "Invalid TInstrumentator, the type is not child of the BaseInstrumentor class");
  }

  constexpr TInstrumentator* GetDerivedPointer() {
    return static_cast<TInstrumentator*>(this);
  }
};

template<typename TInstrumentator>
inline void BaseInstrumentor<TInstrumentator>::BeginSession(const std::string &name, const std::string &file_path) {
  output_stream_.open(file_path);
  WriteHeader();
  current_session_ = new InstrumentationSession{name};
}

template<typename TInstrumentator>
inline void BaseInstrumentor<TInstrumentator>::EndSession() {
  WriteFooter();
  output_stream_.close();
  delete current_session_;
  current_session_ = nullptr;
  profile_count_ = 0;
}

/**
 * Profiles in a chrome://tracing compatible format
 */
class ChromeInstrumentor : public BaseInstrumentor<ChromeInstrumentor> {
 public:
  ChromeInstrumentor() : BaseInstrumentor<ChromeInstrumentor>() {}

  void WriteHeader();
  void WriteProfile(const ProfileResult& result);
  void WriteFooter();
};

inline void ChromeInstrumentor::WriteHeader() {
  output_stream_ << R"({"otherData": {},"traceEvents":[)";
  output_stream_.flush();
}

inline void ChromeInstrumentor::WriteProfile(const ProfileResult& result) {
  if (profile_count_++ > 0)
    output_stream_ << ",";

  std::string name = result.name;
  std::replace(name.begin(), name.end(), '"', '\'');

  output_stream_ << "{";
  output_stream_ << R"("cat":"function",)";
  output_stream_ << R"("dur":)" << (result.end - result.start) << ',';
  output_stream_ << R"("name":")" << name << "\",";
  output_stream_ << R"("ph":"X",)";
  output_stream_ << R"("pid":0,)";
  output_stream_ << R"("tid":)" << result.threadID << ",";
  output_stream_ << R"("ts":)" << result.start;
  output_stream_ << "}";
  output_stream_.flush();
}

inline void ChromeInstrumentor::WriteFooter() {
  output_stream_ << "]}";
  output_stream_.flush();
}

/**
 * Times a scope and sends the profile to the Instrumentor
 */
class InstrumentationTimer {
 public:
  explicit InstrumentationTimer(const char* name) : name_(name), stopped_(false) {
    start_timepoint_ = Clock::now();
  }
  ~InstrumentationTimer() {
    if (!stopped_)
      Stop();
  }

  void Stop();

 private:
  using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
  using Clock = std::chrono::high_resolution_clock;

  const char* name_;
  bool stopped_;
  TimePoint start_timepoint_;
};

inline void InstrumentationTimer::Stop() {
  TimePoint end_timepoint = Clock::now();
  long long start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint_).time_since_epoch().count();
  long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

  uint32_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
  UTILS_INSTRUMENTOR::Get().WriteProfile({name_, start, end, thread_id});
  stopped_ = true;
}


}

#pragma clang diagnostic pop
