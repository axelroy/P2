#ifndef SCENE_H
#define SCENE_H
#include <QQueue>
#include <QGraphicsScene>
#include "cell.h"


class View;

class CustomScene: public QGraphicsScene
{
public:
    CustomScene(Cell *refCell);
    //Scene(View* parent = 0);
    void MoveCell(double x, double y, Cell * cell);
    //peuple la Scene à l'initialisation
    void initSettling(int nCells, Cell * refCell);
    //Detecte et gère les collisions
    void collider(Cell * collidingCell);
    //parcours la deadlist et replace, modifie les cellules
    void settler(Cell * refCell);

    void giveProperties(Cell * cell, Cell * refCell, int minRange);

    void borderguard();


    //Definition propriétés cellules à déplacer dans la classe Cell ?
    static int randomCell;

    static int ProbMalusCell;
    static int ProbBonusCell;
    static double BaseSpeedCell;

    static char autorizedDirection;


private:

    View* myView;

    QQueue<Cell*> deadList;

    int randInt(int low, int high);

    Cell *refCell;

    int area;

public slots:
    //Donne à la deadlist les cellules trop éloignées de la cellule principale



};

#endif // SCENE_H
