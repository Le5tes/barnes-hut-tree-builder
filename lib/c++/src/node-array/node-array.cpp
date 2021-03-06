#include "node-array.h"
#include <cstring>

NodeArray::NodeArray(int numberOfBodies): NodeArray() {
    _length = numberOfBodies * 4;
    _nodes = new double[numberOfBodies * 4][12];
};

NodeArray::~NodeArray() {
    delete[] _nodes;
};

int NodeArray::nextAvailable() {
    _nextAvailable ++;
    if(_nextAvailable >= _length) {
       increaseLength();
    }
    return _nextAvailable;
};

void NodeArray::increaseLength() {
    int newLength = _length * 2;
    double (*newNodes)[12] = new double[newLength][12];
    
    memcpy(newNodes, _nodes, sizeof(double) * 12 * _length);
    
    delete[] _nodes;
    _nodes = newNodes;
    _length = newLength;
};

void NodeArray::reset() {
    _nextAvailable = 0;    
}
