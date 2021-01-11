#include "dialog.h"
MyDialog::MyDialog()
{
    editLayout = new QFormLayout;
    editLayout->addRow(new QLabel(tr("Are you sure that you want to exit paint?")));
    editWidget = new QWidget;
    editWidget->setLayout(editLayout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No);
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(editWidget);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle("Close");
}
