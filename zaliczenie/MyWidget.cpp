#include "MyWidget.h"

using namespace std;

MyWidget::MyWidget() {
    K = 0;
    image = new QImage(W, W, QImage::Format_RGB32);
    tekstura = new QImage("./a.jpg");

    fov = Pi / 4;
    near = 250 + sqrt(4);
    far = near + 500;
    aspect = 1;
    /*
     * Zerowanie macierzy;
     */
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            macierzPersp[i][j] = 0;
        }
    }
    macierzPersp[0][0] = tan(fov / 2) / aspect;
    macierzPersp[1][1] = tan(fov / 2);
    macierzPersp[2][2] = (near + far) / (near - far);
    macierzPersp[3][2] = -1;
    macierzPersp[2][3] = (2 * near * far) / (near - far);

    swiatlo.x = 80;
    swiatlo.y = 50;
    swiatlo.z = 400;


}

void MyWidget::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    paint.drawImage(0, 0, *image);

    imageT = image->bits();
    teksT = tekstura->bits();
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < W; j++) {
            Zbufor[i][j] = 2000;
        }
    }
    Point srodek(50, -120, 400);
    kula(srodek, 100);
    K += 0.1;
}

Point MyWidget::rzutPersp(double persp[4][4], double punkt[4]) {
    Point odp((persp[0][0] * punkt[0] / (-punkt[2]))*250 + 250, (persp[1][1] * punkt[1] / (-punkt[2]))*250 + 250, punkt[2]);
    return odp;
}

void MyWidget::rysuj(Point a, Point kolor) {
    if ((a.x >= 0) && (a.x < W) && (a.y >= 0) && (a.y < W) &&
            (Zbufor[(int) round(a.x)][(int) round(a.y)] > a.z)) {
        Zbufor[(int) round(a.x)][(int) round(a.y)] = a.z;
        imageT[W * 4 * (int) round(a.y) + 4 * (int) round(a.x)] = kolor.x;
        imageT[W * 4 * (int) round(a.y) + 4 * (int) round(a.x) + 1] = kolor.y;
        imageT[W * 4 * (int) round(a.y) + 4 * (int) round(a.x) + 2] = kolor.z;
        update();
    }
}

void MyWidget::obrot(double *punkt, double x, double z) {
    double tmp1, tmp2;
    tmp1 = (punkt[0] - x) * cos(K)-(punkt[2] - z) * sin(K) + x;
    tmp2 = (punkt[2] - z) * cos(K)+(punkt[0] - x) * sin(K) + z;
    punkt[0] = tmp1;
    punkt[2] = tmp2;
}

void MyWidget::kula(Point s, int r) {
    Point punktRzut;
    double punkt[4];
    Point tmpkolor;
    double normalny[3];
    int x, y;
    Point kolor;

    for (double i = 0; i <= 2 * Pi; i += 0.02) {
        for (double j = -Pi / 2; j <= Pi / 2; j += 0.02) {
            punkt[0] = s.x + r * cos(i) * cos(j);
            punkt[1] = s.y + r * sin(i) * cos(j);
            punkt[2] = s.z + r * sin(j);
            punkt[3] = 1;

            normalny[0] = cos(i) * cos(j);
            normalny[1] = sin(i) * cos(j);
            normalny[2] = sin(j);

            obrot(punkt, s.x, s.z);
            obrot(normalny, 0, 0);

            x = (int) round(360 * i / (2 * Pi));
            y = (int) round(360 * (j + Pi / 2) / Pi);

            kolor.x = teksT[360 * 4 * y + 4 * x + 0];
            kolor.y = teksT[360 * 4 * y + 4 * x + 1];
            kolor.z = teksT[360 * 4 * y + 4 * x + 2];

            punktRzut = rzutPersp(macierzPersp, punkt);
            tmpkolor = oswietlenie(punkt, normalny, kolor);
            rysuj(punktRzut, tmpkolor);
        }
    }
}

double MyWidget::skalarny(double a[3], double p2[3]) {
    double tmp = a[0] * p2[0] + a[1] * p2[1] + a[2] * p2[2];
    return max(tmp, (double) 0);
}

double MyWidget::dlugosc(double p[3]) {
    return sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
}

double MyWidget::max(double a, double b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

double MyWidget::min(double a, double b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

Point MyWidget::oswietlenie(double punkt[4], double normalna[3], Point kolor) {
    double zrodlo[3];
    Point punktO;
    double dl;
    double dlu;
    double tmp[3];
    Point p1;
    Point p2;
    double odbicie[3];

    zrodlo[0] = swiatlo.x - punkt[0];
    zrodlo[1] = swiatlo.y - punkt[1];
    zrodlo[2] = swiatlo.z - punkt[2];

    dl = dlugosc(zrodlo);
    zrodlo[0] /= dl;
    zrodlo[1] /= dl;
    zrodlo[2] /= dl;
    dl /= 600;

    p1.x = normalna[0] * skalarny(normalna, zrodlo);
    p1.y = normalna[1] * skalarny(normalna, zrodlo);
    p1.z = normalna[2] * skalarny(normalna, zrodlo);
    p2.x = p1.x - zrodlo[0];
    p2.y = p1.y - zrodlo[1];
    p2.z = p1.z - zrodlo[2];

    odbicie[0] = zrodlo[0] + 2 * p2.x;
    odbicie[1] = zrodlo[1] + 2 * p2.y;
    odbicie[2] = zrodlo[2] + 2 * p2.z;
    tmp[0] = -punkt[0];
    tmp[1] = -punkt[1];
    tmp[2] = -punkt[2];

    dlu = dlugosc(tmp);
    tmp[0] /= dlu;
    tmp[1] /= dlu;
    tmp[2] /= dlu;
    punktO.x = 0.1 * kolor.x + (0.5 * 255 * pow(skalarny(odbicie, tmp), 3) + 0.4 * kolor.x * skalarny(normalna, zrodlo)) * min(1 / (0.4 + 0.2 * dl + 0.4 * dl * dl), (double) 1);
    punktO.y = 0.1 * kolor.y + (0.5 * 255 * pow(skalarny(odbicie, tmp), 3) + 0.4 * kolor.y * skalarny(normalna, zrodlo)) * min(1 / (0.4 + 0.2 * dl + 0.4 * dl * dl), (double) 1);
    punktO.z = 0.1 * kolor.z + (0.5 * 255 * pow(skalarny(odbicie, tmp), 3) + 0.4 * kolor.z * skalarny(normalna, zrodlo)) * min(1 / (0.4 + 0.2 * dl + 0.4 * dl * dl), (double) 1);
    
    return punktO;
}



