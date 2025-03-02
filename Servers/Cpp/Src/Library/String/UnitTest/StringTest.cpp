/**
 * @file StringTest.cpp
 * @brief Модульные тесты для класса String.
 */

#include <string>

#include <gtest/gtest.h>

#include "Include/Library/String.hpp"

TEST(StringConstructorTest, Default) {
   BabbleChat::String str;
   EXPECT_EQ(str.Length(), 0);
   EXPECT_EQ(str.Data(), nullptr);
}


TEST(StringConstructorTest, CString_nullptr) {
   EXPECT_THROW(BabbleChat::String str(nullptr), std::runtime_error);
}


TEST(StringConstructorTest, CString_EmptyString) {
   BabbleChat::String str("");

   EXPECT_EQ(str.Length(), 0);
   EXPECT_STREQ(str.Data(), "");
}


TEST(StringConstructorTest, CString_SmallString) {
   BabbleChat::String str("small string");

   EXPECT_EQ(str.Length(), 12);
   EXPECT_STREQ(str.Data(), "small string");
}


int main(int argc, char *argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}