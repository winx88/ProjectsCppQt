#ifndef _POINT_H
#define	_POINT_H
#include<iostream>

class Point {
public:
    double x,y,z;
    Point();
    Point(double,double,double);
    Point operator=(Point);
    
};

#endif	/* _POINT_H */

