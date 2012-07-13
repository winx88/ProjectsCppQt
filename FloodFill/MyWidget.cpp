#include "MyWidget.h"


MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    _w = Width;
    _h = Height;

    _max = _w * _h * 4;
    _flood = false;
    _b = false;

    setFixedSize(_w, _h);
    _image = new QImage(_w, _h, QImage::Format_RGB32);
    memset(_image->bits(), 255, _max);
    _bits = _image->bits();
}

void MyWidget::Elipse(int x1, int y1, int x2, int y2) {
    int a = abs((x1 - x2)*(x1 - x2));
    int b = abs((y1 - y2)*(y1 - y2));

    int xMax = abs(x1 - x2);
    for (int x = 0; x < xMax; x++) {
        int y = sqrt((a * b - x * x * b) / a);
        SetPixel(x1 + x, y1 + y);
        SetPixel(x1 + x, y1 - y);
        SetPixel(x1 - x, y1 + y);
        SetPixel(x1 - x, y1 - y);
    }

    int yMax = abs(y1 - y2);
    for (int y = 0; y < yMax; y++) {
        int x = sqrt((a * b - y * y * a) / b);
        SetPixel(x1 + x, y1 + y);
        SetPixel(x1 + x, y1 - y);
        SetPixel(x1 - x, y1 + y);
        SetPixel(x1 - x, y1 - y);
    }
}

void MyWidget::Line(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        int yMin = y1 < y2 ? y1 : y2;
        int yMax = y1 < y2 ? y2 : y1;

        for (int y = yMin; y < yMax; y++) {
            SetPixel(x1, y, 0, 0, 0);
        }
    } else {
        double a = (double) (y2 - y1) / (double) (x2 - x1);
        double b = -a * x1 + y1;

        if (a >= -1 && a <= 1) {
            int xMin = x1 < x2 ? x1 : x2;
            int xMax = x1 < x2 ? x2 : x1;

            for (int x = xMin; x < xMax; x++) {
                double y = a * x + b;
                SetPixel(x, y);
            }
        } else {
            int yMin = y1 < y2 ? y1 : y2;
            int yMax = y1 < y2 ? y2 : y1;

            for (int y = yMin; y < yMax; y++) {
                double x = (y - b) / a;
                SetPixel(x, y);
            }
        }
    }
}

void MyWidget::FloodFill(int x, int y) {

    stack<Point> mystack;
    Point t[4];
    int delta = 5;

    Point g = GetPixel(x, y);
    mystack.push(g);

    while (!mystack.empty()) {
        Point q = mystack.top();
        mystack.pop();
        SetPixel(q.X, q.Y, 255, 0, 0);

        t[0] = GetPixel(q.X + 1, q.Y);
        t[1] = GetPixel(q.X - 1, q.Y);
        t[2] = GetPixel(q.X, q.Y - 1);
        t[3] = GetPixel(q.X, q.Y + 1);

        for (int i = 0; i < 4; i++) {
            if ((t[i].R < g.R + delta && t[i].R > g.R - delta) &&
                    (t[i].G < g.G + delta && t[i].G > g.G - delta) &&
                    (t[i].B < g.B + delta && t[i].B > g.B - delta)) {
                mystack.push(t[i]);
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent * e) {
    if (!_flood) {
        if (_b) {
            Elipse(x1, y1, x2, y2);
        } else {
            Line(x1, y1, x2, y2);
        }
    } else {
        FloodFill(x1, y1);
        _flood = false;
    }
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
}

void MyWidget::mousePressEvent(QMouseEvent * e) {
    x1 = e->x();
    y1 = e->y();
    if (e->button() == Qt::RightButton) {
        _flood = true;
        repaint();
    } else {
        _flood = false;
    }
}

void MyWidget::keyPressEvent(QKeyEvent * e) {
    switch (e->key()) {
        case 89: //y
            _b = !_b;
            break;
    }
}

void MyWidget::mouseReleaseEvent(QMouseEvent * e) {
    if (!_flood) {
        x2 = e->x();
        y2 = e->y();
    }
    repaint();
}

