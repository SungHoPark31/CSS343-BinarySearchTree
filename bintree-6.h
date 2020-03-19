 /*-------------- bintree.h -------------------
 Sung Ho Park
 1/25/2020
 -------------------------------------------------
 Purpose - This is the bintree header class. Implementation
 is in the cpp file, but this class declares every function
 that'll be implemented in the cpp file and some private
 functions.
 --------------------------------------------------
 Had to use <iostream> and <string> for basic necessity.
 cout's and strings. <fstream> is used for txt file io.
 --------------------------------------------------*/

#ifndef bintree_h
#define bintree_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "nodedata.h"

using namespace std;

class BinTree
{
    // you add class method comments and assumptions...
    friend ostream& operator<<(ostream &output, const BinTree &tree);
    
public:
    // constructor
    BinTree();
    
    // copy constructor
    BinTree(const BinTree &);
    
    // destructor, calls makeEmpty
    ~BinTree();
    
    // true if tree is empty, otherwise false
    bool isEmpty() const;
    
    // make the tree empty so isEmpty returns true
    void makeEmpty();
    
    //Operator Overload
    BinTree& operator=(const BinTree &);
    bool operator==(const BinTree &other) const;
    bool operator!=(const BinTree &other) const;
    
    //Insert to the Tree
    bool insert(NodeData* insertNode);
    
    //Retrieve
    bool retrieve(const NodeData &getData,
                    NodeData* &getObject) const;
    
    //Get the height of a specific node.
    int getHeight(const NodeData &root) const;
    
    // provided below, displays the tree sideways...
    void displaySideways() const;
    
    void bstreeToArray(NodeData* array[]);
    void arrayToBSTree(NodeData* array[]);
    
private:
    struct Node
    {
        //Pointer to the data object
        NodeData* data = nullptr;
        
        //Left subtree pointer
        Node* left = nullptr;
        //Right subtree pointer
        Node* right = nullptr;
        
        //Destructor for Node
        ~Node()
        {
            left = nullptr;
            delete left;
            right = nullptr;
            delete right;
            data = nullptr;
            delete data;
        }
    };

    //Root of the tree
    Node* root = nullptr;
    
    //Method in case a new node needs to be made.
    
    // utility functions
    void inorderHelper( ... ) const;
    void sideways(Node*, int) const;
    
    //Here are some helper functions for the public functions.
    //The reason why there are a lot of helper functions is
    //because these public functions cannot be solved using
    //recursion. SO, having private helper functions enable
    //the entire program to be solvable recursively.
    
    //Helper function that copies the tree recursively.
    Node* copyHelper( Node* other);
    //void copyHelper(Node* copyRoot, Node *other);
    
    //Helper method to recursively destroy the tree
    void destroy(Node* thisRoot);
    
    //Helper method for insert
    bool insertHelper(Node* thisRoot, NodeData* insertNode);
    
    bool retrieveHelper(Node* thisRoot,const NodeData &other,
                            NodeData* &otherData) const;
    
    //Helper method for get height.
    int getHeightHelper(Node *root,
                        const NodeData &node,  bool &found) const;
    
    //Prints in order
    void inOrder(Node* root) const;
    
    //Gets the height of a node.
    int depth(Node* root) const;
    
    //Helper for finding comparison operator. 
    bool equalsHelper(Node* root, Node* other, bool &match) const;
    
    //Helper for BSTree to Array
    void bstreeToArrayHelper(NodeData* array[],
                             Node* root, int &size);
    
    //Helper for array to BSTree
    void arrayToTreeHelper(NodeData* array[],
                           int &left, int &right);
    int sizeOfArray;
    int size;
};

#endif /* nodedata_h */
