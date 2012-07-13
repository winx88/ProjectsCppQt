#include "QImageWidget.h"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QImageWidget widget;
    widget.show();
    widget.setGeometry(0, 0, DL, DL);

    return app.exec();
}
