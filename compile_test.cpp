/*****************************************
** File:    compilation_test.cpp
** Project: CSCE 221 Lab 4 Spring 2022
** Author:  Naimur Rahman
** Date:    03/21/2022
** Section: 511
** E-mail:  naimurrah01@tamu.edu
** Description: Tests compilation of BinarySearchTree and AVLTree Classes
**/
#include "binary_search_tree.h"
#include "avl_tree.h"
#include "binary_search_tree.h"
#include "avl_tree.h"

struct ComparableValue {
    int value;
    
    ComparableValue() : value{0} {}
    explicit ComparableValue(int value) : value{value} {}
    
    bool operator<(const ComparableValue& rhs) const { 
        return value < rhs.value; 
    }
    bool operator>(const ComparableValue& rhs) const { 
        return rhs < *this; 
    }
    bool operator>=(const ComparableValue& rhs) const { 
        return !(*this < rhs); 
    }
    bool operator<=(const ComparableValue& rhs) const { 
        return !(*this > rhs); 
    }
    bool operator!=(const ComparableValue& rhs) const { 
        return *this < rhs || *this > rhs; 
    }
    bool operator==(const ComparableValue& rhs) const { 
        return !(*this != rhs); 
    }
};

int main() {
    // BST
    {
        BinarySearchTree<int> tree;
        tree.insert(2);
        tree.insert(1);
        tree.insert(3);
        tree.contains(4);
        tree.find_min();
        tree.find_max();
        tree.remove(1);
    }
    
    {
        BinarySearchTree<ComparableValue> tree;
        tree.insert(ComparableValue(2));
        tree.insert(ComparableValue(1));
        tree.insert(ComparableValue(3));
        tree.contains(ComparableValue(4));
        tree.find_min();
        tree.find_max();
        tree.remove(ComparableValue(1));
    }
    
    
    // AVL
    {
        AVLTree<int> tree;
        tree.insert(2);
        tree.insert(1);
        tree.insert(3);
        tree.contains(4);
        tree.find_min();
        tree.find_max();
        tree.remove(1);
    }
    
    {
        AVLTree<ComparableValue> tree;
        tree.insert(ComparableValue(2));
        tree.insert(ComparableValue(1));
        tree.insert(ComparableValue(3));
        tree.contains(ComparableValue(4));
        tree.find_min();
        tree.find_max();
        tree.remove(ComparableValue(1));
    }
}
