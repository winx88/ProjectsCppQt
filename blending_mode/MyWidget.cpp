#include "MyWidget.h"
#include "modes.h"
#include <stdio.h>

int (*func[29])(int a, int b);

void MyWidget::setSliderValue(int v) {
    char buf[18];
    sprintf(buf, "Opacity (%d/100)", v);
    _groupBox->setTitle(buf);
    repaint();
}

void MyWidget::setComboValue(int v) {
    _selectedFunc = v;
    repaint();
}

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {
    _picWidth = 400;
    _picHeight = 300;
    _selectedFunc = 0;

    setFixedSize(Width, Height);

    _image = new QImage(_picWidth, _picHeight, QImage::Format_RGB32);
    _imageA = new QImage("/home/winx/NetBeansProjects/blending/kon.jpg");
    _imageB = new QImage("/home/winx/NetBeansProjects/blending/robal.jpg");

    _groupBox = new QGroupBox(this);
    _groupBox->setGeometry(QRect(0, 300, 400, 100));
    _groupBox->setTitle("Opacity (0/100)");

    _comboBox = new QComboBox(_groupBox);
    _comboBox->setGeometry(QRect(10, 30, 380, 25));
    _comboBox->insertItems(0, QStringList()
            << "normal mode"
            << "average mode"
            << "multiply mode"
            << "screen mode"
            << "darken mode"
            << "lighten mode"
            << "difference mode"
            << "negation mode"
            << "exclusion mode"
            << "overlay mode"
            << "hard light mode"
            << "soft light mode"
            << "color dodge mode"
            << "inverse color dodge mode"
            << "soft dodge mode"
            << "color burn mode"
            << "inverse color burn mode"
            << "soft burn mode"
            << "reflect mode"
            << "glow mode"
            << "freeze mode"
            << "heat mode"
            << "additive mode"
            << "subtractive mode"
            << "stamp mode"
            << "interpolation mode"
            << "logical XOR mode"
            << "logical OR mode"
            << "logical AND mode");

    _slider = new QSlider(_groupBox);
    _slider->setOrientation(Qt::Horizontal);
    _slider->setRange(0, 100);
    _slider->setGeometry(QRect(10, 60, 380, 25));

    connect(_slider, SIGNAL(sliderMoved(int)), this, SLOT(setSliderValue(int)));
    connect(_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setComboValue(int)));

    func[0] = normalMode;
    func[1] = averageMode;
    func[2] = multiplyMode;
    func[3] = screenMode;
    func[4] = darkenMode;
    func[5] = lightenMode;
    func[6] = differenceMode;
    func[7] = negationMode;
    func[8] = exclusionMode;
    func[9] = overlayMode;
    func[10] = hardlightMode;
    func[11] = softlightMode;
    func[12] = colordodgeMode;
    func[13] = inversecolordodgeMode;
    func[14] = softdodgeMode;
    func[15] = colorburnMode;
    func[16] = inversecolorburnMode;
    func[17] = softburnMode;
    func[18] = reflectMode;
    func[19] = glowMode;
    func[20] = freezeMode;
    func[21] = heatMode;
    func[22] = additiveMode;
    func[23] = subtractiveMode;
    func[24] = stampMode;
    func[25] = interpolationMode;
    func[26] = logicalXORMode;
    func[27] = logicalORMode;
    func[28] = logicalANDMode;

    initCosineTab();

}

void MyWidget::createImage(double alpha) {

    uchar *dest = _image->bits();
    uchar *A = _imageA->bits();
    uchar *B = _imageB->bits();

    for (int j = 0; j < _picHeight; j++) {
        for (int i = 0; i < _picWidth; i++) {
            int pos = (_picWidth * j + i) << 2;
            for (int k = 0; k < 3; k++) {
                int n = pos + k;
                dest[n] = A[n]*(1 - alpha) + func[_selectedFunc](A[n], B[n]) * alpha;
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent*) {
    QPainter paint(this);
    createImage(_slider->value() / (double) 100);
    paint.drawImage(QPoint(0, 0), *_image);
}