/**
 * @file    BinaryTreeTest.cpp
 * @brief   Модульные тесты для класса BinaryTree.
 */

#include <iostream> // delete me!

#include <gtest/gtest.h>

#include <Include/Library/BinaryTree.hpp>


TEST(BinaryTreeIterator, EmptyTree) {
   BabbleChat::BinaryTree<int> tree;

   auto beginIt = tree.begin();
   auto endIt = tree.end();

   EXPECT_TRUE(beginIt == endIt);
}


TEST(BinaryTreeIterator, InOrderTraversal) {
   BabbleChat::BinaryTree<int> tree;

   tree.Insert(10);
   tree.Insert(5);
   tree.Insert(15);
   tree.Insert(3);
   tree.Insert(7);
   tree.Insert(12);
   tree.Insert(17);

   // Ожидаемый результат обхода: [ 3, 5, 7, 10, 12, 15, 17 ]
   std::vector<int> expected = { 3, 5, 7, 10, 12, 15, 17 };
   std::vector<int> result;

   for (auto it = tree.begin(); it != tree.end(); ++it) {
      result.push_back(*it);
   }

   EXPECT_EQ(expected, result);
}


TEST(BinaryTreeIterator, OperatorAsterisk) {
   BabbleChat::BinaryTree<int> tree;
   tree.Insert(42);
   auto it = tree.begin();

   EXPECT_EQ(42, *it);
}


TEST(BinaryTreeIterator, OperatorArrow) {
   BabbleChat::BinaryTree<int> tree;
   tree.Insert(42);
   auto it = tree.begin();

   int* ptr = it.operator->();
   EXPECT_NE(nullptr, ptr);
   EXPECT_EQ(42, *ptr);
}


TEST(BinaryTreeIterator, EqualityInequalityOperators) {
   BabbleChat::BinaryTree<int> tree;
   tree.Insert(10);
   tree.Insert(5);
   tree.Insert(15);

   auto it1 = tree.begin();
   auto it2 = tree.begin();
   EXPECT_TRUE(it1 == it2);

   ++it1;
   EXPECT_FALSE(it1 == it2);
   EXPECT_TRUE(it1 != it2);
}


int main(int argc, char *argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}