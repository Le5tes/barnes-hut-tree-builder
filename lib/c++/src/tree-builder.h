#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

typedef int doublePtr_t;

class TreeBuilder {
    public:
        TreeBuilder () {
            tree = 0;
        }
        
        doublePtr_t build(doublePtr_t bodies, int noOfBodies, double width, double cornerX, double cornerY);

        double *build(double* bodies, int noOfBodies, double width, double cornerX, double cornerY);

        int getTreeLength() {
            return treeLength;
        }

    private:
        double (*tree)[12];
        
        int treeLength;

        void cleanUp() {
            delete tree;
            tree = 0;
        }
        
        void addBody(double nodeAddr, double bodyAddr);
};

#endif
