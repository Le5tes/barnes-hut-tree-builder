class TreeBuilder {
    
    public:
        TreeBuilder () {
            tree = 0;
        }
        
        double *build() {
            cleanup();
            
            tree = new double[1]; 
            tree[0] = 3.0;
            return tree;
        }

    private:
        double *tree;
        
        void cleanUp() {
            delete tree;
            tree = 0;
        }
};
