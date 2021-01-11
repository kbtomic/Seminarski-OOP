#ifndef WIDGET_H
#define WIDGET_H
#include <QtWidgets>
#include <cmath>
class Widget : public QWidget
{
    Q_OBJECT
public:
    QImage image;

    QLabel *label;
    QSlider *slider;
    QPushButton *bSave;
    QPushButton *bOpen;
    QPushButton *bElipse;
    QPushButton *bRectangle;
    QPushButton *bColorPalette;
    QPushButton *bRubber;

    QCursor cursorLabel;
    QCursor cursorButton;
    QCursor cursorSlider;

    QColor color;
    QPoint current;
    QBrush brush;
    QPen pen;
    int diametr;
    QList<QPoint> list;

    QString fileName;

    QPoint one;
    QPoint two;

    bool isPressed;
    bool drawRectangle;
    bool drawElipse;
    bool drawRubber;

    Widget(QWidget *parent = 0);

public slots:
    void Save();
    void Open();
    void Elipse();
    void Rectangle();
    void SetColor();
    void Rubber();
    void SetSize(int);

    void paintEvent(QPaintEvent *)override;
    void mouseMoveEvent(QMouseEvent *)override;
    void mousePressEvent(QMouseEvent *)override;
    void mouseReleaseEvent(QMouseEvent *)override;
};
#endif // WIDGET_H
