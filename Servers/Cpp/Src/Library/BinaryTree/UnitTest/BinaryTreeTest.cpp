/**
 * @file    BinaryTreeTest.cpp
 * @brief   Модульные тесты для класса BinaryTree.
 */

#include <set>
#include <iostream>

#include <gtest/gtest.h>

#include <Include/Library/BinaryTree.hpp>


TEST(BinaryTree, Insert_50_40_60_70) {
   BabbleChat::BinaryTree<int> tree;

   tree.Insert(50);
   tree.Insert(40);
   tree.Insert(60);
   tree.Insert(70);

   EXPECT_EQ(1, 1);
}


TEST(BinaryTree, Insert_67_3_100_4_50) {
   BabbleChat::BinaryTree<int> tree;

   tree.Insert(67);
   tree.Insert(3);
   tree.Insert(100);
   tree.Insert(50);
   tree.Insert(4);

   auto it = tree.begin();
   std::cout << *it << std::endl;
   ++it;
   std::cout << *it << std::endl;
   ++it;

   for (auto it : tree) {
      std::cout << it << " ";
   }
   std::cout << std::endl;

   EXPECT_EQ(1, 1);
}


int main(int argc, char *argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}