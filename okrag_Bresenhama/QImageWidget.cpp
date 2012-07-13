#include "QImageWidget.h"

QImageWidget::QImageWidget() {
    click = 0, x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    // lol=0;
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

void QImageWidget::PlotCircle(QImage &image, int xCenter, int yCenter, int x, int y) {
    image.setPixel(xCenter + x, yCenter + y, qRgb(255, 255, 255));
    image.setPixel(xCenter + y, yCenter + x, qRgb(255, 255, 255));
    image.setPixel(xCenter - x, yCenter + y, qRgb(255, 255, 255));
    image.setPixel(xCenter + y, yCenter - x, qRgb(255, 255, 255));
    image.setPixel(xCenter - x, yCenter - y, qRgb(255, 255, 255));
    image.setPixel(xCenter - y, yCenter - x, qRgb(255, 255, 255));
    image.setPixel(xCenter + x, yCenter - y, qRgb(255, 255, 255));
    image.setPixel(xCenter - y, yCenter + x, qRgb(255, 255, 255));
}

void QImageWidget::DrawCircle(QImage &image, int xC, int yC, int r) {

    int x = 0, y = r;
    int d = 3 - (2 * r);
    while (x <= y) {

        PlotCircle(image, xC, yC, x, y);

        if (d < 0)
            d += (4 * x) + 6;
        else {
            d += (4 * (x - y)) + 10;
            y -= 1;
        }
        x++;
    }
}

void QImageWidget::paintEvent(QPaintEvent *) {
    QImage image(DL, DL, QImage::Format_RGB32);
    double r = sqrt((x1 - x0)*(x1 - x0)+(y1 - y0)*(y1 - y0));
    DrawCircle(image, x0, y0, r);
    QPainter paint(this);
    paint.drawImage(0, 0, image);


}