#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QPoint>
#include <vector>
#include <iostream>

#ifndef _MYWIDGET_H
#define _MYWIDGET_H

#define _PIC_X 400
#define _PIC_Y 300
#define _PIC_MAX 30000 << 4

using namespace std;

class MyWidget : public QWidget {
private:

    QImage *_imagePic;

    QImage *_imageDest;
    QImage *_imageSrc;

    uchar *_bitsPic;

    uchar *_bitsDest;
    uchar *_bitsSrc;

    vector<QPoint> *_pointsSrc;
    vector<QPoint> *_pointsDest;

    vector<QPoint>::iterator _it;
    vector<QPoint>::iterator _moveIt;

    bool _move;
    int _point_size;

    int AC[_PIC_Y][_PIC_X];
    int _XMin, _XMax, _YMin, _YMax;

    double Inter(double a, double b, double d);
    void Interpolation(double x, double y, int *R, int *G, int *B);
    void TextureMap();

    void Line(uchar *bits, QPoint &s, QPoint &t, uchar R = 0, uchar G = 0, uchar B = 0);
    void Square(uchar *bits, QPoint &p, uchar R = 0, uchar G = 0, uchar B = 0);

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(uchar *bits, int x, int y, uchar R = 0, uchar G = 0, uchar B = 0) {
        if (x > 0 && y > 0 && x < _PIC_X && y < _PIC_Y) {
            bits[AC[y][x]] = B;
            bits[AC[y][x] + 1] = G;
            bits[AC[y][x] + 2] = R;
        }
    }
    ~MyWidget();
};

#endif /* _MYWIDGET_H */