#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <math.h>
#include <iostream>
#include <stack>
using namespace std;

class Point {
public:
    int X, Y;
    int R, G, B;

    Point() {
        X = 0;
        Y = 0;
    }

    Point(int X, int Y, int R = 0, int G = 0, int B = 0) {
        this->X = X;
        this->Y = Y;
        this->R = R;
        this->G = G;
        this->B = B;
    }
};

class MyWidget : public QWidget {
private:
    int x1, y1, x2, y2;
    int _w, _h;

    long _max;
    bool _flood;
    bool _b;

    QImage *_image;
    uchar *_bits;

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent * e);
public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(int x, int y, int R = 0, int G = 0, int B = 0) {
        int b = _w * 4 * y + 4 * x;
        if (b > -1 && b < _max) {
            _bits[b] = B;
            _bits[b + 1] = G;
            _bits[b + 2] = R;
        }
    }

    Point GetPixel(int x, int y) {
        int b = _w * 4 * y + 4 * x;
        if (b > -1 && b < _max) {
            return Point(x, y, _bits[b], _bits[b + 1], _bits[b + 2]);
        }
        return Point();
    }
    void FloodFill(int x, int y);
    void Line(int x1, int y1, int x2, int y2);
    void Elipse(int x1, int y1, int x2, int y2);
};


#endif	/* _MYWIDGET_H */

