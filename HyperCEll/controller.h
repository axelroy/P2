#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "cell.h"
#include "customscene.h"
#include "view.h"
#include "collider.h"
#include "settler.h"
#include "utility.h"
#include "borderguard.h"
#include "ia.h"
#include <QWidget>

#include <QTimeLine>
#include <QHBoxLayout>
// todo méthode qui retourne le centre de la cellule
// méthode dans cell de désactivation des cellules / activation

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
    char keysStatment;
    CustomScene* map;
    View* camera;
    Cell *mainCell;
    int nCells;
    Collider* mainCollider;
    Settler* settler;
    Cell* cTest;
    Ia* testIa;

protected:

    void timerEvent(QTimerEvent* e);


};

#endif // CONTROLLER_H
