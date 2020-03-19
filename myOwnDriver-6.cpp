/*-------------- myOwnDrivver.cpp -------------------
Sung Ho Park
1/25/2020
2/1/2020
-------------------------------------------------
Purpose - This is the main driver class that tests the
binTree classes.
--------------------------------------------------
fstream is used for file io, <assert.h> is used for
debuging.
--------------------------------------------------*/
#include "bintree.h"
#include <assert.h>
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&);      //
void initArray(NodeData*[]);             // initialize array to NULL

int main()
{
    // create file object infile and open it
    // for testing, call your data file something appropriate, e.g., inputdata.txt

    ifstream infile("myOwnInput.txt");

    if (!infile)
    {
        cout << "File could not be opened." << endl;
        return 1;
    }

    // the NodeData class must have a constructor that takes a string
    NodeData longND("longing");
    NodeData rustND("rusted");
    NodeData furND("fur");
    NodeData dayND("daybreak");
    NodeData onesevenND("seventeen");
    NodeData bND("benign");
    NodeData nineND("nine");
    NodeData homeND("homecoming");
    NodeData oneND("one");
    NodeData carND("freightCar");
    

    BinTree T, T2, dup;
    NodeData* ndArray[ARRAYSIZE];
    initArray(ndArray);
    cout << "Initial data:" << endl << "  ";
    buildTree(T, infile);              // builds and displays initial data
    cout << endl;
    assert(T.isEmpty() == false);
    BinTree first(T);                  // test copy constructor
    dup = dup = T;                  // test operator=, self-assignment
    while (!infile.eof())
    {
        cout << "Tree Inorder:" << endl;             // operator<< does endl
        cout << T << endl;
        T.displaySideways();

        // test retrieve
        NodeData* p;                    // pointer of retrieved object
        bool found;                     // whether or not object was found in tree
        found = T.retrieve(rustND, p);
        cout << "Retrieve --> rusted:  " << (found ? "found" : "not found") << endl;
        found = T.retrieve(longND, p);
        cout << "Retrieve --> longing:  " << (found ? "found" : "not found") << endl;
        found = T.retrieve(furND, p);
        cout << "Retrieve --> fur:  " << (found ? "found" : "not found") << endl;

        // test getHeight
        cout << "Height    --> rusted:  " << T.getHeight(rustND) << endl;
        cout << "Height    --> longing:  " << T.getHeight(longND) << endl;
        cout << "Height    --> fur:  " << T.getHeight(furND) << endl;
        cout << "Height    --> daybreak:  " << T.getHeight(dayND) << endl;
        cout << "Height    --> seventeen:  " << T.getHeight(onesevenND) << endl;
        cout << "Height    --> benign:  " << T.getHeight(bND) << endl;
        cout << "Height    --> nine:  " << T.getHeight(nineND) << endl;
        cout << "Height    --> homecoming:  " << T.getHeight(homeND) << endl;
        cout << "Height    --> one:  " << T.getHeight(oneND) << endl;
        cout << "Height    --> freightCar:  " << T.getHeight(carND) << endl;

        // test ==, and !=
        T2 = T;

        cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
        cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
        cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
        dup = T;

        // somewhat test bstreeToArray and arrayToBSTree
        T.bstreeToArray(ndArray);
        T.arrayToBSTree(ndArray);
        T.displaySideways();

        T.makeEmpty();                  // empty out the tree
        initArray(ndArray);             // empty out the array

        cout << "---------------------------------------------------------------"
            << endl;
        cout << "Initial data:" << endl << "  ";
        buildTree(T, infile);
        cout << endl;
    }
    return 0;
}

//------------------------------- buildTree ----------------------------------
// YOU COMMENT

// To build a tree, read strings from a line, terminating when "$$" is
// encountered. Since there is some work to do before the actual insert that is
// specific to the client problem, it's best that building a tree is not a
// member function. It's a global function.

void buildTree(BinTree& T, ifstream& infile)
{
    string s;

    for (;;)
    {
        infile >> s;
        cout << s << ' ';
        if (s == "$$") break;                // at end of one line
        if (infile.eof()) break;             // no more lines of data
        NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
        // would do a setData if there were more than a string

        bool success = T.insert(ptr);
        if (!success)
            delete ptr;                       // duplicate case, not inserted
    }
}

//------------------------------- initArray ----------------------------------
// initialize the array of NodeData* to NULL pointers

void initArray(NodeData* ndArray[]) {
    for (int i = 0; i < ARRAYSIZE; i++)
        ndArray[i] = NULL;
}

