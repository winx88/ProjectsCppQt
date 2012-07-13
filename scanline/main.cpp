#include "QImageWidget.h"
using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QImageWidget widget;
    widget.resize(DL, DL);
    widget.show();



    return app.exec();
}