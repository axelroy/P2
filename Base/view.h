#ifndef VIEW_H
#define VIEW_H

#include "CustomScene.h"
#include <QGraphicsView>
#include <QKeyEvent>
#include "Cell.h"
#include <QLayout>

class View : public QGraphicsView
{
public:
    View();
    //View(QGraphicsScene& scene);


private:
    // 0-> w
    // 1-> a
    // 2-> s
    // 3-> d
    char keysStatment;
    CustomScene* myScene;
    Cell *mainCell;



protected:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    void timerEvent(QTimerEvent* e);
};

#endif // VIEW_H
