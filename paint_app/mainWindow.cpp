#include "mainWindow.h"
#include "dialog.h"

MyMainWindow::MyMainWindow(QWidget *parent):QMainWindow(parent)
{
    central = new Widget();
    setCentralWidget(central);

    FullScreen = new QAction(tr("&Fullscreen..."), this);
    FullScreen->setShortcut(tr("F11"));
    connect(FullScreen, &QAction::triggered, this,
    &MyMainWindow::ViewFullScreen);

    ViewMenu = menuBar()->addMenu(tr("&View"));
    ViewMenu->addAction(FullScreen);

    setWindowTitle("My Paint");
}
void MyMainWindow::ViewFullScreen()
{
    setWindowState(Qt::WindowFullScreen);
}
void MyMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Escape:
            setWindowState(Qt::WindowNoState);
        break;
    }
}
void MyMainWindow::closeEvent(QCloseEvent *event)
{
    MyDialog closeDialog;
    int ret = closeDialog.exec();
    if( ret == QDialog::Accepted )
        event->accept();
    else
        event->ignore();
}
