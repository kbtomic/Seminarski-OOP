#include "widget.h"

Widget::Widget(QWidget *parent): QWidget(parent)
{
    resize(800,400);

    slider = new QSlider(Qt::Horizontal);
    slider->setToolTip("Adjust pen");
    slider->setMaximumHeight(20);
    slider->setMaximumWidth(800);
    slider->setMinimum(1);
    slider->setMaximum(30);

    bSave = new QPushButton;
    bSave->setToolTip("Save");
    bSave->setIcon(QIcon(":/save.png"));
    bSave->setIconSize(QSize(100,20));
    bSave->setFixedSize(80,30);

    bOpen = new QPushButton;
    bOpen->setToolTip("Open");
    bOpen->setIcon(QIcon(":/open.png"));
    bOpen->setIconSize(QSize(100,20));
    bOpen->setFixedSize(80,30);

    bElipse = new QPushButton;
    bElipse->setToolTip("Select Elipse");
    bElipse->setIcon(QIcon(":/elipse2.png"));
    bElipse->setIconSize(QSize(100,20));
    bElipse->setFixedSize(80,30);

    bRectangle = new QPushButton;
    bRectangle->setToolTip("Select Rectangle");
    bRectangle->setIcon(QIcon(":/rectangle2.png"));
    bRectangle->setIconSize(QSize(100,50));
    bRectangle->setFixedSize(80,30);

    bColorPalette = new QPushButton;
    bColorPalette->setToolTip("Set color");
    bColorPalette->setIcon(QIcon(":/palette.png"));
    bColorPalette->setIconSize(QSize(60,20));
    bColorPalette->setFixedSize(80,30);

    bRubber = new QPushButton;
    bRubber->setToolTip("Select Rubber");
    bRubber->setIcon(QIcon(":/rubber.png"));
    bRubber->setIconSize(QSize(60,20));
    bRubber->setFixedSize(80,30);

    label = new QLabel;
    label->setFrameStyle(QFrame::Sunken);
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vButtonLayout = new QVBoxLayout;
    vButtonLayout->addWidget(bSave);
    vButtonLayout->addWidget(bOpen);
    vButtonLayout->addWidget(bElipse);
    vButtonLayout->addWidget(bRectangle);
    vButtonLayout->addWidget(bColorPalette);
    vButtonLayout->addWidget(bRubber);
    hLayout->addWidget(label);
    hLayout->addLayout(vButtonLayout);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(slider,Qt::AlignBottom);
    vLayout->setAlignment(slider,Qt::AlignBottom);
    setLayout(vLayout);

    cursorLabel = QCursor(QPixmap(":/cursor_brush.png"));
    label->setCursor(cursorLabel);

    cursorButton = QCursor(Qt::PointingHandCursor);
    bSave->setCursor(cursorButton);
    bOpen->setCursor(cursorButton);
    bElipse->setCursor(cursorButton);
    bRectangle->setCursor(cursorButton);
    bColorPalette->setCursor(cursorButton);
    bRubber->setCursor(cursorButton);

    cursorSlider = QCursor(Qt::SizeHorCursor);
    slider->setCursor(cursorSlider);

    connect(bSave,SIGNAL(clicked(bool)),SLOT(Save()));
    connect(bOpen,SIGNAL(clicked(bool)),SLOT(Open()));
    connect(bElipse,SIGNAL(clicked(bool)),SLOT(Elipse()));
    connect(bRectangle,SIGNAL(clicked(bool)),SLOT(Rectangle()));
    connect(bColorPalette,SIGNAL(clicked(bool)),SLOT(SetColor()));
    connect(bRubber,SIGNAL(clicked(bool)),SLOT(Rubber()));
    connect(slider,SIGNAL(valueChanged(int)),SLOT(SetSize(int)));

    QImage image2(800,400,QImage::Format_RGB32);
    image = image2;
    image.fill(Qt::white);
    label->setPixmap(QPixmap::fromImage(image));
    color = Qt::black;
    brush.setColor(color);
    pen.setColor(color);

    drawRectangle = false;
    drawElipse = false;
    drawRubber = false;
}
void Widget::Save()
{
    fileName = QFileDialog::getSaveFileName(this,"Save Image", "/untitled.png", tr("Images (*.png *.xpm *.jpg)"));
    if(fileName == "")
    {
        return;
    }
    image.save(fileName);
}
void Widget::Open()
{
    fileName = QFileDialog::getOpenFileName(this, "Open Image", ""," *.png *.xpm *.jpg ;; *.jpg ;; *.png ;; All files (*.*)" );
    if(fileName == "")
    {
        return;
    }
    QImage image2;
    image2.load(fileName);
    image = image2.scaled(800,400);
    label->setPixmap(QPixmap::fromImage(image));
}
void Widget::Elipse()
{
    drawElipse = true;
}
void Widget::Rectangle()
{
    drawRectangle = true;
}
void Widget::SetColor()
{
    cursorLabel = QCursor(QPixmap(":/cursor_brush.png"));
    pen.setColor(QColorDialog::getColor());
    brush.setColor(pen.color());
    if(drawRubber == true)
    {
        drawRubber = false;
        bRectangle->setEnabled(true);
        bElipse->setEnabled(true);
        cursorLabel = QCursor(QPixmap(":/cursor_brush.png"));
        label->setCursor(cursorLabel);
        if(pen.color().isValid() == false)
        {
           pen.setColor(Qt::black);
           brush.setColor(pen.color());
        }
    }
}
void Widget::Rubber()
{
    if(drawElipse == true | drawRectangle == true)
    {
        drawElipse = false;
        drawRectangle = false;
    }
    pen.setColor(QColor(Qt::white));
    brush.setColor(pen.color());
    bRectangle->setEnabled(false);
    bElipse->setEnabled(false);
    drawRubber = true;
    cursorLabel = QCursor(QPixmap(":/cursor_rubber.png"));
    label->setCursor(cursorLabel);
}
void Widget::SetSize(int a)
{
    pen.setWidth(a);
}
void Widget::paintEvent(QPaintEvent *)
{
    if(isPressed == true)
    {
        if(drawRectangle == true)
        {
            if(one != two)
            {
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                int w = (two.x() - one.x());
                int h = (two.y() - one.y());
                painter.drawRect(one.x(),one.y(),w,h);
                painter.end();
                isPressed = false;
                drawRectangle = false;
                one.setX(0);
                one.setY(0);
                two=one;
                label->setPixmap(QPixmap::fromImage(image));
                return;
            }
        }
        else if(drawElipse == true)
        {
            if(one != two)
            {
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                int w = (two.x() - one.x());
                int h = (two.y() - one.y());
                painter.drawEllipse(one.x(),one.y(),w,h);
                painter.end();
                isPressed = false;
                drawElipse = false;
                one.setX(0);
                one.setY(0);
                two=one;
                label->setPixmap(QPixmap::fromImage(image));
                return;
            }
        }
        QPainter painter;
        painter.begin(&image);
        if (list.size() < 2) return;
        painter.setPen(pen);
        QList<QPoint>::const_iterator it = list.begin();
        QPoint start = *it;
        it++;
        while(it != list.end())
        {
            QPoint end = *it;
            painter.drawLine(start,end);
            start = end;
            it++;
        }
        painter.end();
        label->setPixmap(QPixmap::fromImage(image));
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (!isPressed)
    {
        return;
    }
    if(drawRectangle == true)
    {
        this->update();
        return;
    }
    else if(drawElipse == true)
    {
        this->update();
        return;
    }
    QPoint tmp = event->pos();
    QPoint tmp_correct;
    tmp_correct.setX(tmp.x()-10);
    tmp_correct.setY(tmp.y()-10);
    list.push_back(tmp_correct);
    this->update();
    current = tmp_correct;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
 if (event->button() == Qt::LeftButton)
    {
        if(drawRectangle == true)
        {
            QToolTip::showText(event->globalPos(),"Keep button pressed and move mouse", this);
            isPressed = true;
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            one=tmp_correct;
            two=one;
            return;
        }
        else if(drawElipse == true)
        {
            QToolTip::showText(event->globalPos(),"Keep button pressed and move mouse", this);
            isPressed = true;
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            one=tmp_correct;
            two=one;
            return;
        }
        isPressed = true;
        QPoint tmp = event->pos();
        QPoint tmp_correct;
        tmp_correct.setX(tmp.x()-10);
        tmp_correct.setY(tmp.y()-10);
        list.push_back(tmp_correct);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(drawRectangle == true)
        {
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            two = tmp_correct;
            this->update();
            cursorLabel = QCursor(QPixmap(":/cursor_crosshair.png"));
            label->setCursor(cursorLabel);
            return;
        }
        else if(drawElipse == true)
        {
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            two = tmp_correct;
            this->update();
            cursorLabel = QCursor(QPixmap(":/cursor_crosshair.png"));
            label->setCursor(cursorLabel);
            return;
        }
        isPressed = false;
        QPoint tmp = event->pos();
        QPoint tmp_correct;
        tmp_correct.setX(tmp.x()-10);
        tmp_correct.setY(tmp.y()-10);
        list.push_back(tmp_correct);
        this->update();
        list.clear();
    }
}
