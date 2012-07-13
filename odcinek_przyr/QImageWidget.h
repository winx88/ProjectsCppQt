#include<QtGui>
#include<iostream>
#include<cmath>
#define DL 500
#ifndef _QIMAGEWIDGET_H
#define	_QIMAGEWIDGET_H
using namespace std;

class QImageWidget : public QWidget {
private:

    int x0, y0, x1, y1;
    int click;

public:

    QImageWidget();
    void paintEvent(QPaintEvent *);
    void zmien(int &, int &, int &, int &);
    void mousePressEvent(QMouseEvent *);
};

#endif	/* _QIMAGEWIDGET_H */

