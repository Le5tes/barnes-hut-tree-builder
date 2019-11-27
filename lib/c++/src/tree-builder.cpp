#include "tree-builder.h"
#include "body-array.h"
#include "tree/tree.cpp"

double* TreeBuilder::build(double* bodies, int noOfBodies, double width, double cornerX, double cornerY) {
    cleanUp();

    BodyArray bodyArray = BodyArray(bodies);

    tree = new double[noOfBodies * 10][12];
    
    Tree treeContainer = Tree(tree, bodyArray);
    treeContainer.setupNode(0, -1, width, cornerX, cornerY);
    
    for (int i = 0; i < noOfBodies; i++) {
        treeContainer.addBody(0, 0.0);
    }

    double *returnVal = &tree[0][0];
    return returnVal;
}

TreeBuilder getTreeBuilder() {
    TreeBuilder treeBuilder;
    return treeBuilder;
}
