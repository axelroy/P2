#include "controller.h"
#include "ui_controller.h"
#include "config.h"

#include <QtDebug>


QQueue<Cell*> Cell::deadList;
char View::keysStatment = Config::INIT_KEYS_STATMENT;

int Settler::ProbMalusCell = Config::PROBABILITY_MALUS_CELL;
int Settler::ProbBonusCell = Config::PROBABILITY_BONUS_CELL;
QSemaphore Cell::sem_deadList(1);


Controller::Controller(QWidget *parent) :
    QWidget(parent)
{
    nCells = Config::NB_CELLS;

    qsrand(QTime::currentTime().msec());
    qDebug() << "Lancement de l'app";
    //QHBoxLayout *layout = new QHBoxLayout;

    //Cell::deadList/* = new QQueue<Cell*>*/;
    map = new CustomScene();
    camera = new View();


    camera->setScene(map);

    camera->show();

    mainCell = new Cell(Config::START_LIFE);
    mainCell->setBrush(Qt::blue);
    mainCell->setSpeed(Config::BASE_SPEED_CELL);
    /*testIa = new Ia(map, mainCell);
    testIa->start();*/



    map->addItem(mainCell);

    camera->centerOn((mainCell->pos().x() - mainCell->boundingRect().width()/2), (mainCell->pos().y() - mainCell->boundingRect().height()/2));

    //faire une fonction Settler::initSettling()
    settler = new Settler(Config::SETTLER_OFF_AREA, Config::SETTLER_ON_AREA, mainCell);
    for(int i = 0; i < nCells; i++){
        Cell * cell = new Cell(Config::START_LIFE);
        map->addItem(cell);
        Cell::deadListEnqueue(cell);
        settler->settle();
        //qDebug() << i;
    }


    //Instancie et démarre le borderguard et le collider
    Borderguard *borderguard = new Borderguard(Config::BORDERGUARD_AREA, mainCell, map);
    borderguard->start();
    mainCollider = new Collider(map, mainCell);
    mainCollider->start();

    startTimer(Config::KEYS_TIMER);

    /*
    layout->addWidget(map);
    setLayout(layout);*/
}


//Est appellé à une fréquence donnée, génère les déplacements
void Controller::timerEvent(QTimerEvent *e)
{
//CustomScene* myScene = dynamic_cast<CustomScene *>(scene());
    //Move up
    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_UP){
        map->MoveCell(0.0,-mainCell->getSpeed(), mainCell);
        mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
    }

    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_UP_LEFT){
        map->MoveCell(-mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR,-mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR, mainCell);
        mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
    }

    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_LEFT){
        map->MoveCell(-mainCell->getSpeed(),0.0, mainCell);
        mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
    }

    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_DOWN_LEFT){
        map->MoveCell(-mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR,mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR, mainCell);
        mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
    }

    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_DOWN){
         map->MoveCell(0.0,mainCell->getSpeed(), mainCell);
         mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
     }

    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_DOWN_RIGHT){
        map->MoveCell(mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR,mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR, mainCell);
        mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
    }

    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_RIGHT){
        map->MoveCell(mainCell->getSpeed(),0.0, mainCell);
        mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
    }

    if((View::keysStatment & mainCollider->getAutorizedDirection()) == Config::ACTION_UP_RIGHT){
        map->MoveCell(mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR,-mainCell->getSpeed()*Config::DIAGONAL_SPEED_MULTIPLICATOR, mainCell);
        mainCollider->setAutorizedDirection(Config::DIRECTION_AUTHORIZED_ALL);
    }

    //qDebug() << "move " <<CustomScene::autorizedDirection;
    camera->centerOn((mainCell->pos().x() + mainCell->boundingRect().width()/2), (mainCell->pos().y() + mainCell->boundingRect().height()/2));

    //Réajustement de la vitesse de la Maincell, les bonus sont temporaires
    mainCell->setSpeed((mainCell->getSpeed()-Config::BASE_SPEED_CELL)*Config::BONUS_SPEED_REGRESSION+Config::BASE_SPEED_CELL);

    //qDebug() << mainCell->getSpeed();
    settler->settle();

    //mainCollider->update();
    mainCollider->update();
}

Controller::~Controller()
{
}
