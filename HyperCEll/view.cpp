#include "view.h"
#include "controller.h"


#include <QtDebug>

View::View()
{
    setStyleSheet("background-color:white");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);
    QHBoxLayout * MainLayout = new QHBoxLayout(this);

    connect(this,SIGNAL(gamePause(bool),)

    resize(800, 600);
}

void View::keyPressEvent(QKeyEvent* e)
{
    if(!e->isAutoRepeat())
    {
        switch (e->key()) {
        case Qt::Key_W:
            View::keysStatment=View::keysStatment | 0b00000001;
            break;

        case Qt::Key_A:
            View::keysStatment=View::keysStatment | 0b00000010;
            break;

        case Qt::Key_S:
            View::keysStatment=View::keysStatment | 0b00000100;
            break;

        case Qt::Key_D:
            View::keysStatment=View::keysStatment | 0b00001000;
            break;
        case Qt::Key_Escape:
            if(View::keysStatment & 0b10000000 == 0b10000000)

            break;

        default:
            break;
        }
     }
}

void View::keyReleaseEvent(QKeyEvent* e)
{
    if(!e->isAutoRepeat())
    {
        switch (e->key()) {
        case Qt::Key_W:
            View::keysStatment=View::keysStatment & 0b11111110;
            break;
        case Qt::Key_A:
            View::keysStatment=View::keysStatment & 0b11111101;
            break;

        case Qt::Key_S:
            View::keysStatment=View::keysStatment & 0b11111011;
            break;

        case Qt::Key_D:
            View::keysStatment=View::keysStatment & 0b11110111;
            break;

        default:
            break;
        }
     }
}
