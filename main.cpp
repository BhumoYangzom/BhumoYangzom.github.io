//
//  main.cpp
//  Project4
//
//  Created by Yangzom Dolma on 3/28/19.
//  Copyright © 2019 Yangzom Dolma. All rights reserved.
//

#include <iostream>
using namespace std;
#include <iostream>
using namespace std;

class Tree{
protected:
    int arraySize;
    int root;
    int parentArray[];
    
public:
    Tree(); // default constructor
    Tree (int numNodes); // Non-default constructor
    ~Tree(); // destructor
    
    int Parent(int i); // get the parent of node i;
    void Children (int i); // get children of node i;
    void Siblings (int i); // get siblings of node i;
    int Root(); // get the root of the tree;
    int LCA (int a, int b); //least common ancestor of the two nodes.
    void nodesAtLevel(int i);
    int getLevel(int i); // get level of node i
    int level(int i); // Give the level of node i
    int height (); // height of tree
    void setRoot(int rootNode); // set the root value to the specified parameter.
    void setParent( int node, int parent); // set the parent of the node to the specified parent value.
    void setSize(int size); // set the size of the array.
    int size();
    void dispay(ostream& os);
    friend ostream& operator<< (ostream& os, Tree& t);
    void PreOrder(); // preorder traversal
    
};

// Default constructor

Tree:: Tree(){
    parentArray[arraySize]; // parentArray's size is set to arraySize value.
}

// Constructur taking in the size of the array
Tree:: Tree (int numNodes) {
    arraySize = numNodes;
}

// The setSize method implementation

void Tree:: setSize(int size){ // same as copy constructor
    arraySize=size;
}

//The size method implementation
int Tree:: size()
{
    return arraySize;
}

// Returns the root of the tree
int Tree:: Root() {
    return root;
}

// sets the root of the tree.
void Tree:: setRoot(int rootNode) {
    root = rootNode;
}

//Returns the parent of the node specified.
int Tree:: Parent(int i) {
    if (parentArray[i] == -1)
        return Root();
    return parentArray [i];
}

// sets the parent of the specified node.
void Tree:: setParent(int node, int parent){
    parentArray[node] = parent;
}

//Prints out the children of node p.
void Tree:: Children(int p) {
    for (int i=0; i<size(); i++)
    {
        if (parentArray[i]==p)
            cout<<i <<" ";
        
    }
}

//Prints out the siblings of the specified node.
void Tree:: Siblings(int s){
    
    for (int i =0; i< size(); i++) {
        if (parentArray[i] == parentArray[s])
        {
            if (i != s)
                cout<<i<<" ";
        }
    }
}

// retuns the least common ancestors of the two specified nodes. The ancestors of each node are stored in separate arrays and then, the first common values in the two set of arrays is return as the least common ancestor.
int Tree::LCA(int node1, int node2)
{
    int a [size()];
    int b [size()];
    
    a [0] = node1;
    b [0] = node2;
    
    int count1 = 1; // counter for array a.
    int count2 = 1; // counter for array b.
    
    if (node1 == node2)
    {
        return node2;
    }
    
    // The following code operates if node1 and node2 are different.
    
    else
    {
        while (node1 != -1)
        {
            a [count1] = node1;
            count1 ++;
            node1 = parentArray[node1];
        }
        
        while (node2 != -1)
        {
            b [count2] =  node2;
            count2 ++;
            node2 = parentArray [node2];
        }
        
        // Two for loop used to find same values in the two arrays.
        for (int i=0; i < count1; i++)
        {
            for (int j=0; j<count2; j++)
            {
                if (a[i] == b[j])
                    return a[i];
            }
        }
    }
    
    
    
    return 0;
}

// returns the level at the specified node.
int Tree:: level(int i) // get the level of node i
{
    int L =1;
    if (i== Root())
    {
        L = 1;
    }
    else {
        while (i != Root()){
            L++;
            i = parentArray [i];
            //level (parentArray[i]);
            
        }
    }
    return L;
}

// prints out the nodes at the specified level.
void Tree::nodesAtLevel(int l) {
    int temp [size()];
    for (int i=0; i < size(); i++){
        temp[i]=this->level(i);
        
        if (temp[i] == l)
            cout <<i <<" ";
    }
    cout<<endl;
    //delete[] temp;
}

// returns the height of the tree
int Tree:: height() {
    int temp[size()];
    int height =0;
    for (int i=0; i<size(); i++) {
        temp[i]=level(i);
    }
    for (int i=0; i<size(); i++){
        if (temp[i]>height){
            height = temp[i];
        }
    }
    
    return height;
}

// The display method implementation
void Tree:: dispay(ostream& os){
    for (int i=0; i<size(); i++ ){
        os<<i << "  "<< parentArray[i] <<endl;
    }
}
ostream& operator<< (ostream& os, Tree& t) {
    t.dispay(os);
    return os;
}

// PreOrder Implementation with recursive call.
void Tree:: PreOrder(){
    
    int r = Root(); // storing the root of the tree in a variable r.
    
    if (parentArray[r] == -1)
    {
        cout << r << " ";
    }
    for (int i=0; i<size(); i++)
    {
        if (parentArray[i] == r)
        {
            cout<<i<<" ";
            setRoot(i); // set the root to i.
            PreOrder(); // the recursive call of the PreOrder method.
            
        }
    }
    
    
}

// The main method implementation

int main(int argc, const char * argv[]) {
    Tree* myTree;
    
    int numNodes, node, parent;
    cout <<"enter num nodes "<<endl;
    cin>>numNodes;
    myTree = new Tree (numNodes);
    for (int i=0; i< numNodes; i++){
        cin>>node>>parent;
        myTree->setParent(node, parent);
        if (parent == -1) {
            myTree->setRoot(node);
        }
    }
    
    cout << "The tree that we just read is ...."<<endl;
    for (int i=0; i< myTree->size(); i++){
        cout << i<<": "<<myTree->Parent(i)<<" ";
    }
    cout<<endl;
    cout<< "The tree that we just copied is ...."<<endl;
    for (int i=0; i< myTree->size(); i++){
        cout << i<<": "<<myTree->Parent(i)<<" ";
    }
    cout<<endl;
    
    //Printing other methods ...
    
    cout << "The root of the tree is: " <<myTree->Root()<<endl;
    
    
    cout <<"The least common ancestors of nodes 3 and 8 is: "<<myTree->LCA(3, 8)<<endl;
    cout <<"The least common ancestors of nodes 13 and 8 is: "<<myTree->LCA(13, 8)<<endl;
    cout <<"The least common ancestors of nodes 13 and 11 is: "<<myTree->LCA(13, 11)<<endl;
    
    cout <<"Children of node 12 is/are: "<<endl;
    myTree->Children(12);
    cout<<endl;
    
    cout <<"Children of node 10 is/are: "<<endl;
    myTree->Children(10);
    cout<<endl;
    
    cout <<"Siblings of node 3 is/are: "<<endl;
    myTree->Siblings(3);
    cout<<endl;
    
    cout <<"Siblings of node 12 is/are: "<<endl;
    myTree->Siblings(12);
    cout<<endl;
    
    cout <<"The nodes at level 3 is/are: "<<endl;
    myTree->nodesAtLevel(3);
    
    cout<<"The height of the tree is: "<<myTree->height()<<endl;
    
    cout<< "The level of node 3 in the tree is: "<<myTree->level(3)<<endl;
    cout<<"The level of node 12 in the tree is: "<<myTree->level(12)<<endl;
    
    cout <<"The preorder traversal of the tree is/are: "<<endl;
    myTree->PreOrder();
    cout<<endl;
    
    return 0;
}
