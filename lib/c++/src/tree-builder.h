#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H
#include "tree/tree.h"

typedef int doublePtr_t;

class TreeBuilder {
    public:
        TreeBuilder () {
            tree = nullptr;
        }
        
        ~TreeBuilder() {
            delete tree;
        }
        
        doublePtr_t build(doublePtr_t bodies, int noOfBodies, double width, double cornerX, double cornerY);

        double *build(double* bodies, int noOfBodies, double width, double cornerX, double cornerY);

        int getTreeLength();

    private:
        Tree *tree;
        
        void addBody(double nodeAddr, double bodyAddr);
};

#endif
