#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QSlider>
#include <QtGui/QWidget>
#include <QtGui/QPainter>

#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

class MyWidget : public QWidget {
    Q_OBJECT
private:
    int _picWidth;
    int _picHeight;
    int _selectedFunc;

    QImage *_image, *_imageA, *_imageB;

    QGroupBox *_groupBox;
    QComboBox *_comboBox;
    QSlider *_slider;

    void createImage(double alpha);
    void paintEvent(QPaintEvent *e);

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

public slots:
    void setSliderValue(int);
    void setComboValue(int);

};

#endif	/* _MYWIDGET_H */
