#pragma once

#include <deque>
#include <memory>
#include <stack>

#include <rb_tree/concepts.hpp>
#include <rb_tree/node.hpp>


namespace rb_tree
{

template <typename T> requires Treeable<T>
class Tree;

template <typename T> requires Treeable<T>
struct TreeIterator;

template <typename T> requires Treeable<T>
struct TreeIteratorBase
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = T;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  TreeIteratorBase(const Tree<T>& tree):
    current_node_(tree.head_), size_(tree.getSize())
  {}

  TreeIteratorBase():
    current_node_(nullptr)
  {}

  virtual ~TreeIteratorBase() = default;

  void increment()
  {
    if (this->deque_.empty()) { this->current_node_ = nullptr; return; }
    this->current_node_ = this->deque_.front();
    this->deque_.pop_front();
  }

  virtual TreeIteratorBase* clone() = 0;

protected:
  friend struct TreeIterator<T>;

  virtual void pushSubtree(std::shared_ptr<Node<value_type>> node) = 0;

  std::shared_ptr<Node<value_type>> current_node_;
  size_t size_;
  std::deque<std::shared_ptr<Node<value_type>>> deque_;
};

template <typename T> requires Treeable<T>
struct TreeIterator
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = T;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  TreeIterator(TreeIteratorBase<T> *base):
    base_(base)
  {
    base_->pushSubtree(base_->current_node_);
    base->increment();
  }

  TreeIterator(const TreeIterator<T>& b):
    base_(b.base_->clone())
  {}

  // Prefix increment
  TreeIterator& operator++()
  {
    base_->increment();
    return *this;
  }

  // Postfix increment
  TreeIterator operator++(int)
  {
    TreeIterator<value_type> tmp(*this);
    base_->increment();
    return tmp;
  }

  reference operator*() const // {return base_->current_node_->data; }
  {
    if (base_->current_node_) {return base_->current_node_->data; }
    return NULL;
  }
  pointer operator->()
  {
    if (base_->current_node_) {return &(base_->current_node_->data); }
    return nullptr;
  }
  bool operator== (const TreeIterator& rhs) { return base_->current_node_ == rhs.base_->current_node_; };
  bool operator!= (const TreeIterator& rhs) { return base_->current_node_ != rhs.base_->current_node_; };

protected:
  std::unique_ptr<TreeIteratorBase<T>> base_;
};

template<typename T> requires Treeable<T> 
struct PreorderTreeIterator : public TreeIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = T;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  PreorderTreeIterator(const Tree<T>& tree):
    TreeIteratorBase<T>(tree)
  {}

  PreorderTreeIterator():
    TreeIteratorBase<T>()
  {}

  PreorderTreeIterator* clone() override { return new PreorderTreeIterator(*this); }

private:
  void pushSubtree(std::shared_ptr<Node<value_type>> node) override
  {
    if (node == nullptr) { return; }
    this->deque_.push_back(node);
    if (node->left != nullptr) { pushSubtree(node->left); }
    if (node->right != nullptr) { pushSubtree(node->right); }
  }
};

template<typename T> requires Treeable<T> 
struct InorderTreeIterator : public TreeIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = T;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  InorderTreeIterator(const Tree<T>& tree):
    TreeIteratorBase<T>(tree)
  {}

  InorderTreeIterator():
    TreeIteratorBase<T>()
  {}

  InorderTreeIterator* clone() override { return new InorderTreeIterator(*this); }

private:
  void pushSubtree(std::shared_ptr<Node<value_type>> node) override
  {
    if (node == nullptr) { return; }
    if (node->left != nullptr) { pushSubtree(node->left); }
    this->deque_.push_back(node);
    if (node->right != nullptr) { pushSubtree(node->right); }
  }
};

template<typename T> requires Treeable<T> 
struct PostorderTreeIterator : public TreeIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = T;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  PostorderTreeIterator(const Tree<T>& tree):
    TreeIteratorBase<T>(tree)
  {}

  PostorderTreeIterator():
    TreeIteratorBase<T>()
  {}

  PostorderTreeIterator* clone() override { return new PostorderTreeIterator(*this); }

private:
  void pushSubtree(std::shared_ptr<Node<value_type>> node) override
  {
    if (node == nullptr) { return; }
    if (node->left != nullptr) { pushSubtree(node->left); }
    if (node->right != nullptr) { pushSubtree(node->right); }
    this->deque_.push_back(node);
  }
};

} // namespace rb_tree