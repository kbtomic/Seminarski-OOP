#ifndef DIALOG_H
#define DIALOG_H
#include "widget.h"
class MyDialog : public QDialog
{
public:
    MyDialog();
    QVBoxLayout* mainLayout;
    QDialogButtonBox* buttonBox;
    QFormLayout* editLayout;
    QWidget* editWidget;
};
#endif // DIALOG_H
