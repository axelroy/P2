#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QList>

class Cell;
class Bot;
class CustomScene;
class View;
class Collider;
class Settler;
class Borderguard;

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(QWidget *parent = 0);
    virtual ~Controller();

public slots:
    void on_collider_collision(Cell &c1, Cell &c2);
signals :
    void blockMovement();
    void gamePause(bool isPaused);


protected:
    void timerEvent(QTimerEvent* e);

private:
    CustomScene* map;
    View* camera;
    Cell* mainCell;
    QList<Bot*> bots;
    Collider* mainCollider;
    Borderguard *borderguard;
    Settler* settler;

    void initialisation();
    void manageDeadCell(Cell &c);
    void scaleView();
    void eat(Cell &c1, Cell &c2);
    void newGame();

    void moveBot(Bot* bot);
};

#endif // CONTROLLER_H
