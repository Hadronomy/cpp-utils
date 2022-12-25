#include <thread>
#include <chrono>

#include <gtest/gtest.h>
#include <utils/hourglass.h>

TEST(Hourglass, ReportsMilliseconds) {
  toffee::Hourglass::Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(123));
  auto time = toffee::Hourglass::Stop();
  EXPECT_GE(time.Elapsed(), 123.0);
  EXPECT_LT(time.Elapsed(), 124.0);
}

TEST(Hourglass, Pops) {
  toffee::Hourglass::Start();
  toffee::Hourglass::Start();
  toffee::Hourglass::Start();
  auto h1 = toffee::Hourglass::Stop().Elapsed();
  auto h2 = toffee::Hourglass::Stop().Elapsed();
  auto h3 = toffee::Hourglass::Stop().Elapsed();
  EXPECT_LT(h1, h2);
  EXPECT_LT(h2, h3);
}
