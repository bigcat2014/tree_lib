#include <iostream>
#include <memory>

#include <rb_tree/rb_tree.hpp>


template <typename T>
void printPreorder(const rb_tree::Tree<T>& tree, unsigned int idx)
{
  std::cout << "Tree " << idx << ": [" << std::endl;
  for (auto itr = tree.preorder_begin(); itr != tree.preorder_end(); itr++)
  {
    std::cout << '\t' << *itr << std::endl;
  }
  std::cout << "]" << std::endl;
  std::cout << std::endl;
}

template <typename T>
void printInorder(const rb_tree::Tree<T>& tree, unsigned int idx)
{
  std::cout << "Tree " << idx << ": [" << std::endl;
  for (auto itr = tree.inorder_begin(); itr != tree.inorder_end(); itr++)
  {
    std::cout << '\t' << *itr << std::endl;
  }
  std::cout << "]" << std::endl;
  std::cout << std::endl;
}

template <typename T>
void printPostorder(const rb_tree::Tree<T>& tree, unsigned int idx)
{
  std::cout << "Tree " << idx << ": [" << std::endl;
  for (auto itr = tree.postorder_begin(); itr != tree.postorder_end(); itr++)
  {
    std::cout << '\t' << *itr << std::endl;
  }
  std::cout << "]" << std::endl;
  std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
  // rb_tree::Node<int> n1(1);

  // n1.left = std::make_unique<rb_tree::Node<int>>(2);
  // n1.right = std::make_unique<rb_tree::Node<int>>(3);

  // std::cout << n1.data << std::endl;
  // std::cout << n1.left->data << std::endl;
  // std::cout << n1.right->data << std::endl;

  rb_tree::Tree<int> tree1;
  tree1.insert(3);
  printPreorder(tree1, 1);
  tree1.insert(21);
  printPreorder(tree1, 2);
  tree1.insert(32);
  printPreorder(tree1, 3);
  tree1.insert(15);
  printPreorder(tree1, 4);

  // tree1.insert(2);
  // tree1.insert(1);
  // tree1.insert(5);
  // tree1.insert(4);
  // tree1.insert(6);
  // tree1.insert(3);
  // tree1.insert(7);
  // printPreorder<int>(tree1, 1);
  // printInorder<int>(tree1, 1);
  // printPostorder<int>(tree1, 1);
  
  // tree1.remove(2);
  // printPreorder<int>(tree1, 2);
  // printInorder<int>(tree1, 2);
  // printPostorder<int>(tree1, 2);
  
  // tree1.remove(1);
  // printPreorder<int>(tree1, 3);
  // printInorder<int>(tree1, 3);
  // printPostorder<int>(tree1, 3);
  
  // tree1.remove(4);
  // printPreorder<int>(tree1, 4);
  // printInorder<int>(tree1, 4);
  // printPostorder<int>(tree1, 4);
  
  // tree1.remove(6);
  // printPreorder<int>(tree1, 5);
  // printInorder<int>(tree1, 5);
  // printPostorder<int>(tree1, 5);
  
  // tree1.remove(5);
  // printPreorder<int>(tree1, 6);
  // printInorder<int>(tree1, 6);
  // printPostorder<int>(tree1, 6);

  return 0;
}
