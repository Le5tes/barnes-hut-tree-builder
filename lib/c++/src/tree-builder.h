#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H
#include "body.h"

class TreeBuilder {
    public:
        TreeBuilder () {
            tree = 0;
        }
        
        double *build(Body *bodies, int length);

    private:
        double (*tree)[10];
        
        void cleanUp() {
            delete tree;
            tree = 0;
        }
};

#endif
