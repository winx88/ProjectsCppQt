#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QComboBox>
#include <QtGui/QColor>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QGroupBox>
#include "Point.h"

#ifndef _MYWIDGET_H
#define _MYWIDGET_H

class MyWidget : public QWidget {
    Q_OBJECT
private:

    QGroupBox *grpMain;
    QGroupBox *grpSH;
    QGroupBox *grpSC;
    QGroupBox *grpObrot;
    QGroupBox *grpTran;

    QSlider *SliderSHY;
    QSlider *SliderSHX;
    QLabel *lblSHX;
    QLabel *lblSHY;

    QSlider *SliderSCX;
    QSlider *SliderSCY;
    QLabel *lblSCX;
    QLabel *lblSCY;

    QSlider *SliderObrot;
    QLabel *lblObrot;

    QSlider *SliderTranX;
    QSlider *SliderTranY;
    QLabel *lblTranX;
    QLabel *lblTranY;

    double Tx, Ty;
    double Scx, Scy;
    double Shx, Shy;
    double alfa;

    long _maxSrc, _maxDest;


    QImage *_imageSrc, *_imageDest;
    uchar *_bitsSrc, *_bitsDest;

    void Transform();

    void paintEvent(QPaintEvent * e);
public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(Point p) {
        int b = (500 * p.Y + p.X) << 2;
        if (b > -1 && b < _maxDest && p.X < 500 && p.X > 0) {
            _bitsDest[b] = p.B;
            _bitsDest[b + 1] = p.G;
            _bitsDest[b + 2] = p.R;
        }
    }

    Point GetPixel(int x, int y) {
        int b = (400 * y + x) << 2;
        if (b > -1 && b < _maxSrc && x < 400 && x > 0) {
            return Point(x, y, _bitsSrc[b + 2], _bitsSrc[b + 1], _bitsSrc[b]);
        }
        return Point();
    }

public slots:
    void setSHXSliderValue(int);
    void setSHYSliderValue(int);

    void setSCXSliderValue(int);
    void setSCYSliderValue(int);

    void setObrotSliderValue(int);

    void setTranXSliderValue(int);
    void setTranYSliderValue(int);

};

#endif /* _MYWIDGET_H */