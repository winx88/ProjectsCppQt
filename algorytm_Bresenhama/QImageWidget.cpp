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

void QImageWidget::BresenhamLine(QImage &image, int x0, int y0, int x1, int y1) {

    image.fill(0);
    int d, dx, dy, ai, bi, xi, yi;
    int x = x0, y = y0;
    if (x0 < x1){
        xi = 1;
        dx = x1 - x0;
    } else {
        xi = -1;
        dx = x0 - x1;
    }
    if (y0 < y1){
        yi = 1;
        dy = y1 - y0;
    } else {
        yi = -1;
        dy = y0 - y1;
    }
    image.setPixel(x, y, qRgb(255, 255, 255));

    if (dx > dy){
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;

        while (x != x1) {
            if (d >= 0){
                x += xi;
                y += yi;
                d += ai;
            } else {
                d += bi;
                x += xi;
            }
            image.setPixel(x, y, qRgb(255, 255, 255));
        }
    } else{
        ai = (dx - dy) * 2;
        bi = dx * 2;
        d = bi - dy;

        while (y != y1) {
            if (d >= 0){
                x += xi;
                y += yi;
                d += ai;
            } else {
                d += bi;
                y += yi;
            }
            image.setPixel(x, y, qRgb(255, 255, 255));
        }
    }

}

void QImageWidget::paintEvent(QPaintEvent *) {
    QImage image(DL, DL, QImage::Format_RGB32);
    BresenhamLine(image, x0, y0, x1, y1);
    QPainter paint(this);
    paint.drawImage(0, 0, image);


}
