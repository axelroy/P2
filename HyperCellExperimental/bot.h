#ifndef BOT_H
#define BOT_H

#include <QMutex>

#include "cell.h"
#include "collider.h"
#include "customscene.h"
#include "config.h"


class Bot : public QThread, public Cell
{
public:
    Bot(CustomScene* map);
    void run();

    char getDirection() const;

    Collider *getBotCollider() const;

private:
    Cell* botCell;
    Cell* target;
    Cell* fetch;
    Collider* botCollider;
    CustomScene* map;
    char direction;
    bool targetTargeted;

    QMutex mutex_direction;

    void calcDirection();

};

#endif // BOT_H
