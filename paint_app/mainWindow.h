#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "widget.h"

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MyMainWindow(QWidget* parent = 0);
    Widget* central;

    void ViewFullScreen();

    QMenu* ViewMenu;
    QAction* FullScreen;

    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
