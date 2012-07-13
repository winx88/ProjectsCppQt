#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QGroupBox>
#include <stdio.h>
#include <math.h>

#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

class MyWidget : public QWidget {
    Q_OBJECT
private:
    int _v, _n;
    int _w, _h;

    long _max;

    QImage *_image;
    uchar *_bits;

    QGroupBox *grpBoxPreview;
    QGroupBox *grpBoxRGB;
    QGroupBox *grpBoxCMYK;
    QGroupBox *grpBoxHSV;

    QLabel *lblR;
    QSlider *SliderR;
    QLabel *lblG;
    QSlider *SliderG;
    QLabel *lblB;
    QSlider *SliderB;

    QLabel *lblC;
    QSlider *SliderC;
    QLabel *lblM;
    QSlider *SliderM;
    QLabel *lblY;
    QSlider *SliderY;
    QLabel *lblK;
    QSlider *SliderK;

    QLabel *lblH;
    QSlider *SliderH;
    QLabel *lblS;
    QSlider *SliderS;
    QLabel *lblV;
    QSlider *SliderV;

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void paintEvent(QPaintEvent * e);

    void RGB(int v, int n);
    void HSV(int v, int n);
    void CMYK(int v, int k, int n);

public slots:
    void setRSliderValue(int);
    void setGSliderValue(int);
    void setBSliderValue(int);
    void setHSliderValue(int);
    void setSSliderValue(int);
    void setVSliderValue(int);
    void setCSliderValue(int);
    void setMSliderValue(int);
    void setYSliderValue(int);
    void setKSliderValue(int);

};

#endif	/* _MYWIDGET_H */