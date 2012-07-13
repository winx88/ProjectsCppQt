/*
 * File:   main.cpp
 * Author: winx
 *
 * Created on 26 maj 2010, 14:42
 */

#include"MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.show();
    widget.setGeometry(0, 0, 300, 300);

    return app.exec();
}
