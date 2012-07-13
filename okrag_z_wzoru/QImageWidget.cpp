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

void QImageWidget::circleSimple(QImage &image, int xCenter, int yCenter, int radius) {
        int x, y, r2;

        r2 = radius * radius;
        for (x = -radius; x <= radius; x++) {
            y = floor((sqrt(r2 - x*x) + 0.5));
            image.setPixel(xCenter + x, yCenter + y,qRgb(255, 255, 255));
            image.setPixel(xCenter + x, yCenter - y,qRgb(255, 255, 255));
        }
        for (y = -radius; y <= radius; y++) {
            x = floor((sqrt(r2 - y*y) + 0.5));
            image.setPixel(xCenter + x, yCenter + y,qRgb(255, 255, 255));
            image.setPixel(xCenter - x, yCenter + y,qRgb(255, 255, 255));
        }

}

void QImageWidget::paintEvent(QPaintEvent *) {
    QImage image(DL, DL, QImage::Format_RGB32);
    double r = sqrt((x1 - x0)*(x1 - x0)+(y1 - y0)*(y1 - y0));
    circleSimple(image, x0, y0, int(r));
    QPainter paint(this);
    paint.drawImage(0, 0, image);


}