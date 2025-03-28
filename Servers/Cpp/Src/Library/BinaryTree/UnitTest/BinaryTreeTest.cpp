/**
 * @file    BinaryTreeTest.cpp
 * @brief   Модульные тесты для класса BinaryTree.
 */

#include <iostream> // delete me!

#include <gtest/gtest.h>

#include <Include/Library/BinaryTree.hpp>


///////////////////////////////////////////////////////////////////////////////
/// BinaryTree::Iterator Tests
///////////////////////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////////////////////
/// BinaryTree Tests
///////////////////////////////////////////////////////////////////////////////

TEST(BinaryTree, Insert_SingleInsertion) {
   BabbleChat::BinaryTree<int> tree;
   tree.Insert(42);

   auto begin = tree.begin();
   auto end = tree.end();

   // Дерево не должно быть пустым.
   ASSERT_NE(begin, end);

   // Первый элементь должен быть равен 42.
   EXPECT_EQ(*begin, 42);

   // Если в дереве один элемент, то после инкремента итератор begin должен стать равным end.
   ++begin;
   EXPECT_EQ(begin, end);
}


TEST(BinaryTree, Insert__MultipleInsertion) {
   BabbleChat::BinaryTree<int> tree;

   std::vector values = { 10, 5, 15, 3, 7, 12, 17 };
   for (int value : values) {
      tree.Insert(value);
   }

   // Ожидаемый результат in-order обхода.
   std::vector<int> expected = { 3, 5, 7, 10, 12, 15, 17 };
   std::vector<int> result;

   for (auto it = tree.begin(); it != tree.end(); ++it) {
      result.push_back(*it);
   }

   EXPECT_EQ(result,expected);
}


std::vector<int> TreeToVector(BabbleChat::BinaryTree<int>& Tree) {
   std::vector<int> result;

   for (auto it = Tree.begin(); it != Tree.end(); ++it) {
      result.push_back(*it);
   }

   return result;
}


TEST(BinaryTree, Remove_LeafNode) {
   BabbleChat::BinaryTree<int> tree;

   tree.Insert(50);
   tree.Insert(30);
   tree.Insert(70);
   tree.Insert(20);
   tree.Insert(40);
   tree.Insert(60);
   tree.Insert(80);

   EXPECT_TRUE(tree.Remove(20));

   std::vector<int> result = TreeToVector(tree);
   EXPECT_EQ(result, std::vector<int>({ 30, 40, 50, 60, 70, 80 }));
}


TEST(BinaryTree, Remove_NodeWithOneChild) {
   BabbleChat::BinaryTree<int> tree;

   tree.Insert(50);
   tree.Insert(30);
   tree.Insert(70);
   tree.Insert(20);
   tree.Insert(40);
   tree.Insert(60);
   tree.Insert(80);

   EXPECT_TRUE(tree.Remove(40));

   std::vector<int> result = TreeToVector(tree);
   EXPECT_EQ(result, std::vector<int>({ 20, 30, 50, 60, 70, 80 }));
}


TEST(BinaryTree, Remove_NodeWithTwoChildren) {
   BabbleChat::BinaryTree<int> tree;

   tree.Insert(50);
   tree.Insert(30);
   tree.Insert(70);
   tree.Insert(20);
   tree.Insert(40);
   tree.Insert(60);
   tree.Insert(80);

   EXPECT_TRUE(tree.Remove(30));

   std::vector<int> result = TreeToVector(tree);
   EXPECT_EQ(result, std::vector<int>({ 20, 40, 50, 60, 70, 80 }));
}


TEST(BinaryTree, Remove_RootNode) {
   BabbleChat::BinaryTree<int> tree;

   tree.Insert(50);
   tree.Insert(30);
   tree.Insert(70);
   tree.Insert(20);
   tree.Insert(40);
   tree.Insert(60);
   tree.Insert(80);

   EXPECT_TRUE(tree.Remove(50));

   std::vector<int> result = TreeToVector(tree);
   EXPECT_EQ(result, std::vector<int>({ 20, 30, 40, 60, 70, 80 }));
}


int main(int argc, char *argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}