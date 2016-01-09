#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QHBoxLayout>

class View : public QGraphicsView
{
public:
    View();
    static char keysStatment;
protected:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
};

#endif // VIEW_H
