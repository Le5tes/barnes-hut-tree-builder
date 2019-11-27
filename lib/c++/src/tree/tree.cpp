#include "tree.h"

void Tree::addBody(int index, int body) {
    if (nodeArray.bodyAddr(index) == -1.0 && hasNoSubnodes(index)) {
        nodeArray.setBodyAddr(body, index);
        nodeArray.setPosX(bodies.posX(body), index);
        nodeArray.setPosY(bodies.posY(body), index);
        nodeArray.setMass(bodies.mass(body), index);
    } else {
        if (nodeArray.bodyAddr(index) != -1.0) {
            createSubnodes(index);
            // add old body to subnode
            nodeArray.setBodyAddr(-1, index);
        }
        // add new body to subnode
    }
};

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

void Tree::setupNode(int index, int parentIndex, double _width, double cX, double cY) {
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