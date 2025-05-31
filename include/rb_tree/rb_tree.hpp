#pragma once

#include <memory>
#include <optional>

#include <rb_tree/iterators.hpp>
#include <rb_tree/node.hpp>


namespace rb_tree
{

template <typename T> requires Treeable<T>
class Tree
{
public:
  Tree(): size_(0), head_(nullptr) {}

  //! \brief Get the number of nodes in the tree.
  //!
  //! \return size_t The number of nodes in the tree.
  size_t getSize() const noexcept { return size_; } 

  //! \brief Insert a node into the tree.
  //!
  //! \param [in] value The value to store in the new node.
  //! \return true If the node is successfully added.
  //! \return false If the node is not successfully added.
  bool insert(const T& value) noexcept
  {
    bool ret = insert_(head_, value);
    if (ret) { size_++; }
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
    return ret;
  }

  TreeIterator<T> preorder_begin() const { return TreeIterator<T>(new PreorderTreeIterator<T>(*this)); }
  TreeIterator<T> preorder_end() const { return TreeIterator<T>(new PreorderTreeIterator<T>()); }

  TreeIterator<T> inorder_begin() const { return TreeIterator<T>(new InorderTreeIterator<T>(*this)); }
  TreeIterator<T> inorder_end() const { return TreeIterator<T>(new InorderTreeIterator<T>()); }

  TreeIterator<T> postorder_begin() const { return TreeIterator<T>(new PostorderTreeIterator<T>(*this)); }
  TreeIterator<T> postorder_end() const { return TreeIterator<T>(new PostorderTreeIterator<T>()); }

protected:
  friend struct TreeIteratorBase<T>;

  //! \brief The number of nodes in the tree.
  size_t size_;

  //! \brief The head of the tree.
  std::shared_ptr<Node<T>> head_;

  inline std::shared_ptr<Node<T>>& getSubtree(std::shared_ptr<Node<T>>& node, const T& value) { return value < *node ? node->left : node->right; }

  std::shared_ptr<Node<T>> getInorderSuccessor(std::shared_ptr<Node<T>>& node)
  {
    std::shared_ptr<Node<T>> curr_node = nullptr;

    // Get to the left-most child of the right child of current node
    if (node->right != nullptr)
    {
      curr_node = node->right;
      while (curr_node->left != nullptr)
      {
        curr_node = curr_node->left;
      }
    }
    else
    {
      curr_node = node;
      std::shared_ptr<Node<T>> prev_node = node->parent;
      while (prev_node != nullptr && curr_node == prev_node->right) {
        curr_node = prev_node;
        prev_node = prev_node->parent;
      }
      if (curr_node->right != prev_node)
      {
        curr_node = prev_node;
      }
    }

    return curr_node;
  }

  void swapNodes(std::shared_ptr<Node<T>>& node1, std::shared_ptr<Node<T>>& node2)
  {
    std::shared_ptr<Node<T>> tmp_left = node1->left;
    std::shared_ptr<Node<T>> tmp_right = node1->right;
    std::shared_ptr<Node<T>> tmp_parent = node1->parent;

    node1->left = node2->left;
    node1->right = node2->right;
    node1->parent = node2->parent;

    node2->left = tmp_left;
    node2->right = tmp_right;
    node2->parent = tmp_parent;

    std::swap(*node1, *node2);
  }

  bool insert_(std::shared_ptr<Node<T>>& node, const T& value)
  {
    static std::shared_ptr<Node<T>> parent_node = nullptr;

    // We've reached the insertion point
    if (not node )
    {
      node = std::make_shared<Node<T>>(value, parent_node);
      parent_node = nullptr;
      return true;
    }

    // Node exists at current position, keep going
    parent_node = node;
    return insert_(getSubtree(node, value), value);
  }

  bool remove_(std::shared_ptr<Node<T>>& node, const T& value)
  {
    // Node does not exist in tree
    if (not node) { return false; }

    // Found the node, remove it
    if (value == *node)
    {
      if (not node->left and not node->right) { node = nullptr; }
      else
      {
        std::shared_ptr<Node<T>> successor = getInorderSuccessor(node);
        swapNodes(node, successor);

        if (successor->parent->left == successor) { successor->parent->left = nullptr; }
        else if (successor->parent->right == successor) { successor->parent->right = nullptr; }
      }

      return true;
    }

    // Continue searching for node
    return remove_(getSubtree(node, value), value);
  }
};

} // namespace rb_tree