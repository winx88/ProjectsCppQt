#include<iostream>
#include<QApplication>
#include<QPainter>
#include<QWidget>
#include<QPainter>
#include<QImage>
#include<cstdlib>
#include<cmath>
#include"Point.h"
#define W 500
#define Pi 3.1415

using namespace std;


class MyWidget : public QWidget{
   public:
   QImage *image;
   QImage *tekstura;

   unsigned char* imageT;
   unsigned char *teksT;

   double Zbufor[W][W];
   Point swiatlo;
   double macierzPersp[4][4];
   double fov;
   double near;
   double far;
   double aspect;
   double K;

   MyWidget();

   void paintEvent(QPaintEvent *);
   Point rzutPersp(double[4][4],double[4]);
   void rysuj(Point, Point);
   void kula(Point,int);
   double skalarny(double[3],double[3]);
   double dlugosc(double[3]);
   double max(double,double);
   double min(double,double);
   Point oswietlenie(double[4],double[3], Point);
   void obrot(double *,double,double);
};
