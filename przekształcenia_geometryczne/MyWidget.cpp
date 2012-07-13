#include "MyWidget.h"
#include <stdio.h>
#include <math.h>

void MyWidget::setSHXSliderValue(int) {
    Shx = SliderSHX->value() / (double) 25;
    char buf[18];
    sprintf(buf, "X: (%0.4f / 8)", Shx);
    lblSHX->setText(buf);
    Transform();
    repaint();
}

void MyWidget::setSHYSliderValue(int) {
    Shy = SliderSHY->value() / (double) 25;
    char buf[18];
    sprintf(buf, "Y: (%0.4f / 8)", Shy);
    lblSHY->setText(buf);
    Transform();
    repaint();
}

void MyWidget::setSCXSliderValue(int) {
    Scx = SliderSCX->value() / (double) 25;
    char buf[18];
    sprintf(buf, "X: (%0.4f / 8)", Scx);
    lblSCX->setText(buf);
    Transform();
    repaint();
}

void MyWidget::setSCYSliderValue(int) {
    Scy = SliderSCY->value() / (double) 25;
    char buf[18];
    sprintf(buf, "Y: (%0.4f / 8)", Scy);
    lblSCY->setText(buf);
    Transform();
    repaint();
}

void MyWidget::setObrotSliderValue(int) {
    alfa = SliderObrot->value() * 0.0174;
    //0,0174532925199 = Pi / 180
    char buf[18];
    sprintf(buf, "Kat: (%d / 360)", SliderObrot->value());
    lblObrot->setText(buf);
    Transform();
    repaint();
}

void MyWidget::setTranXSliderValue(int) {
    Tx = SliderTranX->value();
    char buf[18];
    sprintf(buf, "X: (%d / 200)", SliderTranX->value());
    lblTranX->setText(buf);
    Transform();
    repaint();
}

void MyWidget::setTranYSliderValue(int) {
    Ty = SliderTranY->value();
    char buf[18];
    sprintf(buf, "Y: (%d / 200)", SliderTranY->value());
    lblTranY->setText(buf);
    Transform();
    repaint();
}

void MyWidget::paintEvent(QPaintEvent * e) {
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_imageDest);
    memset(_bitsDest, 255, _maxDest);
}

void MyWidget::Transform() {

    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 400; j++) {

            Point p = GetPixel(j, i);

            p.X -= 200;
            p.Y -= 150;

            //R
            double x = p.X * cos(alfa) - p.Y * sin(alfa);
            double y = p.X * sin(alfa) + p.Y * cos(alfa);

            p.X = x;
            p.Y = y;

            //Sc
            p.X *= Scx;
            p.Y *= Scy;

            //Sh
            x = p.Y * Shx;
            y = p.X * Shy;

            p.X += x;
            p.Y += y;

            p.X += 200;
            p.Y += 150;

            p.X += 50;
            p.Y += 100;

            p.X += Tx;
            p.Y += Ty;

            SetPixel(p);
        }
    }
}

MyWidget::MyWidget(int Width, int Height, QWidget * parent) : QWidget(parent) {

    alfa = 0;

    //Skalowanie
    Scx = 1;
    Scy = 1;

    Shx = 0;
    Shy = 0;

    setFixedSize(Width, Height);
    _imageSrc = new QImage("./k.JPG");
    _imageDest = new QImage(500, 500, QImage::Format_RGB32);
    _maxDest = 500 * 500 * 4;
    _maxSrc = 400 * 300 * 4;
    _bitsSrc = _imageSrc->bits();
    _bitsDest = _imageDest->bits();
    memset(_bitsDest, 255, _maxDest);

    grpMain = new QGroupBox(this);
    grpMain->setGeometry(QRect(500, 0, 300, 500));
    grpSH = new QGroupBox(grpMain);
    grpSH->setGeometry(QRect(0, 105, 300, 110));
    grpSC = new QGroupBox(grpMain);
    grpSC->setGeometry(QRect(0, 220, 300, 110));
    grpObrot = new QGroupBox(grpMain);
    grpObrot->setGeometry(QRect(0, 25, 300, 80));
    grpTran = new QGroupBox(grpMain);
    grpTran->setGeometry(QRect(0, 340, 300, 110));

    SliderSHY = new QSlider(grpSH);
    SliderSHY->setGeometry(QRect(5, 80, 290, 23));
    SliderSHY->setRange(-200, 200);
    SliderSHY->setOrientation(Qt::Horizontal);
    SliderSHX = new QSlider(grpSH);
    SliderSHX->setGeometry(QRect(5, 40, 290, 23));
    SliderSHX->setRange(-200, 200);
    SliderSHX->setOrientation(Qt::Horizontal);
    lblSHX = new QLabel(grpSH);
    lblSHX->setGeometry(QRect(10, 25, 280, 16));
    lblSHY = new QLabel(grpSH);
    lblSHY->setGeometry(QRect(10, 65, 280, 15));

    SliderSCX = new QSlider(grpSC);
    SliderSCX->setGeometry(QRect(5, 40, 290, 23));
    SliderSCX->setRange(-200, 200);
    SliderSCX->setOrientation(Qt::Horizontal);
    SliderSCY = new QSlider(grpSC);
    SliderSCY->setGeometry(QRect(5, 80, 290, 23));
    SliderSCY->setRange(-200, 200);
    SliderSCY->setOrientation(Qt::Horizontal);
    lblSCX = new QLabel(grpSC);
    lblSCX->setGeometry(QRect(10, 25, 280, 15));
    lblSCY = new QLabel(grpSC);
    lblSCY->setGeometry(QRect(10, 65, 280, 15));

    SliderObrot = new QSlider(grpObrot);
    SliderObrot->setGeometry(QRect(5, 40, 290, 23));
    SliderObrot->setMaximum(360);
    SliderObrot->setOrientation(Qt::Horizontal);
    lblObrot = new QLabel(grpObrot);
    lblObrot->setGeometry(QRect(10, 20, 281, 16));

    SliderTranX = new QSlider(grpTran);
    SliderTranX->setGeometry(QRect(5, 40, 290, 23));
    SliderTranX->setRange(-200, 200);
    SliderTranX->setOrientation(Qt::Horizontal);
    SliderTranY = new QSlider(grpTran);
    SliderTranY->setGeometry(QRect(5, 80, 290, 23));
    SliderTranY->setRange(-200, 200);
    SliderTranY->setOrientation(Qt::Horizontal);
    lblTranX = new QLabel(grpTran);
    lblTranX->setGeometry(QRect(10, 25, 280, 15));
    lblTranY = new QLabel(grpTran);
    lblTranY->setGeometry(QRect(10, 65, 280, 15));


    grpMain->setTitle("Przeksztalcenia");
    grpSH->setTitle("SH");
    grpObrot->setTitle("Obot");
    grpSC->setTitle("SC");
    grpTran->setTitle("Transformacja");

    lblSHX->setText("X: (0 / 8)");
    lblSHY->setText("Y: (0 / 8)");

    lblSCX->setText("X: (0 / 8)");
    lblSCY->setText("Y: (0 / 8)");

    lblObrot->setText("Kat: (0 / 360)");

    lblTranX->setText("X: (0 / 200)");
    lblTranY->setText("Y: (0 / 200)");

    connect(SliderObrot, SIGNAL(sliderMoved(int)), this, SLOT(setObrotSliderValue(int)));
    connect(SliderSCX, SIGNAL(sliderMoved(int)), this, SLOT(setSCXSliderValue(int)));
    connect(SliderSCY, SIGNAL(sliderMoved(int)), this, SLOT(setSCYSliderValue(int)));
    connect(SliderSHX, SIGNAL(sliderMoved(int)), this, SLOT(setSHXSliderValue(int)));
    connect(SliderSHY, SIGNAL(sliderMoved(int)), this, SLOT(setSHYSliderValue(int)));
    connect(SliderTranX, SIGNAL(sliderMoved(int)), this, SLOT(setTranXSliderValue(int)));
    connect(SliderTranY, SIGNAL(sliderMoved(int)), this, SLOT(setTranYSliderValue(int)));

    Transform();

}