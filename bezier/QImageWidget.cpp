#include "QImageWidget.h"
using namespace std;

QImageWidget::QImageWidget(QWidget *parent) : QWidget(parent) {
    circlePressed = false;

    setPalette(QPalette(QColor(250, 250, 250)));
    setAutoFillBackground(true);
}

void QImageWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0));

    for (unsigned int i = 0; i < positions.size(); i++)
        drawSquare(painter, positions[i]);
    if (positions.size() > 1)
        bezier(painter, positions);

    painter.setPen(QColor(255, 0, 0));
    if (positions.size() > 2)
        for (unsigned int i = 1; i < positions.size(); i++)
            bresenhamLine(painter, positions[i - 1], positions[i]);
}

bool QImageWidget::contains(const QPoint &pos) {
    for (unsigned int i = 0; i < positions.size(); i++) {
        if (pow(pos.x() - positions[i].x(), 2)
                + pow(pos.y() - positions[i].y(), 2) <= 25) {
            currentPressedCircle = &positions[i];
            currentPressedPosition = i;
            return true;
        }
    }
    return false;
}

float QImageWidget::bernstein(int n, int i, float u) {
    return newton(n, i) * pow(u, i) * pow(1 - u, n - i);
}

void QImageWidget::bezier(QPainter &painter, vector<QPoint> &pos) {
    unsigned int n = pos.size() - 1;
    float x, y;
    list <QPoint> points;
    QPoint point, point2;

    for (float u = 0.00; u < 1.00; u += 0.01) {
        x = 0;
        y = 0;
        for (unsigned int i = 0; i <= n; i++) {
            x += bernstein(n, i, u) * pos[i].x();
            y += bernstein(n, i, u) * pos[i].y();
        }

        point.setX(round(x));
        point.setY(round(y));
        points.push_front(point);
        if (points.size() > 1) {
            point2 = points.back();
            bresenhamLine(painter, point, point2);
            points.pop_back();
        }
    }
}

int QImageWidget::newton(int n, int k) {
    return silnia(n) / (silnia(n - k) * silnia(k));
}

int QImageWidget::silnia(int n) {
    if (n == 0)
        return 1;
    int wynik = 1;
    for (int i = 1; i <= n; i++) {
        wynik *= i;
    }
    return wynik;
}

void QImageWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (contains(event->pos()))
            circlePressed = true;
        else
            if (positions.size() < 13)
            positions.push_back(event->pos());
        update();
    }
    if (event->button() == Qt::RightButton) {
        if (contains(event->pos())) {
            positions.erase(positions.begin() + currentPressedPosition);
            update();
        }
    }
}

void QImageWidget::mouseMoveEvent(QMouseEvent *event) {
    if (circlePressed) {
        (*currentPressedCircle).setX(event->pos().x());
        (*currentPressedCircle).setY(event->pos().y());
        update();
    }
}

void QImageWidget::mouseReleaseEvent(QMouseEvent *) {
    circlePressed = false;
}

void QImageWidget::bresenhamLine(QPainter &painter, QPoint &begin, QPoint &end) {
    int x1 = begin.x(), y1 = begin.y(), x2 = end.x(), y2 = end.y();
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

    painter.drawPoint(x, y);

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
            painter.drawPoint(x, y);
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

            painter.drawPoint(x, y);
        }
    }
}

void QImageWidget::drawSquare(QPainter &painter, QPoint &pos) {
    int x, y;
    x = pos.x();
    y = pos.y();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            painter.drawPoint(x + j, y + i);
            painter.drawPoint(x + i, y + j);
            painter.drawPoint(x - i, y - j);
            painter.drawPoint(x - j, y + i);
            painter.drawPoint(x + j, y - i);
        }
    }

}
