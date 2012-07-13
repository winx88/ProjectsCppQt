#include "edge.h"
#include "Point.h"
edge::edge(Point p0, Point p1) {
    this->p0.x=p0.x;
    this->p0.y =p0.y;
    this->p1.x = p1.x;
    this->p1.y = p1.y;
    if((p0.x-p1.x)==0)
        this->m=0;
    else
        this->m=((double)p0.y-(double)p1.y)/((double)p0.x-(double)p1.x);
}
edge::edge(){
    this->p0.x=0;
    this->p0.y =0;
    this->p1.x =0;
    this->p1.y =0;
    this->m=0;
   }



