
#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <mainwindow.h>
Plotter::Plotter(QWidget *parent) : QWidget(parent)
{

}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;
    MainWindow janela;

    brush.setColor(QColor(255,255,100));
    brush.setStyle(Qt::SolidPattern);

    pen.setColor(QColor(0,0,255));
    pen.setWidth(2);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(0,0,width(),height());

}
