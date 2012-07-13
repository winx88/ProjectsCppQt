#include<QtGui>
#include <list>
#include <vector>
#include<iostream>
#include<cmath>
#define DL 500
#ifndef _QIMAGEWIDGET_H
#define	_QIMAGEWIDGET_H

class QImageWidget : public QWidget {
    Q_OBJECT
public:
    QImageWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

    void bresenhamLine(QPainter&, QPoint&, QPoint&);
    void drawSquare(QPainter&, QPoint&);
    bool contains(const QPoint&);

    void bezier(QPainter&, std::vector <QPoint>&);
    float bernstein(int, int, float);
    int silnia(int);
    int newton(int, int);


private:
    QPoint pos1, pos2, pos3, *currentPressedCircle;
    int currentPressedPosition;
    bool circlePressed;
    std::vector <QPoint> positions;
};


#endif	/* _QIMAGEWIDGET_H */
