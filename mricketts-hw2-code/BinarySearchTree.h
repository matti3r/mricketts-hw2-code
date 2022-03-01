#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>

#include "Stack.h"
using namespace std;

struct Employee {
    int id;
    int age;
    string name;
    int level;

    Employee(int id = -1, int age = -1, string name = "", int level = -1)
        : id{ id }, age{ age }, name{ name }, level{ level } { }

};

class BinarySearchTree
{

public:

    struct BinaryNode
    {
        Employee element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Employee& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ theElement }, left{ lt }, right{ rt } { }

        BinaryNode(Employee&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } { }

        BinaryNode() {}
    };

    BinarySearchTree() : root{ nullptr }
    {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Find the smallest item in the tree.
     * return default employee if empty
     */
    const Employee& findMin() const
    {
        BinaryNode* retNode = findMin(root);
        if (retNode == nullptr)
            return Employee();
        else
            return retNode->element;
    }

    /**
     * Find the largest item in the tree.
     * return default employee if empty
     */
    const Employee& findMax() const
    {
        BinaryNode* retNode = findMax(root);
        if (retNode == nullptr)
            return Employee();
        else
            return retNode->element;
    }

    /**
     * Prints employee info if id found in tree
     */
    bool find(const int id) const
    {
        return find(id,root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Employee& x)
    {
        insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const int id)
    {
        remove(id, root);
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void report() const
    {

        // Return if nothing to print
        if (isEmpty()) {
            cout << "Tree is empty";
            return;
        }

        // In order traversal - Use stack
        Stack<BinaryNode *> stack;
        BinaryNode* t = root;

        // Stack and counter for keeping track of level
        Stack<int> levelStack;
        int level = 0;

        // Print formatting
        int idWidth = 10;
        int levelWidth = 8;

        cout << left << setw(idWidth) << "ID:";
        cout << left << setw(levelWidth) << "Level:";
        cout << endl;

        while (t != nullptr || stack.isEmpty() == false) {
            
            // Stack all element on the way to the smallest element (all the way left)
            // Also add to stack if t->right from bottom is an element
            while (t != nullptr) {
                stack.push(t);
                t = t->left;
                level++;
                levelStack.push(level);
            }

            // t is currently null pointer, set to top of stack
            t = stack.pop();
            level = levelStack.top();
            int levelToPrint = levelStack.pop();

            // Print ID and level
            cout << left << setw(idWidth) << t->element.id;
            cout << left << setw(levelWidth) << levelToPrint;
            cout << endl;


            t = t->right;
        }   
        
         
    }

private:

    BinaryNode* root;
    int size;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Employee& x, BinaryNode*& t)
    {
        // Create the new node to insert with the new employee object
        BinaryNode* nodeToInsert = new BinaryNode(x,nullptr,nullptr);

        // Pointers to find where to insert
        BinaryNode* curr = t;
        BinaryNode* prev = nullptr;
        int level = 1;

        // Search for the element to insert it as a child
        while (curr != nullptr) {
            prev = curr;
            if (x.id < curr->element.id)
                curr = curr->left;
            else
                curr = curr->right;
            level++;
        }

        nodeToInsert->element.level = level;

        // Insert either above or below the node given BST properties
        // Right = larger, Left = smaller
        if (prev == nullptr) {
            prev = nodeToInsert;
            root = prev;
        } else if (x.id < prev->element.id)
            prev->left = nodeToInsert;
        else
            prev->right = nodeToInsert;


        // Increment Size
        size++;

    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const int id, BinaryNode*& t)
    {
        BinaryNode* prev = nullptr;
        BinaryNode* curr = t;
        
        // Search for the element
        while (curr != nullptr && curr->element.id != id) {
            prev = curr;
            if (id < curr->element.id)
                curr = curr->left;
            else
                curr = curr->right;
        }

        // If the element is not in the tree, return
        if (curr == nullptr) {
            return;

        // Else if the element has only one child
        } else if (curr->left == nullptr || curr->right == nullptr) { 
            BinaryNode* replacementNode;

            // Find which node to put in place of the removed node
            if (curr->left == nullptr)
                replacementNode = curr->right;
            else
                replacementNode = curr->left;

            // If the node is the root
            if (prev == nullptr)
                root = replacementNode;
            else if (curr == prev->left)
                prev->left = replacementNode;
            else
                prev->right = replacementNode;

            delete curr;

        // Else the element has 2 children
        } else { 
            
            BinaryNode* temp = curr->right;
            prev = nullptr;

            // Find the predecessor to put in place of the removed node
            while (temp->left != nullptr) {
                prev = temp;
                temp = temp->left;
            }

            // Rearrange pointers as needed to remove node
            if (prev != nullptr)
                prev->left = temp->right;
            else
                curr->right = temp->right;

            curr->element = temp->element;

            delete temp;
        }
       
        size--;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode* findMin(BinaryNode* t) const
    {
        BinaryNode* curr = t;
        if (curr != nullptr)
            
            // Min is all the way to the left
            while (curr->left != nullptr)
                curr = curr->left;
        return curr;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode* findMax(BinaryNode* t) const
    {
        BinaryNode* curr = t;
        if (curr != nullptr)

            // Max is all the way to the right
            while (curr->right != nullptr && curr != nullptr)
                curr = curr->right;
        return curr;
    }


    /**
     * id is item to search for.
     * t is the node that roots the subtree.
     */
    bool find(const int id, BinaryNode* t) const
    {
        // Traverse tree to find the element given BST properties
        // Right = larger, Left = smaller
        while (t != nullptr && t->element.id != id) {
            if (id < t->element.id)
                t = t->left;
            else
                t = t->right;
        }

        // Print the found element
        if (t == nullptr) { 
            cout << "ID not found";
            return false;
        } else {
            cout << "Found. Name: " << t->element.name <<", Age:" << t->element.age;
            return true;
        }
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(BinaryNode*& t)
    {

        // Find the minimum and remove it, repeat until tree is empty
        int min = findMin().id;
        while (min != -1) {
            min = findMin().id;
            remove(min);
        }

        // Set tree size back to 0
        size = 0;
    }
};

#endif /* BINARY_SEARCH_TREE_H */
