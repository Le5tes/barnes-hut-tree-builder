#include "tree-builder.h"
#include "body-array/body-array.h"
#include "tree/tree.h"

double* TreeBuilder::build(double* bodies, int noOfBodies, double width, double cornerX, double cornerY) {
    BodyArray bodyArray {bodies};

    if (tree == nullptr){
        tree = new Tree(noOfBodies, bodyArray);
    } else {
        tree->reset();
    }
    tree->setupNode(0, -1, width, cornerX, cornerY);
    
    for (int i = 0; i < noOfBodies; i++) {
        if (isInBounds(i, bodyArray, cornerX, cornerY, width)) {
            tree->addBody(0, i);
        }
    }

    return tree->getNodes();
}

int TreeBuilder::getTreeLength() {
    if (tree == nullptr){
        return 0;
    }
    return tree->getLength();
}

bool TreeBuilder::isInBounds(double bodyAddr, BodyArray &bodies, double cornerX, double cornerY, double width) {
    return bodies.posX(bodyAddr) >= cornerX && bodies.posX(bodyAddr) <= cornerX + width
        && bodies.posY(bodyAddr) >= cornerY && bodies.posY(bodyAddr) <= cornerY + width;
}

TreeBuilder getTreeBuilder() {
    TreeBuilder treeBuilder;
    return treeBuilder;
}
