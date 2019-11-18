#include "tree-builder.h"
#include "body-array.h"

double* TreeBuilder::build(double* bodies, int length) {
    cleanUp();

    BodyArray bodyArray = BodyArray(bodies);

    tree = new double[1][10];
    tree[0][0] = bodyArray.mass(0);
    tree[0][1] = bodyArray.posX(0);
    tree[0][2] = bodyArray.posY(0);
    double *returnVal = &tree[0][0];
    return returnVal;
}

TreeBuilder getTreeBuilder() {
    TreeBuilder treeBuilder;
    return treeBuilder;
}
