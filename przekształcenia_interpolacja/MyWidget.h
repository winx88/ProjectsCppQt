#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QComboBox>
#include <QtGui/QColor>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QGroupBox>

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
    QGroupBox *grpMode;

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

    QComboBox *_comboBox;

    double Tx, Ty;
    double Scx, Scy;
    double Shx, Shy;
    double alfa;

    double **M_1;
    double **T_o;
    double **Tr;
    double **R;
    double **Sc;
    double **Sh;

    int _func_index;
    long _maxSrc, _maxDest;

    int AC[300][400];
    int BC[500][500];

    QImage *_imageSrc, *_imageDest;
    uchar *_bitsSrc, *_bitsDest;

    void Transform();

    double Det2x2(double **A, int i, int j);
    void Matrix_1(double** R);
    void MatrixXMatix(double **A, double **R);
    void MatrixXVector(double **M, double *V);

    void (MyWidget::*(func[3]))(double x, double y, int *R, int *G, int *B);

    double Inter(double a, double b, double d);

    void Interpolation(double x, double y, int *R, int *G, int *B);
    void Round(double x, double y, int *R, int *G, int *B);
    void Cut(double x, double y, int *R, int *G, int *B);

    void paintEvent(QPaintEvent * e);
public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

public slots:
    void setSHXSliderValue(int);
    void setSHYSliderValue(int);

    void setSCXSliderValue(int);
    void setSCYSliderValue(int);

    void setObrotSliderValue(int);

    void setTranXSliderValue(int);
    void setTranYSliderValue(int);

    void setComboValue(int);

};

#endif /* _MYWIDGET_H */