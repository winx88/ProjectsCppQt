#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(800, 500);
    widget.show();
    return app.exec();

}