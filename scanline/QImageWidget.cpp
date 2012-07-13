#include "QImageWidget.h"

using namespace std;

void QImageWidget::paintEvent(QPaintEvent *) {

    myImage image(DL, DL, QImage::Format_RGB32);

    image.clean();

    tab_edge = NULL;
    tab_range = NULL;

    if (points.size() > 0) {
        drawSquare(image);
        if (points.size() > 2) {
            updateEdge(points);

            upoints.assign(points.begin(), points.end());
            sortPoint();
            addPoint();
            sortPoint();
        }

        if (points.size() > 2) {
            countRange();
        }

    }

    for (unsigned int i = 0; i < points.size(); i++)
        if (i == (points.size() - 1)) {
            image.line(points[i].x, points[i].y, points[0].x, points[0].y);
            image.line(points[i].x - 1, points[i].y, points[0].x - 1, points[0].y);
        } else {
            image.line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            image.line(points[i].x - 1, points[i].y, points[i + 1].x - 1, points[i + 1].y);
        }
    if (points.size() > 2) {
        for (unsigned int j = 0; j < (upoints.size() - 1); j++) {
            sortEdges(j);

            if (fill && (upoints[j].y != upoints[j + 1].y)) drawRange(upoints[j].y, upoints[j + 1].y, j, tab_range, image);

            for (unsigned int i = 0; i < points.size(); i++)
                if (i == (points.size() - 1)) {
                    image.line(points[i].x, points[i].y, points[0].x, points[0].y);
                    image.line(points[i].x - 1, points[i].y, points[0].x - 1, points[0].y);
                } else {
                    image.line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
                    image.line(points[i].x - 1, points[i].y, points[i + 1].x - 1, points[i + 1].y);
                }
            drawSquare(image);

        }
    }

    QPainter paint(this);
    paint.drawImage(0, 0, image);
}

void QImageWidget::addPoint() {
    bool b1, b2;
    b1 = false;
    b2 = false;

    for (unsigned int i = 0; i < points.size(); i++) {
        for (unsigned int j = i; j < points.size(); j++) {

            Point tmp;
            if (i != j) {
                solve(tab_edge[i], tab_edge[j], tmp);
                if (!vertex(tmp)) {
                    b2 = false;
                    b1 = false;
                    if ((tmp.y > tab_edge[i].p0.y) && (tmp.y < tab_edge[i].p1.y) && (tmp.y > tab_edge[j].p0.y) && (tmp.y < tab_edge[j].p1.y)) {
                        b1 = true;
                        b2 = true;
                    }
                    if ((b1) && (b2)) upoints.push_back(tmp);
                }
            }
        }
    }

}

bool QImageWidget::vertex(Point& p) {

    for (unsigned int i = 0; i < points.size(); i++) {
        if ((points[i].x == p.x) && (points[i].y == p.y)) return true;
    }
    return false;
}

void QImageWidget::solve(edge k0, edge k1, Point &p) {

    double b0, b1;
    double w, wx, wy;

    b0 = (double) k0.p0.y - ((double) k0.p0.x * k0.m);
    b1 = (double) k1.p0.y - ((double) k1.p0.x * k1.m);

    w = k1.m - k0.m;

    if (w == 0.0) {
        p.x = -10;
        p.y = -10;
    } else {
        wx = b0 - b1;
        wy = k1.m * b0 - k0.m*b1;

        double dz1, dz2;

        dz1 = wx / w;
        dz2 = wy / w;

        p.x = round(dz1);
        p.y = round(dz2);
    }

    if (k0.p0.x == k0.p1.x) {
        p.x = k0.p0.x;
        p.y = k1.m * p.x + b1;
    }
    if (k0.p0.y == k0.p1.y) {
        p.y = k0.p0.y;
        p.x = (((double) p.y - b1) / k1.m);
    }
    if (k1.p0.x == k1.p1.x) {
        p.x = k1.p0.x;
        p.y = k0.m * p.x + b0;
    }
    if (k1.p0.y == k1.p1.y) {
        p.y = k1.p0.y;
        p.x = (((double) p.y - b0) / k0.m);
    }


    if ((k0.p0.x == k0.p1.x) && (k1.p0.y == k1.p1.y)) {
        p.x = k0.p0.x;
        p.y = k1.p0.y;
    }
    if ((k0.p0.y == k0.p1.y) && (k1.p0.x == k1.p1.x)) {
        p.x = k1.p0.x;
        p.y = k0.p0.y;
    }

}

void QImageWidget::changeEdge(edge &k0, edge &k1) {

    edge tmp;

    tmp.p0.x = k0.p0.x;
    tmp.p0.y = k0.p0.y;
    tmp.p1.x = k0.p1.x;
    tmp.p1.y = k0.p1.y;
    tmp.m = k0.m;
    k0.p0.x = k1.p0.x;
    k0.p0.y = k1.p0.y;
    k0.p1.x = k1.p1.x;
    k0.p1.y = k1.p1.y;
    k0.m = k1.m;
    k1.p0.x = tmp.p0.x;
    k1.p0.y = tmp.p0.y;
    k1.p1.x = tmp.p1.x;
    k1.p1.y = tmp.p1.y;
    k1.m = tmp.m;
}

void QImageWidget::sortEdges(int i) {

    int min;
    Point tmp0;
    Point pkt1(100, ((upoints[i].y + upoints[i + 1].y) / 2));
    Point pkt2(200, ((upoints[i].y + upoints[i + 1].y) / 2));
    edge tmp_edge(pkt1, pkt2);

    for (unsigned int k = 0; k < tab_range[i].size(); k++) {
        min = k;
        for (unsigned int j = k; j < tab_range[i].size(); j++) {

            solve(tab_range[i][min], tmp_edge, tmp0);

            Point tmp1;
            solve(tab_range[i][j], tmp_edge, tmp1);

            if ((tmp0.x - tmp1.x) > 0) min = j;
        }
        changeEdge(tab_range[i][min], tab_range[i][k]);
    }

}

void QImageWidget::changePoint(Point &p0, Point &p1) {
    Point tmp;
    tmp = p0;
    p0 = p1;
    p1 = tmp;
}

bool cmp(Point p0, Point p1) {

    return (p0.y < p1.y);
}

void QImageWidget::sortPoint() {
    sort(upoints.begin(), upoints.end(), cmp);
}

void QImageWidget::updateEdge(vector<Point> w) {
    if (!tab_edge) delete [] tab_edge;

    tab_edge = new edge[w.size()];
    for (unsigned int i = 0; i < w.size(); i++) {
        if (i != (w.size() - 1)) {
            Point p0(w[i].x, w[i].y), p1(w[i + 1].x, w[i + 1].y);
            if (p0.y < p1.y) {
                edge k1(p0, p1);
                tab_edge[i] = k1;
            } else {
                edge k1(p1, p0);
                tab_edge[i] = k1;
            }
        } else {
            Point p3(w[i].x, w[i].y), p4(w[0].x, w[0].y);
            if (p3.y < p4.y) {
                edge k2(p3, p4);
                tab_edge[i] = k2;
            } else {
                edge k2(p4, p3);
                tab_edge[i] = k2;
            }
        }
    }
}

void QImageWidget::countRange() {
    if (!tab_range) delete[] tab_range;

    tab_range = new vector<edge>[upoints.size() - 1];

    int size;
    size = upoints.size() - 1;

    for (int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < points.size(); j++) {

            Point tmp0;
            Point pkt1(100, (int) (((double) upoints[i].y + (double) upoints[i + 1].y) / 2.0));
            Point pkt2(200, (int) (((double) upoints[i].y + (double) upoints[i + 1].y) / 2.0));
            edge tmp_edge(pkt1, pkt2);

            solve(tmp_edge, tab_edge[j], tmp0);

            if ((tmp0.y > upoints[i].y) && (tmp0.y < upoints[i + 1].y)) {
                if ((tab_edge[j].p0.y < tmp0.y) && (tab_edge[j].p1.y > tmp0.y)) tab_range[i].push_back(tab_edge[j]);
            }
        }
    }
}

void QImageWidget::drawRange(int ymin, int ymax, int i, vector<edge> *tab_ranges, myImage& image) {

    double x0, x1, y;
    double b0, b1;

    for (unsigned int k = 0; k < tab_ranges[i].size(); k = k + 2) {

        b0 = tab_ranges[i][k].p0.y - tab_ranges[i][k].m * tab_ranges[i][k].p0.x;
        b1 = tab_ranges[i][k + 1].p0.y - tab_ranges[i][k + 1].m * tab_ranges[i][k + 1].p0.x;


        if (tab_ranges[i][k].m != 0)
            x0 = ((double) ymin - b0) / tab_ranges[i][k].m;
        else
            x0 = tab_ranges[i][k].p0.x;

        if (tab_ranges[i][k + 1].m != 0)
            x1 = ((double) ymin - b1) / tab_ranges[i][k + 1].m;
        else
            x1 = tab_ranges[i][k + 1].p0.x;

        QRgb kolor;
        kolor = qRgb(0, 255, 0);
        for (y = ymin; y < ymax; y++) {
            if (tab_ranges[i][k].m != 0)
                x0 = x0 + 1.0 / (tab_ranges[i][k].m);
            if (tab_ranges[i][k + 1].m != 0)
                x1 = x1 + 1.0 / (tab_ranges[i][k + 1].m);
            if ((x0 != 0) && (x1 != 0))
                image.line(floor(x0 + 0.5), y, floor(x1 + 0.5), y);
            if (y == (upoints[upoints.size() - 1].y - 1))
                image.line(floor(x0 + 0.5), y, floor(x1 + 0.5), y);
        }
    }
}

bool QImageWidget::controlPoint(Point p) {
    for (unsigned int i = 0; i < points.size(); i++) {
        if ((p.x > (points[i].x - 5)) && (p.x < (points[i].x + 5)) && (p.y > (points[i].y - 5)) && (p.y < (points[i].y + 5))) {
            positions = i;
            return true;
        }
    }
    positions = points.size();
    return false;

}

void QImageWidget::deletePoint(int pos) {
    points.erase(points.begin() + pos);
}

void QImageWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->p.x = event->x();
        this->p.y = event->y();
        fill = true;
        if (!controlPoint(p)) {
            points.push_back(p);
            update();
        }

    } else {
        this->p.x = event->x();
        this->p.y = event->y();
        if (controlPoint(p)) {
            deletePoint(positions);
            positions = points.size();
            update();
        }
        fill = true;
        update();
    }

}

void QImageWidget::mouseMoveEvent(QMouseEvent *event) {
    points[positions].x = event->pos().x();
    points[positions].y = event->pos().y();
    fill = false;
    update();
}

void QImageWidget::mouseReleaseEvent(QMouseEvent *) {
    fill = true;
    update();
}

void QImageWidget::drawSquare(myImage &image) {
    for (unsigned int i = 0; i < points.size(); i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                image.setPixel(points[i].x - 4 + j, points[i].y - 4 + k, qRgb(255, 0, 0));
            }
        }
    }
}
