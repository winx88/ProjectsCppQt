#include "myImage.h"

myImage::myImage(int a, int b, QImage::Format c) : QImage(a, b, c) {
}

void myImage::change(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void myImage::clean() {
    for (int i=0; i < DL; i++) {
        for (int j=0; j < DL; j++)
            this->setPixel(i, j, qRgb(0, 0, 0));
    }
}

void myImage::line(int x1, int y1, int x2, int y2) {
    int d, dx, dy, ai, bi, xi, yi;
    int x = x1, y = y1;

    if (x1 < x2) {
        xi = 1;
        dx = x2 - x1;
    } else {
        xi = -1;
        dx = x1 - x2;
    }

    if (y1 < y2) {
        yi = 1;
        dy = y2 - y1;
    } else {
        yi = -1;
        dy = y1 - y2;
    }

    this->setPixel(x, y, qRgb(255, 255, 255));

    if (dx > dy) {
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;

        while (x != x2) {

            if (d >= 0) {
                x += xi;
                y += yi;
                d += ai;
            } else {

                d += bi;
                x += xi;
            }
            this->setPixel(x, y, qRgb(255, 255, 255));
        }
    } else {

        ai = (dx - dy) * 2;
        bi = dx * 2;
        d = bi - dy;

        while (y != y2) {

            if (d >= 0) {

                x += xi;
                y += yi;
                d += ai;
            } else {

                d += bi;
                y += yi;
            }

            this->setPixel(x, y, qRgb(255, 255, 255));
        }
    }
}

