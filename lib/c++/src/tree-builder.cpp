#include "tree-builder.h"
#include "body.h"

double* TreeBuilder::build(Body bodies[], int length) {
            cleanUp();

            tree = new double[1][10];
            tree[0][0] = bodies[0].posX;
            double *returnVal = &tree[0][0];
            return returnVal;
        }

TreeBuilder getTreeBuilder() {
    TreeBuilder treeBuilder;
    return treeBuilder;
}
