#ifndef TESTING_NODE_ARRAY_H
#define TESTING_NODE_ARRAY_H

#include "../../src/node-array/node-array.h"

class TestingNodeArray: public NodeArray {
    public:
        TestingNodeArray(double* nodes, int length) {
            _length = length;
            _nodes = new double[length][12];
            for ( int i = 0; i < length; i++ ) {
                for (int j = 0; j < 12; j++) {
                    _nodes[i][j] = *(nodes + i * 12 + j); 
                }
            }
            _nextAvailable = 0;
        }
};

#endif