#pragma once

#include <functional>
#include <memory>

#include <rb_tree/concepts.hpp>


namespace rb_tree
{

template <typename T> requires Graphable<T>
struct Node
{
  //! \brief Construct a tree node with the specified value.
  //! \param [in] value The value to store in the node.
  Node(const T& value):
    data(value),
    left(nullptr),
    right(nullptr)
  {}

  //! \brief The value stored in the node.
  T data;

  //! \brief The left child node.
  std::unique_ptr<Node<T>> left;

  //! \brief The right child node.
  std::unique_ptr<Node<T>> right;

  // EQ operator
  inline        bool operator==(const Node<T>& rhs)               const { return data == rhs.data; }
  inline        bool operator==(const T& rhs)                       const { return data == rhs; }
  inline friend bool operator==(const T& lhs, const Node<T>& rhs)       { return lhs == rhs.data; }

  // Comparison operators
  inline        bool operator>(const Node<T>& rhs)               const { return data > rhs.data; }
  inline        bool operator>(const T& rhs)                       const { return data > rhs; }
  inline friend bool operator>(const T& lhs, const Node<T>& rhs)       { return lhs > rhs.data; }

  inline        bool operator<(const Node<T>& rhs)               const { return data < rhs.data; }
  inline        bool operator<(const T& rhs)                       const { return data < rhs; }
  inline friend bool operator<(const T& lhs, const Node<T>& rhs)       { return lhs < rhs.data; }

  // Stream insertion operator
  // TODO: Remove this after testing
  inline friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) { os << "[data: " << node.data << "]"; return os;}
};

template <typename T> requires Hashable<T>
struct NodeHash
{
  size_t operator()(const rb_tree::Node<T> &x) const
  {
    return std::hash<T>()(*x.data);
  }
};

template <typename T> requires Graphable<T>
struct NodePtrHash {
  using is_transparent = void;

  std::size_t operator() (const std::shared_ptr<Node<T>>& p) const { return NodeHash<T>()(*p); }
  std::size_t operator() (const Node<T>& p)                  const { return NodeHash<T>()(p); }
  std::size_t operator() (const T& p)                          const { return std::hash<T>()(p); }
};

template <typename T> requires Graphable<T>
struct NodePtrCompare {
  using is_transparent = void;

  bool operator() (const std::shared_ptr<Node<T>>& a, const std::shared_ptr<Node<T>>& b) const { return (*a) == (*b); }

  bool operator() (const Node<T>& a, const std::shared_ptr<Node<T>>& b)                  const { return a == (*b); }
  bool operator() (const std::shared_ptr<Node<T>>& a, const Node<T>& b)                  const { return (*a) == b; }

  bool operator() (const T& a, const std::shared_ptr<Node<T>>& b)                          const { return a == (*b); }
  bool operator() (const std::shared_ptr<Node<T>>& a, const T& b)                          const { return (*a) == b; }
};

} // namespace rb_tree