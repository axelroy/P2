#ifndef SCENE_H
#define SCENE_H
#include <QQueue>
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
    void initSettling(int nCells, Cell * refCell);
    //Detecte et gère les collisions
    void collider(Cell * collidingCell);
    //parcours la deadlist et replace, modifie les cellules
    void settler(Cell * refCell);

    void giveProperties(Cell * cell, Cell * refCell, int minRange);


private:

    View* myView;

    QQueue<Cell*> deadList;

    int randInt(int low, int high);



    //Donne à la deadlist les cellules trop éloignées de la cellule principale
    void borderguard();


    //Definition propriétés cellules
    int randomCell = 0;

    int ProbMalusCell = 20;
    int ProbBonusCell = 20;

};

#endif // SCENE_H
