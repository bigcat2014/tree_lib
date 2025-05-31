#pragma once

#include <functional>
#include <memory>

#include <rb_tree/concepts.hpp>


namespace rb_tree
{

enum class COLOR
{
  RED = 0,
  BLACK
};

template <typename T> requires Treeable<T>
struct Node
{
  //! \brief Construct a tree node with the specified value.
  //! \param [in] value The value to store in the node.
  Node(const T& value, std::shared_ptr<Node<T>> parent):
    data(value),
    left(nullptr),
    right(nullptr),
    parent(parent),
    color(COLOR::RED)
  {}

  //! \brief The value stored in the node.
  T data;

  //! \brief The left child node.
  std::shared_ptr<Node<T>> left;

  //! \brief The right child node.
  std::shared_ptr<Node<T>> right;

  //! \brief The parent of the current node.
  std::shared_ptr<Node<T>> parent;

  COLOR color;

  // EQ operator
  inline        bool operator==(const Node<T>& rhs)               const { return data == rhs.data; }
  inline        bool operator==(const T& rhs)                       const { return data == rhs; }
  inline friend bool operator==(const T& lhs, const Node<T>& rhs)       { return lhs == rhs.data; }

  // LT operator
  inline        bool operator<(const Node<T>& rhs)               const { return data < rhs.data; }
  inline        bool operator<(const T& rhs)                       const { return data < rhs; }
  inline friend bool operator<(const T& lhs, const Node<T>& rhs)       { return lhs < rhs.data; }

  // Stream insertion operator
  // TODO: Remove this after testing
  inline friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) { os << "[data: " << node.data << "]"; return os;}
};

} // namespace rb_tree