#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class QKeyEvent;

class View : public QGraphicsView
{
public:
    static char keysStatment;
    View(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
signals:
    void wheelEvent(QWheelEvent* e);
};

#endif // VIEW_H
