#include<QtGui>
#include <list>
#include <vector>
#include<algorithm>
#include "myImage.h"
#include "edge.h"
#define DL 500
#ifndef _QIMAGEWIDGET_H
#define	_QIMAGEWIDGET_H

class QImageWidget : public QWidget {
protected:

    void paintEvent(QPaintEvent*);
    void addPoint();
    bool vertex(Point &);
    void solve(edge, edge, Point &);
    void changeEdge(edge &, edge &);
    void sortEdges(int i);
    void changePoint(Point &, Point &);
    void sortPoint();
    void updateEdge(std::vector<Point>);
    void countRange();
    void drawRange(int, int, int, std::vector<edge>*, myImage&);
    bool controlPoint(Point p);
    void deletePoint(int pos);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void drawSquare(myImage &image);
private:
    bool fill;
    int positions;
    Point p;
    edge *tab_edge;
    std::vector <Point> points;
    std::vector<Point> upoints;
    std::vector<edge> *tab_range;
};


#endif	/* _QIMAGEWIDGET_H */
