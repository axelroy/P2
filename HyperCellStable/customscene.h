/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : CustomScene
 * Resumé           : QGraphicsScene avec une méthode pour bouger les cellules dans la scene
 * version          : 0.0
 */

#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <cell.h>
#include <QtDebug>

class CustomScene: public QGraphicsScene
{
public:
    CustomScene(QObject * parent = 0);

    void MoveCell(double x, double y, Cell * cell);
};

#endif // CUSTOMSCENE_H
