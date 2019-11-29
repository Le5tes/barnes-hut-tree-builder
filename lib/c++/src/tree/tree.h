#ifndef TREE_H
#define TREE_H
#include "../body-array.h"
#include "node-array/node-array.h"

class Tree {
    public: 
        Tree(double nodes[][12], BodyArray &bodies) : nodeArray(nodes), bodies(bodies) 
        {
        }
    
        void addBody(int index, int bodyAddr);
        
        void setupNode(int index, int parentIndex, double width, double cX, double cY);
        
    private:
        NodeArray nodeArray;
        
        BodyArray &bodies;
        
        void addToCorrectSubnode(int body, int index);
        bool isInsideNode( int nodeIndex, int bodyIndex);
        bool hasNoSubnodes(int index);
        void createSubnodes(int index);
};

#endif