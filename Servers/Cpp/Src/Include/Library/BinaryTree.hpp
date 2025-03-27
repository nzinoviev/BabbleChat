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

// TODO: Добавить header guards.
// TODO: Добавить деструктор.
// TODO: Закончить класс Iterator.

namespace BabbleChat {

/**
 * @class   BinaryTree
 * @brief   Реализует функционал бинарного дерева поиска.
 * @tparam  T Тип данных, хранящихся в узлах дерева.
 */
template <typename T>
class BinaryTree {
private:
   // Предварительное объявление TreeNode.
   struct TreeNode;

public:
   // Предварительное объявление Iterator.
   class Iterator;

public:
   /**
    * @brief Конструктор по умолчанию.
    */
   BinaryTree();

   /**
    * @brief   Возвращает итератор, указывающий на первый элемент дерева.
    * @return  Итератор на начало дерева. Если дерево пустое, возвращает итератор, равный end().
    */
   Iterator begin();

   /**
    * @brief   Возвращает итератор, указывающий на конец дерева.
    * @return  Итератор на конец дерева.
    */
   Iterator end();

   /**
    * @brief Помещает данные в дерево.
    * @param[in] Data Данные.
    * @todo: Подумать над статусом возврата. 
    */
   void Insert(const T& Data);

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
      /**
       * @brief Конструктор.
       * @param[in] Node Указатель на узел дерева.
       */
      Iterator(TreeNode* Node);

      /**
       * @brief   Оператор разыменования.
       * @return  Ссылка на данные текущего узла.
       */
      T& operator*();

      /**
       * @brief   Оператор доступа к члену.
       * @return  Указатель на данные текущего узла.
       */
      T* operator->();

      /**
       * @brief Префиксный инкремент.
       * @return Итератор, указывающий на следующий узел.
       */
      Iterator& operator++();

      /**
       * @brief Постфиксный инкремент.
       * @return Итератор, указывающй на текущий узел до инкремента.
       */
      Iterator operator++(int);

      /**
       * @brief Префиксный декремент.
       * @return Итератор, указывающий на предыдущий узел.
       */
      Iterator& operator--();

      /**
       * @brief Постфиксный декремент.
       * @return Итератор, указывающий на узел до декремента.
       */
      Iterator operator--(int);

      /**
       * @brief Оператор сравнения на равенство.
       * @param[in] Other Итератор для сравнения.
       * @retval true   Если итераторы указывают на один и тот же узел.
       * @retval false  Если итераторы указывают на разные узлы.
       */
      bool operator==(const Iterator& Other) const;

      /**
       * @brief Оператор сравнения на неравенство.
       * @param[in] Other Итератор для сравнения.
       * @retval true   Если итераторы указывают на разные узлы.
       * @retval false  Если итераторы указывают на один и тот же узел.
       */
      bool operator!=(const Iterator& Other) const;

   private:
      TreeNode* current_; /** Указатель на текущий узел дерева. */
   };

private:
   TreeNode* root_; /** Указатель на корневой узел дерева. */
};


///////////////////////////////////////////////////////////////////////////////
/// Iterator Implementation
///////////////////////////////////////////////////////////////////////////////

template <typename T>
BinaryTree<T>::Iterator::Iterator(TreeNode* Node) : current_(Node) {}


template <typename T>
T& BinaryTree<T>::Iterator::operator*() {
   return current_->data_;
}


template <typename T>
T* BinaryTree<T>::Iterator::operator->() {
   return &current_->data_;
}


template <typename T>
typename BinaryTree<T>::Iterator& BinaryTree<T>::Iterator::operator++() {
   if (current_ == nullptr) {
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
bool BinaryTree<T>::Iterator::operator==(const BinaryTree<T>::Iterator& Other) const {
   return current_ == Other.current_;
}


template <typename T>
bool BinaryTree<T>::Iterator::operator!=(const BinaryTree<T>::Iterator& Other) const {
   return !(*this == Other);
}


///////////////////////////////////////////////////////////////////////////////
/// BinaryTree Implementation
///////////////////////////////////////////////////////////////////////////////


template <typename T>
BinaryTree<T>::BinaryTree() : root_(nullptr) {}


template <typename T>
void BinaryTree<T>::Insert(const T& Data) {
   if (nullptr == root_) {
      root_ = new TreeNode{Data, nullptr, nullptr, nullptr};
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
      current = new TreeNode{Data, previous, nullptr, nullptr};

      if (previous->data_ < current->data_) {
         previous->rightLeaf_ = current;
      } else {
         previous->leftLeaf_ = current;
      }
   }
}


template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::begin() {
   TreeNode* left = root_;
   while (left != nullptr && left->leftLeaf_ != nullptr)
   {
      left = left->leftLeaf_;
   }
   return Iterator{left};
}


template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::end() {
   return Iterator{nullptr};
}

}