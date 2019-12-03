#include "tree.h"

void Tree::addBody(int index, int body) {
    if (nodeArray.bodyAddr(index) == -1 && hasNoSubnodes(index)) {
        nodeArray.setBodyAddr(body, index);
        nodeArray.setPosX(bodies.posX(body), index);
        nodeArray.setPosY(bodies.posY(body), index);
        nodeArray.setMass(bodies.mass(body), index);
    } else {
        if (nodeArray.bodyAddr(index) != -1) {
            if (isSamePosition(nodeArray.bodyAddr(index), body)) {
                createIdenticalSubnodes(index);
                addBody(nodeArray.subnode2Addr(index), nodeArray.bodyAddr(index));
            } else {
                createSubnodes(index);
                addToCorrectSubnode(nodeArray.bodyAddr(index), index);
            }
            nodeArray.setBodyAddr(-1, index);
        }
        addToCorrectSubnode(body, index);
        calculateCentreOfMass(index);
    }
};

bool Tree::isSamePosition(int body1, int body2) {
    return bodies.posX(body1) == bodies.posX(body2) 
        && bodies.posY(body1) == bodies.posY(body2);
}

void Tree::addToCorrectSubnode(int body, int index) {
    if (isInsideNode(nodeArray.subnode1Addr(index), body)) {
        addBody(nodeArray.subnode1Addr(index), body);
    } else if (isInsideNode(nodeArray.subnode2Addr(index), body)) {
        addBody(nodeArray.subnode2Addr(index), body);
    } else if (isInsideNode(nodeArray.subnode3Addr(index), body)) {
        addBody(nodeArray.subnode3Addr(index), body);
    } else if (isInsideNode(nodeArray.subnode4Addr(index), body)) {
        addBody(nodeArray.subnode4Addr(index), body);
    }
}

bool Tree::isInsideNode(int nodeIndex, int bodyIndex) {
    return bodies.posX(bodyIndex) >= nodeArray.cornerX(nodeIndex)
       && bodies.posX(bodyIndex) < nodeArray.cornerX(nodeIndex) + nodeArray.width(nodeIndex) 
       && bodies.posY(bodyIndex) >= nodeArray.cornerY(nodeIndex)
       && bodies.posY(bodyIndex) < nodeArray.cornerY(nodeIndex) + nodeArray.width(nodeIndex) ;
}

void Tree::calculateCentreOfMass(int index) {
    const int subnode1 = nodeArray.subnode1Addr(index);
    const int subnode2 = nodeArray.subnode2Addr(index);
    const int subnode3 = nodeArray.subnode3Addr(index);
    const int subnode4 = nodeArray.subnode4Addr(index);
    
    const double mass = nodeArray.mass(subnode1)
     + nodeArray.mass(subnode2)
     + nodeArray.mass(subnode3)
     + nodeArray.mass(subnode4);
     
    const double positionX = (nodeArray.mass(subnode1) * nodeArray.posX(subnode1)
     + nodeArray.mass(subnode2) * nodeArray.posX(subnode2)
     + nodeArray.mass(subnode3) * nodeArray.posX(subnode3)
     + nodeArray.mass(subnode4) * nodeArray.posX(subnode4)) / mass;
     
     const double positionY = (nodeArray.mass(subnode1) * nodeArray.posY(subnode1)
     + nodeArray.mass(subnode2) * nodeArray.posY(subnode2)
     + nodeArray.mass(subnode3) * nodeArray.posY(subnode3)
     + nodeArray.mass(subnode4) * nodeArray.posY(subnode4)) / mass;
     
    nodeArray.setMass(mass, index); 
    nodeArray.setPosX(positionX, index);
    nodeArray.setPosY(positionY, index);
}

void Tree::createSubnodes(int index) {
    const double _width = nodeArray.width(index) / 2;
    const double _cornerX = nodeArray.cornerX(index);
    const double _cornerY = nodeArray.cornerY(index);

    nodeArray.setSubnode1Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode1Addr(index), index, _width, _cornerX, _cornerY);
    
    nodeArray.setSubnode2Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode2Addr(index), index, _width, _cornerX + _width, _cornerY);
    
    nodeArray.setSubnode3Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode3Addr(index), index, _width, _cornerX, _cornerY + _width);
    
    nodeArray.setSubnode4Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode4Addr(index), index, _width, _cornerX + _width, _cornerY + _width);
};

void Tree::createIdenticalSubnodes(int index) {
    const double _width = nodeArray.width(index);
    const double _cornerX = nodeArray.cornerX(index);
    const double _cornerY = nodeArray.cornerY(index);

    nodeArray.setSubnode1Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode1Addr(index), index, _width, _cornerX, _cornerY);

    nodeArray.setSubnode2Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode2Addr(index), index, _width, _cornerX, _cornerY);
    
    nodeArray.setSubnode3Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode3Addr(index), index, _width, _cornerX, _cornerY);
    
    nodeArray.setSubnode4Addr(nodeArray.nextAvailable(), index);
    setupNode(nodeArray.subnode4Addr(index), index, _width, _cornerX, _cornerY);
};

void Tree::setupNode(int index, int parentIndex, double _width, double cX, double cY) {
    std::cout << index << " | "<< parentIndex << std::endl;
    nodeArray.setMass(0.0, index);
    nodeArray.setParentAddr(parentIndex, index);
    nodeArray.setWidth(_width, index);
    nodeArray.setCornerX(cX, index);
    nodeArray.setCornerY(cY, index);
    nodeArray.setBodyAddr(-1, index);
    nodeArray.setSubnode1Addr(-1, index);
    nodeArray.setSubnode2Addr(-1, index);
    nodeArray.setSubnode3Addr(-1, index);
    nodeArray.setSubnode4Addr(-1, index);
}

bool Tree::hasNoSubnodes(int index) {
    return (nodeArray.subnode1Addr(index) == -1.0 
    && nodeArray.subnode2Addr(index) == -1.0 
    && nodeArray.subnode3Addr(index) == -1.0 
    && nodeArray.subnode4Addr(index) == -1.0);
}