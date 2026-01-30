// intbst.cpp
// Implements class IntBST
// Elliot Dixon, 1/29/2026

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(!root){
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(value == n->info) return false;
    else if(value > n->info){
        if(!n->right){
            Node* inserted = new Node(value);
            n->right = inserted;
            return true;
        }
        return insert(value,n->right);
    } else {
        if(!n->left){
            Node* inserted = new Node(value);
            n->left = inserted;
            return true;
        }
        return insert(value,n->left);
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    if(!root) return;
    cout << "pre-order: ";
    printPreOrder(root);
    cout << endl;
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n) return;
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    if(!root) return;
    cout << "in-order: ";
    printInOrder(root);
    cout << endl;
}
void IntBST::printInOrder(Node *n) const {
    if(!n) return;
    printInOrder(n->left);
    cout<< n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    if(!root) return;
    cout << "post-order: ";
    printPostOrder(root);
    cout << endl;
}

void IntBST::printPostOrder(Node *n) const {
    if(!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout<< n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n) return 0;
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n) return 0;
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(!n){
        return nullptr;
    }
    if(value == n->info) return n;
    else if(value > n->info){
        return getNodeFor(value,n->right);
    } else {
        return getNodeFor(value,n->left);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(getNodeFor(value,root)){
        return true;
    }
    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* valLocation = getNodeFor(value,root);
    if(!valLocation) return nullptr;
    if(valLocation->left){
        valLocation = valLocation->left;
        while(valLocation->right){
            valLocation = valLocation->right;
        }
        return valLocation;
    }
    while(valLocation && valLocation->parent){
        if(valLocation == valLocation->parent->right){
            return valLocation->parent;
        }
        valLocation = valLocation->parent;
    }
    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* result = getPredecessorNode(value);
    if(result){
        return result->info;
    }
    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* valLocation = getNodeFor(value,root);
    if(!valLocation) return nullptr;
    if(valLocation->right){
        valLocation = valLocation->right;
        while(valLocation->left){
            valLocation = valLocation->left;
        }
        return valLocation;
    }
    while(valLocation && valLocation->parent){
        if(valLocation == valLocation->parent->left){
            return valLocation->parent;
        }
        valLocation = valLocation->parent;
    }
    return nullptr;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* result = getSuccessorNode(value);
    if(result){
        return result->info;
    }
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    return false;
    Node* node = getNodeFor(value,root);
    if(!node) return false;
    if(!node->left && !node->right){
        if(node->parent){
            if(node->parent->left == node){
                node->parent->left = nullptr;
            } else {
                node->parent->right = nullptr;
            }
        }
        if (node == root) root = nullptr;
        delete node;
    } else if(!node->right){
        node->left->parent = node->parent;
        if(node->parent){
            if(node->parent->left == node){
                node->parent->left = node->left;
            } else {
                node->parent->right = node->left;
            }
        }
        if (node == root) root = node->left;
        delete node;
    } else if (!node->left){
        node->right->parent = node->parent;
        if(node->parent){
            if(node->parent->left == node){
                node->parent->left = node->right;
            } else {
                node->parent->right = node->right;
            }
        }
        if (node == root) root = node->right;
        delete node;
    } else {
        Node* pred = getPredecessorNode(value);
        if(pred->left){
            pred->left->parent = pred->parent;
            if(pred->parent->left == pred){
                pred->parent->left = pred->left;
            } else {
                pred->parent->right = pred->left;
            }
            
        } else {
            if(pred->parent->left == pred){
                pred->parent->left = nullptr;
            } else {
                pred->parent->right = nullptr;
            }
        }
        node->info = pred->info;
        delete pred;
    }
    return true;
}
