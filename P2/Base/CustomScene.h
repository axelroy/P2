#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "cell.h"

class View;

class CustomScene: public QGraphicsScene
{
public:
    CustomScene();
    //Scene(View* parent = 0);
    void MoveCell(double x, double y, Cell * cell);
    //peuple la Scene à l'initialisation
    void initSettling(int nCells);
    //Detecte et gère les collisions
    void collider(Cell * collidingCell);
    //parcours la deadlist et replace, modifie les cellules
    void settler(Cell * refCell);
private:

    View* myView;

    QList<Cell*> deadList;

    int randInt(int low, int high);



    //Donne à la deadlist les cellules trop éloignées de la cellule principale
    void borderguard();

};

#endif // SCENE_H
