#include "core/background_color.hpp"
#include <gtest/gtest.h>

class BackgroundColorTest : public ::testing::Test {
protected:
  Color black = {0, 0, 0};
  Color white = {255, 255, 255};
  Color red = {255, 0, 0};
  Color blue = {0, 0, 255};

  BackgroundColor bg{black, red, white, blue};
};

TEST_F(BackgroundColorTest, ReturnsBottomLeftCorner) {
  Color result = bg.sampleUV(0.0f, 0.0f);
  EXPECT_EQ(result, black);
}

TEST_F(BackgroundColorTest, ReturnsBottomRightCorner) {
  Color result = bg.sampleUV(1.0f, 0.0f);
  EXPECT_EQ(result, red);
}

TEST_F(BackgroundColorTest, ReturnsTopLeftCorner) {
  Color result = bg.sampleUV(0.0f, 1.0f);
  EXPECT_EQ(result, white);
}

TEST_F(BackgroundColorTest, ReturnsTopRightCorner) {
  Color result = bg.sampleUV(1.0f, 1.0f);
  EXPECT_EQ(result, blue);
}
