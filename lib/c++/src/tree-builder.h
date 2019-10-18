class TreeBuilder {
    
    public:
        TreeBuilder () {
            tree = 0;
        }
        
        double *build(double bodies[][5]) {
            cleanUp();
            
            tree = new double[1][10]; 
            tree[0][0] = bodies[0][0];
            double *returnVal = &tree[0][0];
            return returnVal;
        }

    private:
        double (*tree)[10];
        
        void cleanUp() {
            delete tree;
            tree = 0;
        }
};
