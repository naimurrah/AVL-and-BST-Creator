/*****************************************
** File:    binary_search_tree.h
** Project: CSCE 221 Lab 4 Spring 2022
** Author:  Naimur Rahman
** Date:    03/21/2022
** Section: 511
** E-mail:  naimurrah01@tamu.edu
** Description: Implementation for BinarySearchTree class
**/
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>

using std::cout, std::endl;

template <typename Comparable>
class BinarySearchTree {
private:
    // Node Struct for tree
    struct Node {
        Comparable data;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* root; // pointer to root of tree
    
    //-------------------------------------------------------
    // Name: find_min_ptr(Node*& n)
    // PreCondition:  Node n passed by reference
    // PostCondition: returns node pointer of node with minimum value of tree with root n recursively
    //---------------------------------------------------------
    Node* find_min_ptr(Node*& n) const {
        if (n == nullptr) {
            return nullptr;
        }
        if (n->left == nullptr) {
            return n;
        }
        return find_min_ptr(n->left);
    }

    // remove() helper

    //-------------------------------------------------------
    // Name: deleteFromTree(const Comparable& value, Node*& p)
    // PreCondition:  Comparable value and avlNode p passed as parameters
    // PostCondition: removes item with value as data at tree root p through recursion
    //---------------------------------------------------------
    void deleteFromTree(const Comparable& value, Node*& p) {
        if (p == nullptr) {
            return;
        }

        if (value < p->data) { // go to left branch
            deleteFromTree(value, p->left);
        }
        else if (p->data < value) { // go to right branch
            deleteFromTree(value, p->right);
        }
        else if (p->left != nullptr && p->right != nullptr) { // node has no children
            p->data = find_min_ptr(p->right)->data;
            deleteFromTree(p->data, p->right);
        }
        else { // at least one or more has children
            Node *oldNode = p;
            p = (p->left != nullptr) ? p->left : p->right; // p = p->left is p->left is not a nullptr else p = p->right
            delete oldNode;
        }
    }

    // destructor helper

    //-------------------------------------------------------
    // Name: destroy(Node*& p)
    // PreCondition:  root node p given
    // PostCondition: Deletes node p and its children recursively
    //---------------------------------------------------------
    void destroy(Node*& p) {
        if (p != nullptr) {
            destroy(p->left);
            destroy(p->right);
            delete p;
        }
        return;
    }

    // copy constructor and assignment operator helper

    //-------------------------------------------------------
    // Name: copyNode(Node* n)
    // PreCondition:  root node n given
    // PostCondition: Deep copys root node n and children recursively and returns a copy of node n connected to its children
    //---------------------------------------------------------
    Node* copyNode(Node* n) { // helper
        Node* c = new Node;
        c->data = n->data;
        if (n->left != nullptr) { // copy left child
            c->left = copyNode(n->left);
        }
        if (n->right != nullptr) { // copy right child
            c->right = copyNode(n->right);
        }
        return c;
    }

    // print_tree() helper

    //-------------------------------------------------------
    // Name: printTreeLine(Node* p, int space, std::ostream& os=std::cout)
    // PreCondition:  root Node p given with value for space, and an ostream os that defaults to cout
    // PostCondition: recursively prints tree rotated to os 90 degrees from root node p
    //---------------------------------------------------------
    void printTreeLine(Node* p, int space, std::ostream& os=std::cout) const {
        if (p == nullptr) {
            return;
        }
        space++; // number of levels 
        printTreeLine(p->right, space, os);
        for (int i = 1; i < space; i++) {
            os << "  "; // adds number of spaces
        }
        os << p->data << endl;
        printTreeLine(p->left, space, os);
        return;
    }

public:
    // constructors 

    //-------------------------------------------------------
    // Name: BinarySearchTree()
    // PreCondition: none
    // PostCondition: creates new BinarySearchTree object and sets root to nullptr
    //---------------------------------------------------------
    BinarySearchTree():root(nullptr) {}

    //-------------------------------------------------------
    // Name: BinarySearchTree(const BinarySearchTree& other)
    // PreCondition: BinarySearchTree other passed by reference
    // PostCondition: creates new object BinarySearchTree that is a deep copy of other
    //---------------------------------------------------------
    BinarySearchTree(const BinarySearchTree& other) {
        this->root = copyNode(other.root);
    }

    // destructor

    //-------------------------------------------------------
    // Name: ~BinarySearchTree()
    // PreCondition: BinarySearchTree object has already been created
    // PostCondition: destroys all nodes and root of BinarySearchTree object and sets root to nullptr
    //---------------------------------------------------------

    ~BinarySearchTree() {
        destroy(this->root);
        this->root = nullptr;
    }

    // assignment operator

    //-------------------------------------------------------
    // Name: operator=(const BinarySearchTree& other)
    // PreCondition: BinarySearchTree other passed by reference
    // PostCondition: return copy of other, having changed this object 
    //---------------------------------------------------------
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) { // checking not the same object
            if (this->root != nullptr) { // emptying object if not empty
                destroy(this->root);
                this->root = nullptr;
            }
            this->root = copyNode(other.root);
        }
        return *this;
    }

    //-------------------------------------------------------
    // Name: contains(const Comparable& value)
    // PreCondition: Comparable value passed by reference
    // PostCondition: return true if value is a node in the tree, false if not
    //---------------------------------------------------------
    bool contains(const Comparable& value) const {
        if (is_empty()) { // tree has no nodes = automatically false
            return false;
        }

        Node* current = this->root;

        while (current != nullptr) { // traverse tree
            if (current->data == value) { // nodes data is value
                return true;
            }
            else if (current->data > value) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        // if gets out of loop, that means value is not in tree
        return false;
    }

    //-------------------------------------------------------
    // Name: insert(const Comparable& value)
    // PreCondition: Comparable value passed by reference
    // PostCondition: creates a node with value as its data and puts it into tree
    //---------------------------------------------------------
    void insert(const Comparable& value) {
        if (contains(value)) { // value in tree already
            return;
        }

        Node* item = new Node;
        item->data = value;

        Node* current;
        Node* trailCurrent;
        
        if (this->root == nullptr) { // tree is empty, becomes root
            this->root = item;
            return;
        }

        current = this->root;
        while (current != nullptr) {
            trailCurrent = current; // parent of current

            if (current->data > value) { // shift to left
                current = current->left;
            }
            else { // shift to right
                current = current->right;
            }
        }

        if (trailCurrent->data > value) { // add to left child
            trailCurrent->left = item;
        }
        else { // add to right child
            trailCurrent->right = item;
        }
    }

    //-------------------------------------------------------
    // Name: remove(const Comparable& value)
    // PreCondition: Comparable value passed by reference
    // PostCondition: removes a node with value from tree
    //---------------------------------------------------------
    void remove(const Comparable& value) {
        deleteFromTree(value, this->root);
    }

    //-------------------------------------------------------
    // Name: find_min()
    // PreCondition: root is not a nullptr
    // PostCondition: returns the Comparable data of the minimum value node in the tree
    //---------------------------------------------------------
    const Comparable& find_min() const {
        if (is_empty()) {
            throw std::invalid_argument("Tree is Empty");
        }
        Node* current = this->root;
        while (current->left != nullptr) { // shifts to leftmost child
            current = current->left;
        }
        return current->data;
    }

    //-------------------------------------------------------
    // Name: find_max()
    // PreCondition: root is not a nullptr
    // PostCondition: returns the data of the maximum value node in the tree
    //---------------------------------------------------------
    const Comparable& find_max() const {
        if (is_empty()) {
            throw std::invalid_argument("Tree is Empty");
        }
        Node* current = this->root;
        while (current->right != nullptr) { // shifts to right most child
            current = current->right;
        }
        return current->data;
    }

    //-------------------------------------------------------
    // Name: print_tree(std::ostream& os=std::cout)
    // PreCondition: ostream os defaults to cout if none given
    // PostCondition: prints 90 degree rotated tree to os
    //---------------------------------------------------------
    void print_tree(std::ostream& os=std::cout) const {
        if (!is_empty()) {
            this->printTreeLine(this->root, 0, os);
        }
        else { // empty tree
            os << "<empty>\n";
        }
    }

    //-------------------------------------------------------
    // Name: is_empty()
    // PreCondition: none
    // PostCondition: returns true if tree is empty, false if it isnt
    //---------------------------------------------------------
    bool is_empty() const {
        return (this->root == nullptr);
    }

    //-------------------------------------------------------
    // Name: make_empty()
    // PreCondition: none
    // PostCondition: destroys all nodes, including root of tree, making it empyu.
    //---------------------------------------------------------
    void make_empty() {
        destroy(this->root);
        this->root = nullptr;
    }


    // optional
    // BinarySearchTree(BinarySearchTree&& other);
    // BinarySearchTree& operator=(BinarySearchTree&& other);
    // void insert(Comparable&& value);
};

#endif
