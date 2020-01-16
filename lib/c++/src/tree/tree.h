#ifndef TREE_H
#define TREE_H
#include "../body-array/body-array.h"
#include "../node-array/node-array.h"

class Tree {
    public: 
        Tree(double nodes[][12], BodyArray &bodies) : nodeArray(nodes), bodies(bodies) {};
        
        Tree(int noOfBodies, BodyArray &bodies) : nodeArray(noOfBodies), bodies(bodies) {};
        
        double* getNodes() { return nodeArray.getNodes(); };
    
        void addBody(int index, int bodyAddr);
        
        void setupNode(int index, int parentIndex, double width, double cX, double cY);
        
    private:
        NodeArray nodeArray;
        
        BodyArray &bodies;
        
        bool isSamePosition(int body1, int body2); 
        void addToCorrectSubnode(int body, int index);
        bool isInsideNode( int nodeIndex, int bodyIndex);
        bool hasNoSubnodes(int index);
        void createSubnodes(int index);
        void createIdenticalSubnodes(int index);
        void calculateCentreOfMass(int index);
};

#endif