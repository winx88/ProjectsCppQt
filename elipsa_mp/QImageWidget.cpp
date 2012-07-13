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
 void QImageWidget::PlotEllipse(QImage &image, int xC, int yC, int x, int y){
  image.setPixel(xC+x,yC+y,qRgb(255, 255, 255));
    image.setPixel(xC+x,yC-y,qRgb(255, 255, 255));
    image.setPixel(xC-x,yC+y,qRgb(255, 255, 255));
    image.setPixel(xC-x,yC-y,qRgb(255, 255, 255));
}
void QImageWidget::DrawEllipse (QImage &image ,int xC,int yC,int a, int b){
    int x,y,P,dPe,dPs,dPse,d2Pe,d2Ps,d2Pse;
    x=0;
    y=b;
    P=(b*b)+((a*a)*(1-4*b)-2)/4;
    dPe=3*(b*b);
    d2Pe=2*(b*b);
    dPse=dPe-2*(a*a)*(b-1);
    d2Pse=d2Pe + 2*(a*a);
    PlotEllipse(image,xC,yC,x,y);
    while(dPse<(2*(a*a)+3*(b*b))){
        if(P<0){
            P=P+dPe;
            dPe=dPe+d2Pe;
            dPse=dPse+d2Pe;
        }
        else{
            P=P+dPse;
            dPe=dPe+d2Pe;
            dPse=dPse+d2Pse;
            y--;
        }
    x++;
    PlotEllipse(image,xC,yC,x,y);
    }
    P=P-((a*a)*(4*y-3)+((b*b)*(4*x+3)+2)/4);
    dPs=(a*a)*(3-2*y);
    dPse=2*(b*b)+3*(a*a);
    d2Ps=2*(a*a);
    while(y>0){
        if(P>0){
            P=P+dPe;
            dPe=dPe+d2Ps;
            dPse=dPse+d2Ps;
        }
        else{
            P=P+dPse;
            dPe=dPe+d2Ps;
            dPse=dPse+d2Pse;
            x++;
        }
        y--;
        PlotEllipse(image,xC,yC,x,y);
    }
}

void QImageWidget::paintEvent(QPaintEvent *) {
    QImage image(DL, DL, QImage::Format_RGB32);
    double r = sqrt((x1 - x0)*(x1 - x0)+(y1 - y0)*(y1 - y0));
    DrawEllipse (image,x0,y0,r,30);
    QPainter paint(this);
    paint.drawImage(0, 0, image);


}