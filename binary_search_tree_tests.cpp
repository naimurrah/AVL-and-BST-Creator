/*****************************************
** File:    binary_search_tree_tests.cpp
** Project: CSCE 221 Lab 4 Spring 2022
** Author:  Naimur Rahman
** Date:    03/21/2022
** Section: 511
** E-mail:  naimurrah01@tamu.edu
** Description: Tests for BinarySearchTree class
**/
#include <iostream>
#include "binary_search_tree.h"
using std::cout, std::endl;
int main() {
    // TODO(student): write tests
    
    BinarySearchTree<int> a;
    a.insert(1);
    a.insert(0);
    a.insert(2);
    a.print_tree();
    cout << "Is Empty? Should be 0: " << a.is_empty() << endl;
    a.make_empty();
    cout << "Is Empty after emptying? should be 1: " << a.is_empty() << endl;

    a.insert(1);
    a.insert(0);
    a.insert(2);
    a.insert(3);
    a.print_tree();
    cout << "Removing 2" << endl;
    a.remove(2);
    a.print_tree();
    cout << "Is Empty? Should be 0: " << a.is_empty() << endl;

    cout << "Removing 1" << endl;
    a.remove(1);
    a.print_tree();
    cout << "Is Empty? Should be 0: " << a.is_empty() << endl;
    cout << "Removing 0" << endl;
    a.remove(0);
    a.print_tree();
    cout << "Is Empty? Should be 0: " << a.is_empty() << endl;

    BinarySearchTree<int> t;

    // fail min/max test:
    try {
        t.find_min();
    }
    catch (std::invalid_argument) {
        cout << "Invalid min test success" << endl;
        cout << endl;
    }

    try {
        t.find_min();
    }
    catch (std::invalid_argument) {
        cout << "Invalid max test success" << endl;
        cout << endl;
    }
    cout << "printing empty tree: " << endl;
    t.print_tree();
    cout << "Empty? should be 1: " << t.is_empty() << endl;
    cout << endl;

    cout << endl;
    t.insert(2);
    t.print_tree();
    cout << "Empty? should be 0: " << t.is_empty() << endl;
    cout << "Min: should be 2: " << t.find_min() << endl;
    cout << "Max: should be 2: " << t.find_max() << endl;
    cout << endl;

    t.insert(-6);
    cout << endl;
    t.print_tree();
    cout << "Min: should be -6: " << t.find_min() << endl;
    cout << "Max: should be 2: " << t.find_max() << endl;
    cout << endl;

    // inserting
    t.insert(-3);
    cout << endl;
    t.print_tree();
    cout << endl;

    t.insert(9);
    cout << endl;
    t.print_tree();
    cout << endl;

    t.insert(4);
    cout << endl;
    t.print_tree();
    cout << endl;

    t.insert(-1);
    cout << endl;
    t.print_tree();
    cout << endl;

    t.insert(-5);
    cout << endl;
    t.print_tree();
    cout << endl;

    t.insert(8);
    cout << endl;
    t.print_tree();
    cout << endl;

    cout << endl;

    // removing
    cout << "Removing 9" << endl;
    t.remove(9);
    t.print_tree();
    cout << endl;

    cout << "Removing 2(Root)" << endl;
    cout << endl;
    t.remove(2);
    t.print_tree();
    cout << endl;

    cout << "Removing -3" << endl;
    cout << endl;
    t.remove(-3);
    t.print_tree();
    cout << endl;

    // min/max tests

    cout << endl;
    cout << "Min: should be -6: " << t.find_min() << endl;
    cout << "Max: should be 8: " << t.find_max() << endl;
    cout << endl;

    // copying and assigning
    cout << endl;
    cout << "Copy of Tree: " << endl;
    BinarySearchTree<int> cop(t);
    cop.print_tree();

    BinarySearchTree<int> copA = t;
    cout << endl;
    copA.print_tree();
    cout << endl;
    
    // emptying tree
    cout << "Making empty: " << endl;
    cout << endl;
    copA.make_empty();
    copA.print_tree();
    cout << "Is Empty? Should be 1: " << copA.is_empty() << endl;
    cout << "Contains 2: should be 0 since empty: " << copA.contains(2) << endl;
    cout << endl;

    cout << "COP Tree: should not be empty." << endl;
    cop.print_tree();
    cout << endl << endl;

    // contains tests
    cout << "Contains -1: should be 1: " << cop.contains(-1) << endl;
    cout << "Contains 2: should be 0: " << cop.contains(2) << endl;
    cout << "Contains -6: should be 1: " << cop.contains(-6) << endl;
    cout << "Contains 4: should be 1: " << cop.contains(4) << endl;
    cout << "Contains 9: should be 0: " << cop.contains(9) << endl;
    cout << "Contains -5: should be 1: " << cop.contains(-5) << endl;
    cout << endl;

    // char binary search tree test (Since you can compare)
    BinarySearchTree<char> cbst;
    cbst.insert('a');
    cbst.remove('a');

    cbst.insert('a');
    cbst.insert('c');
    cbst.insert('z');
    cbst.insert('b');
    cout << endl;
    cbst.print_tree();
    cout << "Min val: should be a: " << cbst.find_min() << endl;
    cout << "Max val: should be z: " << cbst.find_max() << endl;
    cout << endl;

    cout << "Removing c (node)" << endl;
    cbst.remove('c');
    cbst.print_tree();
    cout << "Min val: should be a: " << cbst.find_min() << endl;
    cout << "Max val: should be z: " << cbst.find_max() << endl;
}
