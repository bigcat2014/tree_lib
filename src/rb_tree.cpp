#include <iostream>
#include <memory>

#include <rb_tree/rb_tree.hpp>


int main(int argc, char const *argv[])
{
  rb_tree::Node<int> n1(1);

  n1.left = std::make_unique<rb_tree::Node<int>>(2);
  n1.right = std::make_unique<rb_tree::Node<int>>(3);

  std::cout << n1.data << std::endl;
  std::cout << n1.left->data << std::endl;
  std::cout << n1.right->data << std::endl;

  rb_tree::RBTree<int> tree1;
  tree1.insert(2);
  tree1.insert(1);
  tree1.insert(5);
  tree1.insert(4);
  tree1.insert(6);
  tree1.insert(3);
  tree1.insert(7);

  tree1.remove(2);

  // tree1.remove(1);
  // tree1.remove(4);
  // tree1.remove(6);
  // tree1.remove(5);

  return 0;
}
