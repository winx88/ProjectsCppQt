#include "QImageWidget.h"

QImageWidget::QImageWidget() {
    click = 0, x0 = 0, y0 = 0, x1 = 0, y1 = 0;
}

void QImageWidget::zmien(int &a0, int &b0, int &a1, int &b1) {
    int swap;
    swap = a0;
    a0 = a1;
    a1 = swap;
    swap = b0;
    b0 = b1;
    b1 = swap;
}

void QImageWidget::mousePressEvent(QMouseEvent *event) {
    if (!click) {
        x0 = event->x();
        y0 = event->y();
    } else {
        x1 = event->x();
        y1 = event->y();
        update();
    }
    click = !click;
}

void QImageWidget::paintEvent(QPaintEvent *) {

    QImage image(DL, DL, QImage::Format_RGB32);
    image.fill(0);
    int dx = x1 - x0;
    int dy = y1 - y0;
    float m = ((float) dy) / dx;
    float mx = ((float) dx) / dy;

    if (abs(mx) < 1) {
        if (dy < 0) {
            zmien(x0, y0, x1, y1);
        }

        float x;
        for (int y = y0; y < y1; y++) {
            x = mx * (y - y0) + x0;
            image.setPixel(floor(x + 0.5), y, qRgb(255, 255, 255));
        }
    }
    if (abs(m) < 1) {
        float y;
        if (dx < 0) {
            zmien(x0, y0, x1, y1);
        }

        for (int x = x0; x < x1; x++) {
            y = m * (x - x0) + y0;
            image.setPixel(x, floor(y + 0.5), qRgb(255, 255, 255));
        }

    }
    QPainter paint(this);
    paint.drawImage(0, 0, image);

}
