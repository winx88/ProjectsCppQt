/* 
 * File:   MyWidget.cpp
 * Author: winx
 * 
 * Created on 26 maj 2010, 14:42
 */

#include "MyWidget.h"

MyWidget::MyWidget() {
    D = 200;
    SR.x = 200;
    SR.y = 200;
    SR.z = 350;
    o = new QHBoxLayout;
    K = 0;
    p = new QImage(300, 300, QImage::Format_RGB32);
    this->setLayout(o);
    this->resize(300, 300);
    this->show();
}

void MyWidget::policz(int x, int y, int z) {
    int D = 250;
    int x1;
    int y1;
    x1 = round((x) * D / (z + D));
    y1 = round((y) * D / (z + D));
    tabPoint.push_back(Point(x1, y1));
}

void MyWidget::czysc(vector<Point> &p) {
    p.erase(p.begin(), p.end());
}

bool MyWidget::S(int x1, int y1, int x2, int y2, int x4, int y4) {
    if (((x4 - x1) * (y2 - y1) - (x2 - x1) * (y4 - y1)) < 0)
        return true;
    else
        return false;
}

void MyWidget::rysuj(int x1, int y1, int x2, int y2, int x3, int y3, int k = 0) {
    int x, y;
    int kolor = 255;
    int kol2 = 0;
    if (k == 1)
        kolor = 155;
    if (k == 2)
        kol2 = 200;
    for (double i = 0; i <= 1; i += 0.005) {
        for (double j = 0; j <= 1 - i; j += 0.005) {
            x = round(x1 * i + x2 * j + x3 * (1 - i - j));
            y = round(y1 * i + y2 * j + y3 * (1 - i - j));
            p1[300 * 4 * x + 4 * y] = kol2;
            p1[300 * 4 * x + 4 * y + 1] = kol2;
            p1[300 * 4 * x + 4 * y + 2] = kolor;
            update();
        }
    }
}

void MyWidget::paintEvent(QPaintEvent *) {

    Point3d SR(200, 200, 350);
    QPainter paint(this);
    paint.drawImage(0, 0, *p);
    p1 = p->bits();
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {
            p1[300 * 4 * i + 4 * j] = 0;
            p1[300 * 4 * i + 4 * j + 1] = 0;
            p1[300 * 4 * i + 4 * j + 2] = 0;
            update();
        }
    }
    tabPoint3d.push_back(Point3d(150, 250, 300)); //w1
    tabPoint3d.push_back(Point3d(250, 250, 300)); //w2
    tabPoint3d.push_back(Point3d(150, 250, 400)); //w3
    tabPoint3d.push_back(Point3d(250, 250, 400)); //w4
    tabPoint3d.push_back(Point3d(150, 150, 400)); //w5
    tabPoint3d.push_back(Point3d(250, 150, 400)); //w6
    tabPoint3d.push_back(Point3d(150, 150, 300)); //w7
    tabPoint3d.push_back(Point3d(250, 150, 300)); //w8

    cosin = cos(K * Pi / 180);
    sinus = sin(K * Pi / 180);

    int x1, y1, x2, y2, x3, y3, x4, y4;

    //gora
    Point3d temp;
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x1 = round((temp.x) * D / (temp.z + D));
    y1 = round((temp.y) * D / (temp.z + D));
    tabO3d.push_back(temp);
    //w2
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x2 = round((temp.x) * D / (temp.z + D));
    y2 = round((temp.y) * D / (temp.z + D));
    tabO3d.push_back(temp);
    //w4
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x3 = round((temp.x) * D / (temp.z + D));
    y3 = round((temp.y) * D / (temp.z + D));
    //w3
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x4 = round((temp.x) * D / (temp.z + D));
    y4 = round((temp.y) * D / (temp.z + D));

    if (S(x1, y1, x2, y2, x4, y4)) {
        rysuj(x1, y1, x2, y2, x3, y3);
        rysuj(x1, y1, x4, y4, x3, y3);
    }



    // w3
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x4 = round((temp.x) * D / (temp.z + D));
    y4 = round((temp.y) * D / (temp.z + D));
    //w4
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x3 = round((temp.x) * D / (temp.z + D));
    y3 = round((temp.y) * D / (temp.z + D));
    //w5
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x1 = round((temp.x) * D / (temp.z + D));
    y1 = round((temp.y) * D / (temp.z + D));
    // w6
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x2 = round((temp.x) * D / (temp.z + D));
    y2 = round((temp.y) * D / (temp.z + D));

    if (!S(x4, y4, x1, y1, x3, y3)) {

        rysuj(x1, y1, x2, y2, x3, y3, 1);
        rysuj(x1, y1, x4, y4, x3, y3, 1);
    }

    //w5
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.y + (150 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x4 = round((temp.x) * D / (temp.z + D));
    y4 = round((temp.y) * D / (temp.z + D));
    //w6
    temp.x = (250 - SR.y) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x3 = round((temp.x) * D / (temp.z + D));
    y3 = round((temp.y) * D / (temp.z + D));
    //dol w7
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x1 = round((temp.x) * D / (temp.z + D));
    y1 = round((temp.y) * D / (temp.z + D));
    //w8
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x2 = round((temp.x) * D / (temp.z + D));
    y2 = round((temp.y) * D / (temp.z + D));

    if (!S(x1, y1, x2, y2, x4, y4)) {
        rysuj(x1, y1, x2, y2, x3, y3);
        rysuj(x1, y1, x4, y4, x3, y3);
    }

    //prawo w8
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x1 = round((temp.x) * D / (temp.z + D));
    y1 = round((temp.y) * D / (temp.z + D));
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x2 = round((temp.x) * D / (temp.z + D));
    y2 = round((temp.y) * D / (temp.z + D));
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x3 = round((temp.x) * D / (temp.z + D));
    y3 = round((temp.y) * D / (temp.z + D));
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x4 = round((temp.x) * D / (temp.z + D));
    y4 = round((temp.y) * D / (temp.z + D));

    if (S(x1, y1, x2, y2, x4, y4)) {
        rysuj(x1, y1, x2, y2, x3, y3);
        rysuj(x1, y1, x4, y4, x3, y3);
    }

    //lewo w7
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x1 = round((temp.x) * D / (temp.z + D));
    y1 = round((temp.y) * D / (temp.z + D));
    //w5
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x2 = round((temp.x) * D / (temp.z + D));
    y2 = round((temp.y) * D / (temp.z + D));
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (400 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (400 - SR.z) * cosin + SR.z;
    x3 = round((temp.x) * D / (temp.z + D));
    y3 = round((temp.y) * D / (temp.z + D));
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x4 = round((temp.x) * D / (temp.z + D));
    y4 = round((temp.y) * D / (temp.z + D));

    if (!S(x1, y1, x2, y2, x4, y4)) {
        rysuj(x1, y1, x2, y2, x3, y3, 2);
        rysuj(x1, y1, x4, y4, x3, y3, 2);
    }

    //przod
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x1 = round((temp.x) * D / (temp.z + D));
    y1 = round((temp.y) * D / (temp.z + D));
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (150 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (150 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x2 = round((temp.x) * D / (temp.z + D));
    y2 = round((temp.y) * D / (temp.z + D));
    temp.x = (250 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x3 = round((temp.x) * D / (temp.z + D));
    y3 = round((temp.y) * D / (temp.z + D));
    temp.x = (150 - SR.x) + SR.x + SR.y + SR.z;
    temp.y = SR.x + (250 - SR.y) * cosin + SR.y + (300 - SR.z) * (-sinus) + SR.z;
    temp.z = SR.x + (250 - SR.y) * sinus + SR.y + (300 - SR.z) * cosin + SR.z;
    x4 = round((temp.x) * D / (temp.z + D));
    y4 = round((temp.y) * D / (temp.z + D));

    if (S(x1, y1, x2, y2, x4, y4)) {
        rysuj(x1, y1, x2, y2, x3, y3, 1);
        rysuj(x1, y1, x4, y4, x3, y3, 1);
    }
    K -= 10;


}