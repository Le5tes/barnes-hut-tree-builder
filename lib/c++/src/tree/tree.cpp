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
                // createSubnodes(index);
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
    int correctSubnode = getCorrectSubnode(body, index);
    const double _width = nodeArray.width(index) / 2;
    const double _cornerX = nodeArray.cornerX(index);
    const double _cornerY = nodeArray.cornerY(index);
    
    if (correctSubnode == 0) {
        if (nodeArray.subnode1Addr(index) == -1) {
            nodeArray.setSubnode1Addr(nodeArray.nextAvailable(), index);
            setupNode(nodeArray.subnode1Addr(index), index, _width, _cornerX, _cornerY);
        }
        addBody(nodeArray.subnode1Addr(index), body);
    } else if (correctSubnode == 1) {
         if (nodeArray.subnode2Addr(index) == -1) {
            nodeArray.setSubnode2Addr(nodeArray.nextAvailable(), index);
            setupNode(nodeArray.subnode2Addr(index), index, _width, _cornerX + _width, _cornerY);
        }
        addBody(nodeArray.subnode2Addr(index), body);
    } else if (correctSubnode == 2) {
        if (nodeArray.subnode3Addr(index) == -1) {
            nodeArray.setSubnode3Addr(nodeArray.nextAvailable(), index);
            setupNode(nodeArray.subnode3Addr(index), index, _width, _cornerX, _cornerY + _width);
        }
        addBody(nodeArray.subnode3Addr(index), body);
    } else if (correctSubnode == 3) {
        if (nodeArray.subnode4Addr(index) == -1) {
            nodeArray.setSubnode4Addr(nodeArray.nextAvailable(), index);
            setupNode(nodeArray.subnode4Addr(index), index, _width, _cornerX + _width, _cornerY + _width);
        }
        addBody(nodeArray.subnode4Addr(index), body);
    }
}

int Tree::getCorrectSubnode(int body, int index) {
    const double _width = nodeArray.width(index) / 2;
    const double _cornerX = nodeArray.cornerX(index);
    const double _cornerY = nodeArray.cornerY(index);
    
    if(bodies.posY(body) < _cornerY + _width ) {
        if(bodies.posX(body) < _cornerX + _width ) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if(bodies.posX(body) < _cornerX + _width ) {
            return 2;
        } else {
            return 3;
        }
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
    
    const double mass = massIfExists(subnode1)
     + massIfExists(subnode2)
     + massIfExists(subnode3)
     + massIfExists(subnode4);
     
    const double positionX = (massIfExists(subnode1) * posXIfExists(subnode1)
     + massIfExists(subnode2) * posXIfExists(subnode2)
     + massIfExists(subnode3) * posXIfExists(subnode3)
     + massIfExists(subnode4) * posXIfExists(subnode4)) / mass;
     
     const double positionY = (massIfExists(subnode1) * posYIfExists(subnode1)
     + massIfExists(subnode2) * posYIfExists(subnode2)
     + massIfExists(subnode3) * posYIfExists(subnode3)
     + massIfExists(subnode4) * posYIfExists(subnode4)) / mass;
     
    nodeArray.setMass(mass, index); 
    nodeArray.setPosX(positionX, index);
    nodeArray.setPosY(positionY, index);
}

    double Tree::massIfExists(int address) {
        if (address == -1) {
            return 0;
        }
        return nodeArray.mass(address);
    };
    
    double Tree::posXIfExists(int address) {
         if (address == -1) {
            return 0;
        }
        return nodeArray.posX(address);
    };
    
    double Tree::posYIfExists(int address) {
         if (address == -1) {
            return 0;
        }
        return nodeArray.posY(address);
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