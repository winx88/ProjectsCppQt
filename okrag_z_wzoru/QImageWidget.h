#include<QtGui>
#include<iostream>
#include<cmath>
#include<math.h>
#define DL 500 /* Ustalona wielkosc*/
#ifndef _QIMAGEWIDGET_H
#define	_QIMAGEWIDGET_H

class QImageWidget : public QWidget {

private:
    int x0, y0, x1, y1;
    int click;

public:
    QImageWidget();
    void circleSimple(QImage &, int, int, int);
    void mousePressEvent(QMouseEvent *);/*dane z myszki */
    void paintEvent(QPaintEvent *);/*rysowanie*/

};

#endif	/* _QIMAGEWIDGET_H */
