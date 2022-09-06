/*****************************************
** File:    avl_tree.h
** Project: CSCE 221 Lab 4 Spring 2022
** Author:  Naimur Rahman
** Date:    03/21/2022
** Section: 511
** E-mail:  naimurrah01@tamu.edu
** Description: Implementation for AVLTree class
**/
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstddef>
#include <iostream>
using std::cout, std::endl;

template <typename Comparable>
class AVLTree {
private:
    static const int ALLOWED_IMBALANCE = 1; // the most difference between height allowed

    // struct for nodes of AVL tree
    struct avlNode {
        Comparable data;
        avlNode *left = nullptr;
        avlNode *right = nullptr;
        int height = 0;
    };

    avlNode* root; // root of avl Tree

    // helper functions 

    //-------------------------------------------------------
    // Name: balance(avlNode*& t)
    // PreCondition:  node t given
    // PostCondition: Balances tree and heights of all nodes with root t if there is a height imbalance
    //---------------------------------------------------------
    void balance(avlNode*& t) {
        if (t == nullptr) {
            return;
        }

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) { // if difference between heights > 1
            if (height(t->left->left) >= height(t->left->right)) { // if there is a left child but not a right
                rotateWithLeftChild(t);
            }
            else { 
                doubleWithLeftChild(t);
            }
        }
        else {
            if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) { // if difference between right and left are > 1
                if (height(t->right->right) >= height(t->right->left)) { // if there is a right child and not a left
                    rotateWithRightChild(t);
                }
                else {
                    doubleWithRightChild(t);
                }
            }
        }
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    //-------------------------------------------------------
    // Name: find_min(avlNode*& n)
    // PreCondition:  node n given
    // PostCondition: returns a pointer to the node with the minimum value on the tree of root n
    //---------------------------------------------------------
    avlNode* find_min(avlNode*& n) {
        avlNode* current = n;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    //-------------------------------------------------------
    // Name: insertSub(const Comparable& x, avlNode*& t)
    // PreCondition:  Comparable x and avlNode t given
    // PostCondition: inserts item of value x at avl tree root t through recursion and balances tree
    //---------------------------------------------------------
    void insertSub(const Comparable& x, avlNode*& t) {
        if (t == nullptr) { // create node with data x
            t = new avlNode;
            t->data = x;
        }
        else if (x < t->data) { // shift left
            insertSub(x, t->left);
        }
        else if (x > t->data) { // shift right
            insertSub(x, t->right );
        }

        balance(t);
    }

    //-------------------------------------------------------
    // Name: removeSub(const Comparable& x, avlNode*& t)
    // PreCondition:  Comparable x and avlNode t given
    // PostCondition: removes item of value x at avl tree root t through recursion and balances tree
    //---------------------------------------------------------
    void removeSub(const Comparable& x, avlNode*& t) {
        if (t == nullptr) {
            return;
        }

        if (x < t->data) { // shift left
            removeSub(x, t->left);
        }
        else if (x > t->data) { // shift right
            removeSub(x, t->right);
        }
        else if (t->left != nullptr && t->right != nullptr) { // node has no children
            t->data = find_min(t->right)->data;
            removeSub(t->data, t->right);
        }
        else { // node has atleast one child
            avlNode* r = t;
            if (t->left != nullptr) {
                t = t->left;
            }
            else {
                t = t->right;
            }
            delete r;
        }
        balance(t);
    }

    // rotators - helpers for balancing

    //-------------------------------------------------------
    // Name: rotateWithLeftChild(avlNode*& k2)
    // PreCondition:  avlNode k2 passed by reference that only has a left child
    // PostCondition: shifts root k2 to the right and makes k1 its parent
    //---------------------------------------------------------
    void rotateWithLeftChild(avlNode*& k2) { 
        // right shift
        avlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    //-------------------------------------------------------
    // Name: doubleWithLeftChild(avlNode*& k3)
    // PreCondition:  avlNode k3 passed by reference that has children on both sides
    // PostCondition: double shifts root k3 and balances its children
    //---------------------------------------------------------
    void doubleWithLeftChild(avlNode*& k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    //-------------------------------------------------------
    // Name: rotateWithRightChild(avlNode*& k1)
    // PreCondition:  avlNode k1 passed by reference that has child on right side
    // PostCondition: shifts root k1 to left and makes right child its parent
    //---------------------------------------------------------
    void rotateWithRightChild(avlNode*& k1) {
        // shift right
        avlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max(height(k1->left), height(k1->right)) + 1;
        k2->height = std::max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }
    
    //-------------------------------------------------------
    // Name: doubleWithRightChild(avlNode*& k3)
    // PreCondition:  avlNode k3 passed by reference that has children on both sides
    // PostCondition: double shifts root k3 and balances its children
    //---------------------------------------------------------
    void doubleWithRightChild(avlNode*& k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    // print_tree() helper
    //-------------------------------------------------------
    // Name: printTreeLine(avlNode* p, int space, std::ostream& os=std::cout)
    // PreCondition:  root avlNode p given with value for space, and an ostream os that defaults to cout
    // PostCondition: recursively prints tree rotated to os 90 degrees from root node p
    //---------------------------------------------------------
    void printTreeLine(avlNode* p, int space, std::ostream& os=std::cout) const {
        if (p == nullptr) {
            return;
        }
        space++; // amount of levels
        printTreeLine(p->right, space, os);
        for (int i = 1; i < space; i++) {
            os << "  ";
        }
        os << p->data << endl;
        printTreeLine(p->left, space, os);
        return;
    }

    // copy constructor and assignment operator helper

    //-------------------------------------------------------
    // Name: copyTree(avlNode* p)
    // PreCondition:  root node p given
    // PostCondition: Deep copys root node p and children recursively and returns a copy of node p that has a copy of its children
    //---------------------------------------------------------
    avlNode* copyTree(avlNode* p) {
        // copying contents
        avlNode* c = new avlNode;
        c->data = p->data;
        c->height = p->height;

        // copying children
        if (p->left != nullptr) {
            c->left = copyTree(p->left);
        }
        if (p->right != nullptr) {
            c->right = copyTree(p->right);
        }
        return c;
    }

    // destructor helper

    //-------------------------------------------------------
    // Name: destroy(avlNode*& p)
    // PreCondition:  root node p given
    // PostCondition: Deletes node p and children recursively
    //---------------------------------------------------------
    void destroy(avlNode*& p) {
        if (p != nullptr) {
            destroy(p->left);
            destroy(p->right);
            delete p;
        }
        return;
    }
    
    // helper for balance and rotations

    //-------------------------------------------------------
    // Name: height(avlNode* t)
    // PreCondition:  node t given
    // PostCondition: returns int height of node t
    //---------------------------------------------------------
    int height(avlNode* t) {
        if (t == nullptr) {
            return -1;
        }
        else {
            return t->height;
        }
    }

public:
    // constructors 

    //-------------------------------------------------------
    // Name: AVLTree()
    // PreCondition: none
    // PostCondition: creates new AVLTree object and sets root to nullptr
    //---------------------------------------------------------
    AVLTree() {
        this->root = nullptr;
    }

    //-------------------------------------------------------
    // Name: AVLTree(const AVLTree& other)
    // PreCondition: AVLTree other passed by reference
    // PostCondition: creates new object AVLTree that is a copy of other
    //---------------------------------------------------------
    AVLTree(const AVLTree& other) {
        this->root = copyTree(other.root);
    }

    // destructor

    //-------------------------------------------------------
    // Name: ~AVLTree()
    // PreCondition: AVLTree object has already been created
    // PostCondition: destroys all nodes and root of AVLTree object and sets root to nullptr
    //---------------------------------------------------------
    ~AVLTree() {
        destroy(this->root);
        this->root = nullptr;
    }

    // assignment operator

    //-------------------------------------------------------
    // Name: operator=(const AVLTree& other)
    // PreCondition: AVLTree other passed by reference
    // PostCondition: return copy of other, having changed this object 
    //---------------------------------------------------------
    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) { // if not same object
            if (!is_empty()) {
                destroy(this->root);
                this->root = nullptr;
            }
            this->root = copyTree(other.root);
        }
        return *this;
    }

    //-------------------------------------------------------
    // Name: contains(const Comparable& value)
    // PreCondition: Comparable value passed by reference
    // PostCondition: return true if value is a node in the tree, false if not
    //---------------------------------------------------------
    bool contains(const Comparable& value) const {
        if (is_empty()) { // empty tree
            return false;
        }

        avlNode* current = this->root;

        while (current != nullptr) {
            if (current->data == value) { // value in tree
                return true;
            }
            else if (current->data > value) { // shift left
                current = current->left;
            }
            else { // shift right
                current = current->right;
            }
        }

        // not in tree
        return false;
    }

    //-------------------------------------------------------
    // Name: insert(const Comparable& value)
    // PreCondition: Comparable value passed by reference
    // PostCondition: creates a node with value as its data and puts it into tree, balancing it as well
    //---------------------------------------------------------
    void insert(const Comparable& value) {
        insertSub(value, this->root);
    }

    //-------------------------------------------------------
    // Name: remove(const Comparable& value)
    // PreCondition: Comparable value passed by reference
    // PostCondition: remove a node with value and balances the tree
    //---------------------------------------------------------
    void remove(const Comparable& value) {
        removeSub(value, this->root);
    }

    //-------------------------------------------------------
    // Name: find_min()
    // PreCondition: root is not a nullptr
    // PostCondition: returns the Comparable data of the minimum value node in the tree
    //---------------------------------------------------------
    const Comparable& find_min() const {
        if (this->root == nullptr) {
            throw std::invalid_argument("AVLTree is empty");
        }

        avlNode* current = this->root;
        while (current->left != nullptr) { // get to leftmost node
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
        if (this->root == nullptr) {
            throw std::invalid_argument("AVLTree is empty");
        }
        avlNode* current = this->root;
        while (current->right != nullptr) { // get to rightmost node
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
    bool is_empty() const { return (this->root == nullptr); }

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
    // AVLTree(AVLTree&& other);
    // AVLTree& operator=(AVLTree&& other);
    // void insert(Comparable&& value);
};

#endif
