#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

typedef int doublePtr_t;

class TreeBuilder {
    public:
        TreeBuilder () {
            tree = 0;
        }
        
        doublePtr_t build(doublePtr_t bodies, int length);

        double *build(double* bodies, int length);

        int getTreeLength() {
            return treeLength;
        }

    private:
        double (*tree)[10];
        
        int treeLength;

        void cleanUp() {
            delete tree;
            tree = 0;
        }
};

#endif
