#ifndef _EDGE_H
#define	_EDGE_H
#include "Point.h"

class edge {
public:
    Point p0, p1;
    double m;
    edge(Point, Point);
    edge();
};

#endif	/* _EDGE_H */

