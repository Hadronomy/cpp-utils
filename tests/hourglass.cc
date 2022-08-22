#include <thread>
#include <chrono>

#include <gtest/gtest.h>
#include <utils/hourglass.h>

TEST(Hourglass, ReportsMilliseconds) {
  utils::Hourglass::Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(123));
  auto time = utils::Hourglass::Stop();
  EXPECT_GE(time.Elapsed(), 123.0);
  EXPECT_LT(time.Elapsed(), 124.0);
}

TEST(Hourglass, Pops) {
  utils::Hourglass::Start();
  utils::Hourglass::Start();
  utils::Hourglass::Start();
  auto h1 = utils::Hourglass::Stop().Elapsed();
  auto h2 = utils::Hourglass::Stop().Elapsed();
  auto h3 = utils::Hourglass::Stop().Elapsed();
  EXPECT_LT(h1, h2);
  EXPECT_LT(h2, h3);
}