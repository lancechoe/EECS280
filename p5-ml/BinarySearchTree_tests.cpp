// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;


TEST(emptyTree) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int> temp = tree;

    ASSERT_TRUE(tree.check_sorting_invariant());

    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(0, tree.size());
    ASSERT_EQUAL(0, tree.height());
    ASSERT_TRUE(temp.empty());
    ASSERT_EQUAL(0, temp.size());
    ASSERT_EQUAL(0, temp.height());
    ASSERT_TRUE(tree.min_greater_than(5) == tree.end());
    ASSERT_TRUE(tree.min_element() == tree.end());
    ASSERT_TRUE(tree.max_element() == tree.end());
}

TEST(treeWithOneNode){
    BinarySearchTree<int> tree;
    
    tree.insert(0);

    BinarySearchTree<int> temp = tree;

    ASSERT_TRUE(tree.check_sorting_invariant());

    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(1, tree.size());
    ASSERT_EQUAL(1, tree.height());
    ASSERT_FALSE(temp.empty());
    ASSERT_EQUAL(1, temp.size());
    ASSERT_EQUAL(1, temp.height());
}

TEST(treeWithAllRight){
    BinarySearchTree<int> tree;
    
    tree.insert(0);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    cout << "cout << tree.to_string()" << endl;
    cout << tree.to_string() << endl << endl;

    ASSERT_TRUE(tree.check_sorting_invariant());

    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(5, tree.size());
    ASSERT_EQUAL(5, tree.height());
    
  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "0 1 3 5 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "0 1 3 5 7 ");

  ASSERT_TRUE(tree.find(5) != tree.end());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 0);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);
}

TEST(testWithAllLeft){
    BinarySearchTree<int> tree;
    
    tree.insert(10);
    tree.insert(8);
    tree.insert(6);
    tree.insert(4);
    tree.insert(2);
    tree.insert(0);

    cout << "cout << tree.to_string()" << endl;
    cout << tree.to_string() << endl << endl;

    ASSERT_TRUE(tree.check_sorting_invariant());

    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(6, tree.size());
    ASSERT_EQUAL(6, tree.height());
    
  ASSERT_TRUE(*tree.max_element() == 10);
  ASSERT_TRUE(*tree.min_element() == 0);
  ASSERT_TRUE(*tree.min_greater_than(5) == 6);
}

TEST(treeOneNode){
    BinarySearchTree<int> tree;
    tree.insert(7);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 7);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);
  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;
}

TEST(treeNormal){
    BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
  
}

TEST(treeWithMinus){
    BinarySearchTree<int> tree;
    tree.insert(0);
    tree.insert(-5);
    tree.insert(5);
    tree.insert(-2);
    tree.insert(-8);
    tree.insert(2);
    tree.insert(8);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 8);
  ASSERT_TRUE(*tree.min_element() == -8);
  ASSERT_TRUE(*tree.min_greater_than(-7) == -5);
  ASSERT_TRUE(tree.find(5) != tree.end());
  ASSERT_TRUE(tree.size() == 7);
  ASSERT_TRUE(tree.height() == 3);
}

TEST(treeOperator){
    BinarySearchTree<int> treeA;
    treeA.insert(3);
    treeA.insert(7);
    treeA.insert(5);
    ASSERT_TRUE(treeA.height() == 3);

    BinarySearchTree<int> treeB;
    treeB.insert(3);
    treeB.insert(5);
    treeB.insert(7);
    ASSERT_TRUE(treeA.height() == 3);

    ASSERT_TRUE(treeA.begin() != treeB.begin());
    ASSERT_TRUE(treeA.end() == treeB.end());
    ASSERT_TRUE(treeA.find(5) != treeB.find(5));
    ASSERT_TRUE(treeA.begin() == treeA.find(3));

    treeA.insert(8);
    treeB.insert(8);
    ASSERT_TRUE(treeA.height() != treeB.height());
    ASSERT_TRUE(treeA.find(8) != treeB.find(8));

    ASSERT_TRUE(treeA.check_sorting_invariant());
    ASSERT_TRUE(treeB.check_sorting_invariant());

    
}

TEST_MAIN()
