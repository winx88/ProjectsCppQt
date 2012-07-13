#include "QImageWidget.h"

QImageWidget::QImageWidget() {
    click = 0, x0 = 0, y0 = 0, x1 = 0, y1 = 0;
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

void QImageWidget::circlePlotPoints(QImage &image, int xCenter, int yCenter, int x, int y) {
    image.setPixel(xCenter + x, yCenter + y, qRgb(255, 255, 255));
    image.setPixel(xCenter - x, yCenter + y, qRgb(255, 255, 255));
    image.setPixel(xCenter + x, yCenter - y, qRgb(255, 255, 255));
    image.setPixel(xCenter - x, yCenter - y, qRgb(255, 255, 255));
    image.setPixel(xCenter + y, yCenter + x, qRgb(255, 255, 255));
    image.setPixel(xCenter - y, yCenter + x, qRgb(255, 255, 255));
    image.setPixel(xCenter + y, yCenter - x, qRgb(255, 255, 255));
    image.setPixel(xCenter - y, yCenter - x, qRgb(255, 255, 255));

}

void QImageWidget::circleMidpoint(QImage &image, int xCenter, int yCenter, int radius) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    circlePlotPoints(image, xCenter, yCenter, x, y);

    while (x < y) {
        x++;
        if (p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
        circlePlotPoints(image, xCenter, yCenter, x, y);
    }
}

void QImageWidget::paintEvent(QPaintEvent *) {
    QImage image(DL, DL, QImage::Format_RGB32);
    double r = sqrt((x1 - x0)*(x1 - x0)+(y1 - y0)*(y1 - y0));
    circleMidpoint(image, x0, y0, int(r));
    QPainter paint(this);
    paint.drawImage(0, 0, image);


}