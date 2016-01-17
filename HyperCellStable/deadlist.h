/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : DeadList
 * Resumé           : Contient les cellules mortes de l'application
 * version          : 0.0
 */

#ifndef DEADLIST_H
#define DEADLIST_H

#include <QList>

class QMutex;
class Cell;

class DeadList
{
public:
    DeadList();

    static void addCell(Cell *c);
    static Cell *getCell();
    static bool isEmpty();
    static int getSize();

private:
    static QMutex mutex;
    static QList<Cell *> cellList;
};

#endif // DEADLIST_H
