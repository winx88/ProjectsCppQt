#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(1100,260);
    widget.show();
    return app.exec();

}