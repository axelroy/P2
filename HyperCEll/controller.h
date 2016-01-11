#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "cell.h"
#include "customscene.h"
#include "view.h"
#include "collider.h"
#include "settler.h"
#include "utility.h"
#include "borderguard.h"
#include <QWidget>

#include <QTimeLine>
#include <QHBoxLayout>
// todo méthode qui retourne le centre de la cellule

namespace Ui {
class Controller;
}

class Controller : public QWidget
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();

private:
    // 0-> w
    // 1-> a
    // 2-> s
    // 3-> d
    char keysStatment;
    CustomScene* map;
    View* camera;
    Cell *mainCell;
    int nCells;
    Collider* mainCollider;
    Settler* settler;

protected:

    void timerEvent(QTimerEvent* e);

};

#endif // CONTROLLER_H
