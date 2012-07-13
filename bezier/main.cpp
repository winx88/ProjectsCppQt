#include "QImageWidget.h"
using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QImageWidget widget;
    widget.setGeometry(0, 0, DL, DL);
    widget.show();


    return app.exec();
}