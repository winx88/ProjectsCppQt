#include "MyWidget.h"

int main(int argc, char *argv[]){
   QApplication app(argc,argv);
   MyWidget widget;
   widget.show();
   widget.setGeometry(0, 0, W, W);
   return app.exec();
}
