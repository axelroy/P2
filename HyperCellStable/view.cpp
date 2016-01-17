#include "view.h"
#include "controller.h"
#include <QKeyEvent>
#include "config.h"


/*============================================*/
//  STATIC
/*============================================*/

char View::keysStatment = 0;


/*============================================*/
//  CONSTRUCTOR / DESTRUCTOR
/*============================================*/

View::View(QWidget *parent) : QGraphicsView(parent)
{
    setStyleSheet("background-image:url(:/Ressources/background.jpg)");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);

    resize(800, 600);
}

/*============================================*/
//  OVERRIDE
/*============================================*/

void View::keyPressEvent(QKeyEvent* e)
{
    //todo fucking hard code
    if(!e->isAutoRepeat())
    {
        switch (e->key())
        {
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
            if((View::keysStatment & 0b10000000) == 0b10000000)

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
        switch (e->key())
        {
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

void View::wheelEvent(QWheelEvent *e)
{
    if (e->angleDelta().y()>0)
    {
        scale(1 + Config::WHEEL_SCALE, 1 + Config::WHEEL_SCALE);
    }
    else
    {
        scale(1 - Config::WHEEL_SCALE, 1 - Config::WHEEL_SCALE);
    }
}
