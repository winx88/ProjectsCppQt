/* 
 * File:   MyWidget.h
 * Author: winx
 *
 * Created on 26 maj 2010, 14:42
 */
#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

#include <QtGui/QApplication>
#include<QHBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include"Point3d.h"
#include "Point.h"
#include <vector>
#include <iostream>
#include<cmath>
#define Pi 3.1415
using namespace std;

class MyWidget : public QWidget {
public:
    MyWidget();
    MyWidget(const MyWidget& orig);
    void paintEvent(QPaintEvent*);
    void policz(int,int,int);
    void czysc(vector<Point>&);    
    void rysuj(int,int,int,int,int,int,int);
    bool S(int,int,int,int,int,int);
private:
    vector<Point> tabPoint;
    vector<Point3d> tabPoint3d;
    vector<Point3d> tabO3d;
    double cosin;
    double sinus;
    double D;
    int K;
    Point3d SR;    
    
    unsigned char *p1;
    QHBoxLayout *o;
    QImage *p;

};

#endif	/* _MYWIDGET_H */

