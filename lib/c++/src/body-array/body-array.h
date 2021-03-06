#ifndef BODY_ARRAY_H
#define BODY_ARRAY_H

class BodyArray {
    public:
        BodyArray(double *bodies) {
          _bodies = bodies;
        };

        double posX(int index) {
            return *(_bodies + index * 3 + 0); 
        };

        double posY(int index) {
            return *(_bodies + index * 3 + 1); 
        };

        double mass(int index) {
            return *(_bodies + index * 3 + 2); 
        };
    private:
        double * _bodies;
};

#endif