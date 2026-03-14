#include "core/app.hpp"
#include <gtest/gtest.h>

TEST(AppTest, SumAddsTwoIntegers) {
  EXPECT_EQ(App::sum(2, 3), 5);
  EXPECT_EQ(App::sum(-1, 1), 0);
  EXPECT_EQ(App::sum(-10, -5), -15);
}
