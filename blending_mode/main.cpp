#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(400, 400);
    widget.show();
    return app.exec();
}