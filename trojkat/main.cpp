#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(_PIC_X << 1, _PIC_Y);
    widget.show();
    return app.exec();
}