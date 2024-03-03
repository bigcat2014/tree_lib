#pragma once

#include <memory>
#include <optional>

#include <rb_tree/iterators.hpp>
#include <rb_tree/node.hpp>


namespace rb_tree
{

template <typename T> requires Graphable<T>
class RBTree
{
public:
  RBTree(): size_(0), head_(nullptr) {}

  //! \brief Get the number of nodes in the tree.
  //!
  //! \return size_t The number of nodes in the tree.
  size_t getSize() const { return size_; } 

  //! \brief Insert a node into the tree.
  //!
  //! \param [in] value The value to store in the new node.
  //! \return true If the node is successfully added.
  //! \return false If the node is not successfully added.
  bool insert(const T& value) noexcept
  {
    bool ret = insert_(head_, value);
    if (ret) { size_++; }
    rebalance();
    return ret;
  }

  //! \brief Remove a node from the tree.
  //!
  //! \param [in] value The value of the node to remove from the tree.
  //! \return true If the node is successfully removed.
  //! \return false If the node is not successfully removed.
  bool remove(const T& value) noexcept
  {
    bool ret = remove_(head_, value);
    if (ret) { size_--; }
    rebalance();
    return ret;
  }

protected:
  size_t size_;

  //! \brief The head of the tree.
  std::unique_ptr<Node<T>> head_;

  void rebalance() {}

  std::unique_ptr<Node<T>>& getSubtree(std::unique_ptr<Node<T>>& node, const T& value) { return value < *node ? node->left : node->right; }

  std::unique_ptr<Node<T>>& getInorderSuccessor(std::unique_ptr<Node<T>>& node)
  {
    if (!node->right) { return node; }

    std::unique_ptr<Node<T>>* curr_node = &(node->right);
    while ((*curr_node)->left)
    {
      curr_node = &((*curr_node)->left);
    }
    return *curr_node;
  }

  void swapNodes(std::unique_ptr<Node<T>>& node1, std::unique_ptr<Node<T>>& node2)
  {
    std::unique_ptr<Node<T>> tmp_left = std::move(node1->left);
    std::unique_ptr<Node<T>> tmp_right = std::move(node1->right);

    node1->left = std::move(node2->left);
    node1->right = std::move(node2->right);

    node2->left = std::move(tmp_left);
    node2->right = std::move(tmp_right);

    std::unique_ptr<Node<T>> tmp = std::move(node1);
    node1 = std::move(node2);
    node2 = std::move(tmp);
  }

  bool insert_(std::unique_ptr<Node<T>>& node, const T& value)
  {
    if (not node ) { node = std::make_unique<Node<T>>(value); return true; }
    return insert_(getSubtree(node, value), value);
  }

  bool remove_(std::unique_ptr<Node<T>>& node, const T& value)
  {
    // Node does not exist in tree
    if (not node) { return false; }

    // Found the node, remove it
    if (value == *node)
    {
      // Leaf node
      if (not node->left and not node->right) { node = nullptr; return true;}

      // Single child node
      if (node->left and not node->right) { node = std::move(node->left); return true; }

      if (node->right and not node->left) { node = std::move(node->right); return true; }

      // Dual child nodes
      swapNodes(node, getInorderSuccessor(node));
      // TODO(lthomas): Doesn't work
      return remove_(head_, value);
    }

    // Continue searching for node
    return remove_(getSubtree(node, value), value);
  }
};

} // namespace rb_tree