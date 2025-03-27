/**
 * @file    BinaryTree.hpp
 * @brief   Объявление и реализация класс BinaryTree.
 *
 * @details Класс BinaryTree представляет собой реализацию бинарного дерева поиска (Binary Search
 *          Tree, BST). Поддерживает основные операции: вставка, удаление и поиск элементов. Дерево
 *          не является сбалансированным, поэтому в худшем случае сложность операций может
 *          деградировать до O(n).
 *
 *          Алгоритмическая сложность:
 *          - Поиск: O(log n) в среднем случае, O(n) в худшем случае.
 *          - Вставка элемента: O(log n) в среднем случае, O(n) в худшем случае.
 *          - Удаление элемента: O(log n) в среднем случае, O(n) в худшем случае.
 */

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <cstddef>
#include <iterator>

// TODO: Добавить деструктор.
// TODO: Закончить класс Iterator.
// TODO: Добавить проверку PVS.
// TODO: Добавить дополнительные флаги gcc.
// TODO: Добавить проверки на утечку памяти. 

namespace BabbleChat {

/**
 * @class   BinaryTree
 * @brief   Реализует функционал бинарного дерева поиска.
 * @tparam  T Тип данных, хранящихся в узлах дерева.
 */
template <typename T>
class BinaryTree {
private:
   /**
    * @struct  TreeNode
    * @brief   Внутренняя структура, описывающая узел бинарного дерева.
    */
   struct TreeNode {
      T           data_;      /** Данные, хранящиеся в узле. */
      TreeNode*   parent_;    /** Указатель на родительский узел. */
      TreeNode*   leftLeaf_;  /** Указатель на левый дочерний узел. */
      TreeNode*   rightLeaf_; /** Указатель на правый дочерний узел. */
   };

public:
   /**
    * @class   Iterator
    * @brief   Внутренний класс. Реализует итератор для обхода элементов бинарного дерева.
    */
   class Iterator {
      public:
         using iterator_category = std::bidirectional_iterator_tag;
         using value_type        = T;
         using difference_type   = std::ptrdiff_t;
         using pointer           = T*;
         using reference         = T&;

         /**
          * @brief Конструктор.
          * @param[in] Node Указатель на узел дерева.
          */
         explicit Iterator(TreeNode* Node) noexcept;

         /**
          * @brief   Оператор разыменования.
          * @return  Ссылка на данные текущего узла.
          */
         reference operator*() const noexcept;

         /**
          * @brief   Оператор доступа к члену.
          * @return  Указатель на данные текущего узла.
          */
         pointer operator->() const noexcept;

         /**
          * @brief Префиксный инкремент.
          * @return Итератор, указывающий на следующий узел.
          */
         Iterator& operator++() noexcept;

         /**
          * @brief Постфиксный инкремент.
          * @return Итератор, указывающй на текущий узел до инкремента.
          */
         Iterator operator++(int) noexcept;

         /**
          * @brief Префиксный декремент.
          * @return Итератор, указывающий на предыдущий узел.
          */
         Iterator& operator--() noexcept;

         /**
          * @brief Постфиксный декремент.
          * @return Итератор, указывающий на узел до декремента.
          */
         Iterator operator--(int) noexcept;

         /**
          * @brief Оператор сравнения на равенство.
          * @param[in] Other Итератор для сравнения.
          * @retval true   Если итераторы указывают на один и тот же узел.
          * @retval false  Если итераторы указывают на разные узлы.
          */
         bool operator==(const Iterator& Other) const noexcept;

         /**
          * @brief Оператор сравнения на неравенство.
          * @param[in] Other Итератор для сравнения.
          * @retval true   Если итераторы указывают на разные узлы.
          * @retval false  Если итераторы указывают на один и тот же узел.
          */
         bool operator!=(const Iterator& Other) const noexcept;

      private:
         TreeNode* current_; /** Указатель на текущий узел дерева. */
      };

public:
   /**
    * @brief Конструктор по умолчанию.
    */
   BinaryTree() noexcept;

   /**
    * @brief   Возвращает итератор, указывающий на первый элемент дерева.
    * @return  Итератор на начало дерева. Если дерево пустое, возвращает итератор, равный end().
    */
   Iterator begin() const;

   /**
    * @brief   Возвращает итератор, указывающий на конец дерева.
    * @return  Итератор на конец дерева.
    */
   Iterator end() const;

   /**
    * @brief Помещает данные в дерево.
    * @param[in] Data Данные.
    * TODO: Подумать над статусом возврата.
    */
   void Insert(const T& Data);

private:
   TreeNode* root_; /** Указатель на корневой узел дерева. */
};


///////////////////////////////////////////////////////////////////////////////
/// Iterator Implementation
///////////////////////////////////////////////////////////////////////////////

template <typename T>
BinaryTree<T>::Iterator::Iterator(TreeNode* Node) noexcept : current_(Node) {}


template <typename T>
typename BinaryTree<T>::Iterator::reference
BinaryTree<T>::Iterator::operator*() const noexcept {
   return current_->data_;
}


template <typename T>
typename BinaryTree<T>::Iterator::pointer
BinaryTree<T>::Iterator::operator->() const noexcept {
   return &current_->data_;
}


template <typename T>
typename BinaryTree<T>::Iterator&
BinaryTree<T>::Iterator::operator++() noexcept {
   if (nullptr == current_) {
      return *this;
   }

   if (current_->rightLeaf_ != nullptr) {
      current_ = current_->rightLeaf_;
      while (current_->leftLeaf_ != nullptr) {
         current_ = current_->leftLeaf_;
      }
   } else {
      TreeNode* parent = current_->parent_;
      while (parent != nullptr && current_ == parent->rightLeaf_) {
         current_ = parent;
         parent = parent->parent_;
      }
      current_ = parent;
   }

   return *this;
}


template <typename T>
typename BinaryTree<T>::Iterator
BinaryTree<T>::Iterator::operator++(int) noexcept {
   Iterator ret(current_);

   if (nullptr == current_) {
      return ret;
   }

   if (current_->rightLeaf_ != nullptr) {
      current_ = current_->rightLeaf_;
      while (current_->leftLeaf_ != nullptr) {
         current_ = current_->leftLeaf_;
      }
   } else {
      TreeNode* parent = current_->parent_;
      while (parent != nullptr && current_ == parent->rightLeaf_) {
         current_ = parent;
         parent = parent->parent_;
      }
      current_ = parent;
   }

   return ret;
}


template <typename T>
bool BinaryTree<T>::Iterator::operator==(const BinaryTree<T>::Iterator& Other) const noexcept {
   return current_ == Other.current_;
}


template <typename T>
bool BinaryTree<T>::Iterator::operator!=(const BinaryTree<T>::Iterator& Other) const noexcept {
   return !(*this == Other);
}


///////////////////////////////////////////////////////////////////////////////
/// BinaryTree Implementation
///////////////////////////////////////////////////////////////////////////////


template <typename T>
BinaryTree<T>::BinaryTree() noexcept : root_(nullptr) {}


template <typename T>
void BinaryTree<T>::Insert(const T& Data) {
   if (nullptr == root_) {
      root_ = new TreeNode { Data, nullptr, nullptr, nullptr };
   } else {
      TreeNode* current = root_;
      TreeNode* previous = root_;
      while (current != nullptr) {
         if (current->data_ < Data) {
            previous = current;
            current = current->rightLeaf_;
         } else {
            previous = current;
            current = current->leftLeaf_;
         }
      }
      current = new TreeNode { Data, previous, nullptr, nullptr };

      if (previous->data_ < current->data_) {
         previous->rightLeaf_ = current;
      } else {
         previous->leftLeaf_ = current;
      }
   }
}


template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::begin() const {
   TreeNode* left = root_;
   while (left != nullptr && left->leftLeaf_ != nullptr)
   {
      left = left->leftLeaf_;
   }
   return Iterator { left };
}


template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::end() const {
   return Iterator { nullptr };
}

}

#endif // __BINARY_TREE_H__