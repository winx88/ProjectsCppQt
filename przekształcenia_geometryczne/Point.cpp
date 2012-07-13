#include "Point.h"

Point::Point() {
    X = 0;
    Y = 0;
}

Point::Point(int X, int Y, int R, int G, int B) {
    this->X = X;
    this->Y = Y;
    this->R = R;
    this->G = G;
    this->B = B;
}