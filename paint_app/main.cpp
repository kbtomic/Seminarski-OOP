#include "widget.h"
#include "mainWindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyMainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
