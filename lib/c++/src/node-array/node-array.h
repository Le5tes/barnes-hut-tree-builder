#ifndef NODE_ARRAY_H
#define NODE_ARRAY_H

class NodeArray {
    public:
        NodeArray(int numberOfBodies);

        NodeArray(double nodes[][12]);

        ~NodeArray();
   
        double* getNodes() { return &_nodes[0][0]; };
        
        int getLength() { return _length; };

        double posX(int index) { return _nodes[index][0]; };
        
        void setPosX(double posX, int index) { _nodes[index][0] = posX; };

        double posY(int index) { return _nodes[index][1]; };
        
        void setPosY(double posY, int index) { _nodes[index][1] = posY; };
        
        double mass(int index) { return _nodes[index][2]; };
        
        void setMass(double mass, int index) { _nodes[index][2] = mass; };
        
        double width(int index) { return _nodes[index][3]; };
        
        void setWidth(double width, int index) {  _nodes[index][3] = width; };
        
        double cornerX(int index) { return _nodes[index][4]; }
        
        void setCornerX(double cornerX, int index){ _nodes[index][4] = cornerX; }
        
        double cornerY(int index) { return _nodes[index][5]; }
        
        void setCornerY(double cornerY, int index){ _nodes[index][5] = cornerY; }
        
        int parentAddr(int index) {  return (int)_nodes[index][6]; }
        
        void setParentAddr(int parentAddr, int index){ _nodes[index][6] = (double)parentAddr; }
        
        int bodyAddr(int index) { return (int)_nodes[index][7]; }
        
        void setBodyAddr(int bodyAddr, int index){ _nodes[index][7] = (double)bodyAddr; }
        
        int subnode1Addr(int index) { return (int)_nodes[index][8]; }
        
        void setSubnode1Addr(int subnode1Addr, int index){ _nodes[index][8] = (double)subnode1Addr; }
        
        int subnode2Addr(int index) { return (int)_nodes[index][9]; }
        
        void setSubnode2Addr(int subnode2Addr, int index){ _nodes[index][9] = (double)subnode2Addr; }
        
        int subnode3Addr(int index) { return (int)_nodes[index][10]; }
        
        void setSubnode3Addr(int subnode3Addr, int index){ _nodes[index][10] = (double)subnode3Addr; }
        
        int subnode4Addr(int index) { return (int)_nodes[index][11]; }
        
        void setSubnode4Addr(int subnode4Addr, int index){ _nodes[index][11] = (double)subnode4Addr; }

        int nextAvailable();
        
        void reset();
    private:
        double (*_nodes)[12];
        
        int _nextAvailable;
        int _length;
        
        void increaseLength();
};

#endif