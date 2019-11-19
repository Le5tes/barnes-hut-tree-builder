#include "tree-builder.h"
#include "body-array.h"

double* TreeBuilder::build(double* bodies, int noOfBodies, double width, double cornerX, double cornerY) {
    cleanUp();

    BodyArray bodyArray = BodyArray(bodies);

    tree = new double[1][12];
    tree[0][0] = bodyArray.mass(0);
    tree[0][1] = bodyArray.posX(0);
    tree[0][2] = bodyArray.posY(0);
    tree[0][3] = width;
    tree[0][4] = cornerX;
    tree[0][5] = cornerY;
    tree[0][6] = -1.0;
    tree[0][7] = 0.0;
    tree[0][8] = -1.0;
    tree[0][9] = -1.0;
    tree[0][10] = -1.0;
    tree[0][11] = -1.0;

    double *returnVal = &tree[0][0];
    return returnVal;
}

TreeBuilder getTreeBuilder() {
    TreeBuilder treeBuilder;
    return treeBuilder;
}
