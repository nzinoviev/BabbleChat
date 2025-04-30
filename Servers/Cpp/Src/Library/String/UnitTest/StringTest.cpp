// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


/**
 * @file    StringTest.cpp
 * @brief   Модульные тесты для класса String.
 */

#include <cstring>
#include <string>

#include <gtest/gtest.h>

#include "Include/Library/String.hpp"


TEST(StringCtorTest, Default)
{
   BabbleChat::String str;
   EXPECT_EQ(str.Length(), 0);
   EXPECT_TRUE(str.IsEmpty());
   EXPECT_STREQ(str.CStr(), "");
}


TEST(StringCtorTest, CString_SmallString)
{
   const char* input = "A Small String!";
   BabbleChat::String str(input);

   EXPECT_EQ(str.Length(), 15);
   EXPECT_FALSE(str.IsEmpty());
   EXPECT_STREQ(str.CStr(), input);
}


TEST(StringCtorTest, CString_HeapString)
{
   const char* input = "This string is definitely longer than fifteen!";
   BabbleChat::String str(input);

   EXPECT_EQ(str.Length(), std::strlen(input));
   EXPECT_FALSE(str.IsEmpty());
   EXPECT_STREQ(str.CStr(), input);
}


TEST(StringCtorTest, CString_ExplicitLength)
{
   const char input[] = { 'a', 'b', '\0', 'c', 'd' };
   BabbleChat::String str(input, 5);

   EXPECT_EQ(str.Length(), 5);
   EXPECT_EQ(std::memcmp(str.CStr(), input, 5), 0);
}


TEST(StringCopyTest, CopyCtor)
{
   BabbleChat::String original("Copy me!");
   BabbleChat::String copy(original);

   EXPECT_EQ(copy.Length(), original.Length());
   EXPECT_STREQ(copy.CStr(), original.CStr());
}


TEST(StringCopyTest, SelfAssigment)
{
   BabbleChat::String str("self");
   str = str;

   // Сравнение адресов указателей.
   EXPECT_EQ(str.CStr(), str.CStr());
}


TEST(StringCopyTest, CopyAssignment)
{
   BabbleChat::String left("left");
   BabbleChat::String right("right");

   left = right;

   EXPECT_EQ(left.Length(), right.Length());
   EXPECT_STREQ(left.CStr(), right.CStr());
}


int main(int argc, char *argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}