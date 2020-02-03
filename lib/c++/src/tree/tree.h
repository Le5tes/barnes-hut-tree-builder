#ifndef TREE_H
#define TREE_H
#include "../body-array/body-array.h"
#include "../node-array/node-array.h"

class Tree {
    public: 
        Tree(double nodes[][12], BodyArray &bodies) : nodeArray(nodes), bodies(bodies) {};
        
        Tree(int noOfBodies, BodyArray &bodies) : nodeArray(noOfBodies), bodies(bodies) {};
        
        double* getNodes() { return nodeArray.getNodes(); };
        
        int getLength() { return nodeArray.getLength(); };
        
        void reset() { nodeArray.reset(); };
    
        void addBody(int index, int bodyAddr);
        
        void setupNode(int index, int parentIndex, double width, double cX, double cY);
        
    private:
        NodeArray nodeArray;
        
        BodyArray &bodies;
        
        bool isSamePosition(int body1, int body2); 
        int getCorrectSubnode(int body, int index);
        void addToCorrectSubnode(int body, int index);
        bool hasNoSubnodes(int index);
        void createIdenticalSubnodes(int index);
        void calculateCentreOfMass(int index);
        double massIfExists(int address);
        double posXIfExists(int address);
        double posYIfExists(int address);
        bool twoIdenticalSubnodes(int index);
};

#endif