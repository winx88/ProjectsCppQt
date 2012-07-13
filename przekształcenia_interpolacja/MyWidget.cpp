#include "MyWidget.h"
#include <stdio.h>
#include <math.h>

double MyWidget::Inter(double a, double b, double d) {
    return b * d + a * (1 - d);
}

void MyWidget::Interpolation(double x, double y, int *R, int *G, int *B) {

    int x0, y0, x1, y1;
    double dx, dy;

    int a = x / 400;
    if (x > a * 400) {
        x = x - a * 400;
    } else {
        x = a * 400 - x;
    }

    a = y / 300;
    if (y > a * 300) {
        y = y - a * 300;
    } else {
        y = a * 300 - y;
    }

    x0 = x;
    y0 = y;

    x1 = x0 + 1;
    y1 = y0 + 1;

    dx = x - x0;
    dy = y - y0;

    *R = Inter(Inter(_bitsSrc[AC[y0][x0] + 2], _bitsSrc[AC[y0][x1] + 2], dx), Inter(_bitsSrc[AC[y1][x0] + 2], _bitsSrc[AC[y1][x1] + 2], dx), dy);
    *G = Inter(Inter(_bitsSrc[AC[y0][x0] + 1], _bitsSrc[AC[y0][x1] + 1], dx), Inter(_bitsSrc[AC[y1][x0] + 1], _bitsSrc[AC[y1][x1] + 1], dx), dy);
    *B = Inter(Inter(_bitsSrc[AC[y0][x0]], _bitsSrc[AC[y0][x1]], dx), Inter(_bitsSrc[AC[y1][x0]], _bitsSrc[AC[y1][x1]], dx), dy);
}

void MyWidget::Round(double x, double y, int *R, int *G, int *B) {
    int X = (int) (x + 0.5);
    int Y = (int) (y + 0.5);
    X = abs(X % 400);
    Y = abs(Y % 300);
    *B = _bitsSrc[AC[Y][X]];
    *G = _bitsSrc[AC[Y][X] + 1];
    *R = _bitsSrc[AC[Y][X] + 2];
}

void MyWidget::Cut(double x, double y, int *R, int *G, int *B) {
    int X = (int) (x);
    int Y = (int) (y);
    X = abs(X % 400);
    Y = abs(Y % 300);
    *B = _bitsSrc[AC[Y][X]];
    *G = _bitsSrc[AC[Y][X] + 1];
    *R = _bitsSrc[AC[Y][X] + 2];
}

void MyWidget::setComboValue(int v) {
    _func_index = v;
    Transform();
    repaint();
}

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

void MyWidget::MatrixXVector(double **M, double *V) {
    double *B = new double[3];
    memcpy(B, V, sizeof (double) * 3);
    memset(V, 0, sizeof (double) * 3);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            V[i] += M[i][j] * B[j];
        }
    }
    delete []B;
}

double MyWidget::Det2x2(double **A, int i, int j) {

    int x0 = 0, x1 = 1;
    int y0 = 0, y1 = 1;

    if (i == 0) {
        x0++;
        x1++;
    } else if (i == 1) {
        x1++;
    }

    if (j == 0) {
        y0++;
        y1++;
    } else if (j == 1) {
        y1++;
    }

    return A[x0][y0] * A[x1][y1] - A[x0][y1] * A[x1][y0];
}

void MyWidget::Matrix_1(double** R) {
    double **B = new double*[3];
    for (int i = 0; i < 3; i++) {
        B[i] = new double[3];
        memcpy(B[i], R[i], sizeof (double) * 3);
    }

    double detB =
            B[0][0] * B[1][1] * B[2][2] +
            B[1][0] * B[2][1] * B[0][2] +
            B[2][0] * B[0][1] * B[1][2] -
            B[1][0] * B[0][1] * B[2][2] -
            B[0][0] * B[2][1] * B[1][2] -
            B[2][0] * B[1][1] * B[0][2];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[j][i] = Det2x2(B, i, j) / detB;
        }
    }
    delete []B;
}

void MyWidget::MatrixXMatix(double **A, double **R) {
    double **B = new double*[3];
    for (int i = 0; i < 3; i++) {
        B[i] = new double[3];
        memcpy(B[i], R[i], sizeof (double) * 3);
        memset(R[i], 0, sizeof (double) * 3);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    delete []B;
}

void MyWidget::Transform() {

    for (int i = 0; i < 3; i++) {
        memset(M_1[i], 0, sizeof (double) * 3);
        memset(T_o[i], 0, sizeof (double) * 3);
        memset(Tr[i], 0, sizeof (double) * 3);
        memset(R[i], 0, sizeof (double) * 3);
        memset(Sc[i], 0, sizeof (double) * 3);
        memset(Sh[i], 0, sizeof (double) * 3);
    }

    M_1[0][0] = 1;
    M_1[1][1] = 1;
    M_1[2][2] = 1;
    M_1[1][2] = -200;
    M_1[0][2] = -150;

    T_o[0][0] = 1;
    T_o[1][1] = 1;
    T_o[2][2] = 1;
    T_o[1][2] = 100;
    T_o[0][2] = 100;

    Tr[0][0] = 1;
    Tr[1][1] = 1;
    Tr[2][2] = 1;
    Tr[1][2] = -Ty;
    Tr[0][2] = -Tx;

    R[0][0] = cos(alfa);
    R[0][1] = -sin(alfa);
    R[1][0] = sin(alfa);
    R[1][1] = cos(alfa);
    R[2][2] = 1;

    Sc[0][0] = Scx;
    Sc[1][1] = Scy;
    Sc[2][2] = 1;

    Sh[0][0] = 1;
    Sh[1][1] = 1;
    Sh[2][2] = 1;
    Sh[0][1] = Shx;
    Sh[1][0] = Shy;

    Matrix_1(Sc);
    Matrix_1(Sh);

    MatrixXMatix(Tr, M_1);
    MatrixXMatix(R, M_1);
    MatrixXMatix(Sh, M_1);
    MatrixXMatix(Sc, M_1);
    MatrixXMatix(T_o, M_1);

    double x, y;
    int R, G, B;

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {

            x = M_1[0][0] * i + M_1[0][1] * j + M_1[0][2];
            y = M_1[1][0] * i + M_1[1][1] * j + M_1[1][2];

            (this->*func[_func_index])(x, y, &R, &G, &B);

            _bitsDest[BC[j][i]] = B;
            _bitsDest[BC[j][i] + 1] = G;
            _bitsDest[BC[j][i] + 2] = R;
        }
    }
}

MyWidget::MyWidget(int Width, int Height, QWidget * parent) : QWidget(parent) {

    alfa = 0;

    Scx = 1;
    Scy = 1;

    Shx = 0;
    Shy = 0;

    setFixedSize(Width, Height);
    _imageSrc = new QImage("/home/winx/NetBeansProjects/przekasztalcenia/Kura.JPG");
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
    grpMode = new QGroupBox(grpMain);
    grpMode->setGeometry(QRect(0, 440, 300, 80));

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

    _comboBox = new QComboBox(grpMode);
    _comboBox->setGeometry(QRect(10, 25, 280, 25));
    _comboBox->insertItems(0, QStringList()
            << "Odcinanie"
            << "Zaokraglanie"
            << "Interpolacja dwuliniowa");

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
    connect(_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setComboValue(int)));

    M_1 = new double*[3];
    T_o = new double*[3];
    Tr = new double*[3];
    R = new double*[3];
    Sc = new double*[3];
    Sh = new double*[3];

    for (int i = 0; i < 3; i++) {
        M_1[i] = new double[3];
        T_o[i] = new double[3];
        Tr[i] = new double[3];
        R[i] = new double[3];
        Sc[i] = new double[3];
        Sh[i] = new double[3];
    }

    func[0] = &MyWidget::Cut;
    func[1] = &MyWidget::Round;
    func[2] = &MyWidget::Interpolation;
    _func_index = 0;

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            BC[i][j] = (500 * i + j) << 2;
        }
    }

    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 400; j++) {
            AC[i][j] = (400 * i + j) << 2;
        }
    }

    Transform();
}