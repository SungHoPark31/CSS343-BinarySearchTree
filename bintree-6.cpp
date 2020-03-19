 /*-------------- bintree.cpp -------------------
 Sung Ho Park
 1/25/2020
 2/1/2020
 -------------------------------------------------
 Purpose - This is the bintree class. This file creates the
 binary search tree and inserts data from the nodeData class.
 It also retrieves objects from the nodeData, and prints the data
 in order/
 --------------------------------------------------
 Had to use <iostream> and <string> for basic necessity.
 cout's and strings. <assert.h> for debug.
 <vector> is used to create an array.
 --------------------------------------------------*/

#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <cmath>
#include <vector>
#include "bintree.h"
#include "nodedata.h"

using namespace std;

/*------------------------- BinTree ---------------------------------
 Description:
 Default Constructor that creates an empty tree.
 
 Precondition: None
 Postcondition: Creates an empty tree
 -----------------------------------------------------------------*/
BinTree::BinTree()
{
    //Create an empty tree. Everything inside of
    //root is initialized to null.
    root = new Node();
}
//End of default constructor

/*------------------Copy constructor ---------------------------
 Description:
 Copy Constructor that copies another tree with this one.

 Precondition: The parameter that is passed in is an existing
 object.
 Postcondition: Performs a deep copy of the other tree to
 this tree.
-------------------------------------------------------------*/
BinTree::BinTree(const BinTree &other)
{
    //Copy everything over to this tree.
    root = copyHelper(other.root);
}
//End of Copy constructor

/*------------------Destructor---------------------------
 Description:
 Destroys the tree.

 Precondition: None
 Postcondition: Destroys all nodes in the tree and the tree.
--------------------------------------------------------*/
BinTree::~BinTree()
{
    //call destroy to completely destroy all the root.
    destroy(root);
    delete root;
}
//End of Destructor

/*--------------------isEmpty-------------------------
 Description:
 Checks if the tree is empty

 Precondition: None
 Postcondition: Returns true if the tree is empty, false
 if not.
--------------------------------------------------------*/
bool BinTree::isEmpty() const
{
    //If the root is null, then it is empty.
    if(root->data == nullptr)
    {
        return true;
    }
    else
    {
        //Otherwise, it is not, so it is false
        return false;
    }
}
//End of isEmpty

/*---------------------makeEmpty------------------------
 Description:
 Makes the tree empty.

 Precondition: None
 Postcondition: Destroys all nodes in the tree and the tree.
 Helper for the destructor. 
--------------------------------------------------------*/
void BinTree::makeEmpty()
{
    //Destroy everything but the root.
    destroy(root);
    
    //Since it is completely destroyed, make a new root
    //and set it to null to make it empty.
    root->left = nullptr;
    root->right = nullptr;
    root->data = nullptr;
}
//End of makeEmpty

/*---------------------destroy------------------------
 Description:
 Destroys the tree.

 Precondition: The Node that is being passed in exists.
 Postcondition: Destroys all nodes in the tree and the tree.
 Helper for the destructor and make Empty.
--------------------------------------------------------*/
void BinTree::destroy(Node* thisRoot)
{
    //If thisRoot is not nullptr.
    if(thisRoot)
    {
        //Go left and right
        destroy(thisRoot->left);
        destroy(thisRoot->right);
        
        //delete the root
        if(thisRoot != root)
        {
            delete thisRoot;
        }
    }
    else
    {
        //If the root is a nullptr, then exit.
        return;
    }
}
//End of destroy

/*------------------operator=---------------------------
 Description:
 Basically a Copy Constructor that copies another tree
 with this one. Except that it uses the assignment operator

 Precondition: The parameter that is passed in is an existing
 object.
 Postcondition: Performs a deep copy of the other tree to
 this tree.
-------------------------------------------------------------*/
BinTree& BinTree::operator=(const BinTree &other)
{
    //If the other is null, then make this null.
    if(other.root == nullptr)
    {
        root = nullptr;
    }
    //If the trees are the same, then don't really do anything
    //Just return this.
    else if(this == &other)
    {
        return *this;
    }
    else
    {
        //Empty the tree down to one root.
        makeEmpty();
        //Perform the deep copy recursively.
        root = copyHelper( other.root);
    }
    //Return this.
    return *this;
}
//End of operator=

/*------------------copyHelper---------------------------
 Description:
 Basically a Copy Constructor that copies another tree
 with this one. This is a helper method that copies the tree
 recursively.

 Precondition: The both parameter that is passed in is an existing
 object. Node and BinTree
 Postcondition: Performs a deep copy of the other tree to
 this tree.
-------------------------------------------------------------*/
BinTree::Node* BinTree::copyHelper( Node *other)
{
    //This will return the copy of the root, therefore returning the
    //tree. Create a temp variable.
    Node *copyRoot = nullptr;
    //Base case: If the other is eventually null, make this root
    //null.
    if(other == nullptr)
    {
        //make the copyRoot null
        copyRoot = nullptr;
    }
    else //if(copyRoot == nullptr)
    {
        copyRoot = new Node();
        copyRoot->data = other->data;
        
        //Go left and right and keep copying.
        copyRoot->left = copyHelper(other->left);
        copyRoot->right = copyHelper(other->right);
    }
    return copyRoot;
}
//End of copyHelper

/*------------------operator==---------------------------
 Description:
 Checks if one tree is the same as another.

 Precondition: The parameter that is passed in is an existing
 object.
 Postcondition: Returns true if the two trees are the same.
 False otherwise.
-------------------------------------------------------------*/
bool BinTree::operator==(const BinTree &other) const
{
    //Have a boolean to keep track of the tree. If it is false
    //anywhere, it'll return false.
    bool match = false;
    return equalsHelper(root, other.root, match);
}
//End of == operator

/*------------------operator==---------------------------
 Description:
 Checks if one tree is the same as another. This is a helper
 for both the == and the !=. For the == operator, anytime
 where the tree differs in anyway, returns false.

 Precondition: The parameter that is passed in is an existing
 object.
 Postcondition: Returns true if the two trees are the same.
 False otherwise.
-------------------------------------------------------------*/
bool BinTree::equalsHelper(Node* root, Node* other, bool &match) const
{
    //If both of them are empty, then return true.
    if(root == nullptr && other == nullptr)
    {
        match = true;
    }
    //If one of the roots is a nullptr, still return true because
    //we went through the tree.
    else if(root == nullptr && other != nullptr)
    {
        match = true;
    }
    else if(root != nullptr && other == nullptr)
    {
        match = true;
    }
    else
    {
        //If it is equal, then keep going.
        if(*root->data == *other->data)
        {
            equalsHelper(root->left, root->left, match);
            equalsHelper(root->right, root->right, match);
        }
        else
        {
            //If it is not, then just stop everything.
            match = false;
        }
    }
    //Return the result. If it manages to go through the
    //entire test, then it is a successful operator==.
    //If not, then it'll return false.
    return match;
}
//end of equalsHelper

/*------------------operator==---------------------------
 Description:
 Checks if one tree is not the same as another.

 Precondition: The parameter that is passed in is an existing
 object.
 Postcondition: Returns true if the two trees are not the same.
 False otherwise.
-------------------------------------------------------------*/
bool BinTree::operator!=(const BinTree &other) const
{
    //If they are the same, then return false.
    bool match = false;
    if(equalsHelper(root, other.root, match) == true)
    {
        return false;
    }
    else
    {
        //If there is one problem with the equals helper, then
        //it is not equal, therefore return true.
        return true;
    }
}
//End of != operator

/*----------------------insert----------------------------
 Description:
 Insert the node into the tree.

 Precondition: There is a node object.
 Postcondition: Returns true if insert is successful.
 False if not. 
-------------------------------------------------------*/
bool BinTree::insert(NodeData* insertNode)
{
    //Call the helper function.
    return insertHelper(root, insertNode);
}
//End of insert

/*----------------------insert----------------------------
 Description:
 Insert the node into the tree. Helper function inserts
 to the tree recursively.

 Precondition: There is an existing object for Node and
 Nodedata.
 Postcondition: Returns true if insert is successful.
 False if not.
-------------------------------------------------------*/
bool BinTree::insertHelper(Node* thisRoot, NodeData* insertNode)
{
    //If the root is null, or it is an empty tree,
    //insert it.

    if(thisRoot->data == nullptr)
    {
        //Set the datas
        thisRoot->data = insertNode;
        thisRoot->left = nullptr;
        thisRoot->right = nullptr;
        
        //This is a successful insert.
        return true;
    }
    else if(*(thisRoot->data) == *(insertNode))
    {
        //If they are the same, then return false because
        //no duplicates.
        return false;
    }
    //If the data root is greater than the insertNode, go left.
    //Dereference because you don't want to compare their references.
    else if(*thisRoot->data > *insertNode)
    {
        //If the left is nullptr...
        if(thisRoot->left == nullptr)
        {
            //Make a new Node
            Node* newNode = new Node;
            
            //Set that new Node to the left
            thisRoot->left = newNode;
            
            //Go left
            return insertHelper(thisRoot->left, insertNode);
        }
        else
        {
            //Go left
            return insertHelper(thisRoot->left, insertNode);
        }
    }
    //Otherwise, go right.
    else if(*thisRoot->data < *insertNode)
    {
        //If the right is nullptr...
        if(thisRoot->right == nullptr)
        {
            //Make a new Node
            Node* newNode = new Node;
            
            //Set that new Node to the right
            thisRoot->right = newNode;
            
            //Go right
            return insertHelper(thisRoot->right, insertNode);
        }
        else
        {
            //Go right
            return insertHelper(thisRoot->right, insertNode);
        }
    }
    return false;
}
//End of insertHelper.

/*----------------------retrieve----------------------------
 Description:
 gets the NodeData* of a given object in the tree and to
 report whether the object is found.

 Precondition: There is an existing object for Node and
 Nodedata.
 Postcondition: Returns true if you found the data.
 False if not.
-------------------------------------------------------*/
bool BinTree::retrieve(const NodeData &other, NodeData* &otherData) const
{
    //Uses the helper method to retrieve.
    if(retrieveHelper(root, other, otherData) == true)
    {
        return true;
    }
    else
    {
        //If not set the item to nullptr.
        otherData = nullptr;
        return false;
    }
}
//End of retrieve

/*-------------------retrieveHelper------------------------
 Description:
 Helper function for the retrieve function.

 Precondition: There is an existing object for Node and
 Nodedata and this BinTree object exists
 Postcondition: Returns true if you found the data.
 False if not.
-------------------------------------------------------*/
bool BinTree::retrieveHelper(Node* thisRoot, const NodeData &other,
                                        NodeData* &otherData) const
{
    //Base Case: If the root is null...
    if(thisRoot == nullptr)
    {
        //Return false. Or if it is not found.
        return false;
    }
    //If the data is found...
    else if(*thisRoot->data == other)
    {
        //Set the this Data to otherData and return true.
        otherData = thisRoot->data;
        return true;
    }
    //If the the data is greater than the value passed in,
    else if(*thisRoot->data > other)
    {
        //Go left
        return retrieveHelper(thisRoot->left, other, otherData);
    }
    //If the the data is less than the value passed in,
    else if(*thisRoot->data < other)
    {
        //Go right
        return retrieveHelper(thisRoot->right, other, otherData);
    }
    //Rare case, but needed if not found.
    return false;
}
//End of retrieveHelper

/*----------------------getHeight----------------------------
 Description:
 Gets the height of the node that is being passed in.

 Precondition: There is an existing node object.
 Postcondition: Returns the where in the tree the node is
 located in.
------------------------------------------------------------*/
int BinTree::getHeight(const NodeData &node) const
{
    //Call the helper function.
    bool found = false;
    return getHeightHelper(root, node, found);
}
//End of getHeight

/*-------------------getHeightHelper---------------------
 Description:
 Gets the height of the node that is being passed in. This
 method solves this problem recursively.

 Precondition: There is an existing node object and this
 binTree object is existing.
 Postcondition: Returns the where in the tree the node is
 located.
---------------------------------------------------------*/
int BinTree::getHeightHelper(Node *thisRoot, const NodeData &node,
                                                    bool &found) const
{
    //Have a temporary left and right.
    int left;
    int right;
    
    //If the head is null, then return 0.
    if(thisRoot == nullptr)
    {
        return 0;
    }
    //If you found it...
    else if(*thisRoot->data == node)
    {
        //Retrieve the data from it for the boolean.
        NodeData *objectFound;
        found = retrieve(node, objectFound);
        
        //If it is found, then call the helper
        if(found == true)
        {
            //recurse and return the height of the found node.
            return depth(thisRoot);
        }
    }
    //If you cannot find it, recurse through until you find it.
    else
    {
        //If the left is not a null pointer...
        if(thisRoot->left != nullptr)
        {
            //... go left.
            left = getHeightHelper(thisRoot->left, node, found);
            
            //If you found is true, from the recursion, then return that
            //number that you got from the left.
            if(found == true)
            {
                return left;
            }
        }
        if(thisRoot->right != nullptr)
        {
            //Otherwise, go right and return the number you
            //got from the recursion.
            right = getHeightHelper(thisRoot->right, node, found);
            if(found == true)
            {
                return right;
            }
        }
        //If you can't find it, return 0.
        return 0;
    }
    //Return 0 as a rare case.
    return 0;
}
//End of getheightHelper.

/*-------------------depth---------------------
 Description:
 Gets the height of the specific object from the tree.

 Precondition: There is an existing node object and this
 binTree object is existing.
 Postcondition: Returns the where in the tree the node is
 located.
---------------------------------------------------------*/
int BinTree::depth(Node* thisRoot) const
{
    //Have a temporary left and right.
    int left;
    int right;
    
    //If the root is null, then stop the recursion and return 0.
     if(thisRoot == nullptr)
    {
        //Return 0
        return 0;
    }
    //Else if, you have a root and the left and right are
    //nullptr, so if it is a leaf, return 1
    else if(thisRoot->left == nullptr &&
                            thisRoot->right == nullptr)
    {
        return 1;
    }
    else
    {
        //Recurse left and right and save the values for return.
        left = depth(thisRoot->left);
        right = depth(thisRoot->right);
        
        //Find the largest
        return 1 + max(left, right);
    }
    //This is just in case this whole function doesn't work.
    return 0;
}
//End of depth.

/*------------------bstreeToArray-----------------------
 Description:
 Puts all the nodes in the tree inside the array in order.
 
 Precondition: There is an existing array that carries
 NodeData
 Postcondition: Successfully puts all the contents in the tree
 to an array in order. 
---------------------------------------------------------*/
void BinTree::bstreeToArray(NodeData* array[])
{
    //This is foe the current size of the array.
    int theSize = 0;
    
    //Put the nodes in the array in order and increment
    //the size.
    bstreeToArrayHelper(array, root, theSize);
    
    sizeOfArray = theSize;
    //Empty the tree
    makeEmpty();
}
//End of bstreeToArray

/*------------------bstreeToArrayHelper-------------------
 Description:
 Puts all the nodes in the tree inside the array in order.
 This is the helper for bstreetoArray.

 Precondition: There is an existing root, array and size is
 a real number.
 Postcondition: Successfully puts all the contents in the tree
 to a array.
---------------------------------------------------------*/
void BinTree::bstreeToArrayHelper(NodeData* array[],
                                  Node* thisRoot, int &size)
{
    //If the root is nullptr, then just return
    if (thisRoot == nullptr)
    {
        return;
    }
    //In order: left, root, right. Push back the array
    //in order
    bstreeToArrayHelper(array, thisRoot->left, size);
    
    //Since this is a inorder, check if the correct spot is NULL
    while(array[size] != NULL)
    {
        //If it is not then increment size until array[size] is
        //NULL.
        size++;
    }
    //Once you found NULL, then put the data inside the array at
    //that spot.
    array[size] = thisRoot->data;
    
    //Recurse right.
    bstreeToArrayHelper(array, thisRoot->right, size);
}
//End of BSTree to Array Helper


/*------------------arrayToBSTree-------------------
 Description:
 Puts all the elements in the array inside of bstree, starting
 with (left + right) / 2.

 Precondition: There is an existing array passed in
 Postcondition: Successfully puts all the contents in the array
 into the tree.
---------------------------------------------------------*/
void BinTree::arrayToBSTree(NodeData* array[])
{
    //Have the first and the last index because it is
    //needed to cut the array in half.
    int left = 0;
    int right = sizeOfArray;
    
    //Call the function.
    arrayToTreeHelper(array, left, right);
    
    //Since the array is empty, return 0.
    sizeOfArray = 0;
}
//End of arrayToBSTree.

/*------------------arrayToBSTree-------------------
 Description:
 Puts all the elements in the array inside of bstree, starting
 with (left + right) / 2. Helper for arrayToBSTree.

 Precondition: There is an existing array passed in
 Postcondition: Successfully puts all the contents in the array
 into the tree.
---------------------------------------------------------*/
void BinTree::arrayToTreeHelper(NodeData* array[],
                                int &left, int &right)
{
    //If left is greater than right...
    if(left > right)
    {
        //do nothing.
        return;
    }
    else
    {
        //Have a mid index.
        int mid = (left + right) / 2;
        
        //Since you are cutting the array in half,
        //Have a point before the mid, if you are going left,
        //And have a point after the mid, if you're going right.
        int endOfFirstHalf = mid - 1;
        int beginningOfSecondHalf = mid + 1;
        
        //Insert the middle value into the tree.
        insert(array[mid]);
        
        //If it is successful, then set that data in the array to null.
        array[mid] = NULL;
        
        //Recurse left and right. 
        arrayToTreeHelper(array, left, endOfFirstHalf);
        arrayToTreeHelper(array, beginningOfSecondHalf, right);
    }
}
//End of arrayToBSTree


/*-------------- displaySideways ----------------
 Displays a binary tree as though you are viewing it from the side
 hard coded displaying to standard output.
 Preconditions: NONE
 Postconditions: BinTree remains unchanged.
 -----------------------------------------------*/
void BinTree::displaySideways() const
{
    sideways(root, 0);
}
//End of displaySideways

/*------------------ Sideways -------------------
 Helper method for displaySideways
 Preconditions: NONE
 Postconditions: BinTree remains unchanged.
---------------------------------------------------*/
void BinTree::sideways(Node* current, int level) const
{
    if (current != NULL)
    {
        level++;
        sideways(current->right, level);
        
        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            cout << "    ";
        }
        cout << *current->data << endl;
        // display information of object
        sideways(current->left, level);
    }
}
//End of sideways

/*---------------------printInOrder---------------------
 Description:
 Prints all the nodes in the tree in order.

 Precondition: There is an existing node object.
 Postcondition: Prints all the nodes in the tree in order.
---------------------------------------------------------*/
void BinTree::inOrder(Node* root) const
{
    //If the root is nullptr, then just return
    if (root == nullptr)
    {
        return;
    }
    
    //In order: left, root, right
    inOrder(root->left);
    cout << *(root->data) << " ";
    inOrder(root->right);
}
//End of printInOrder.

ostream& operator<<(ostream &out, const BinTree &tree)
{
    BinTree::Node* root = tree.root;
    tree.inOrder(root);
    return out;
}
