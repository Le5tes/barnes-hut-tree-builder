#include "tree-builder.h"
#include "body-array/body-array.h"
#include "tree/tree.h"

double* TreeBuilder::build(double* bodies, int noOfBodies, double width, double cornerX, double cornerY) {
    BodyArray bodyArray = BodyArray(bodies);

    if (tree == nullptr){
        tree = new Tree(noOfBodies, bodyArray);
    }
    tree->setupNode(0, -1, width, cornerX, cornerY);
    
    for (int i = 0; i < noOfBodies; i++) {
        tree->addBody(0, i);
    }

    return tree->getNodes();
}

TreeBuilder getTreeBuilder() {
    TreeBuilder treeBuilder;
    return treeBuilder;
}
