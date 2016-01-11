#include "controller.h"
#include "ui_controller.h"

#include <QtDebug>


double Cell::BaseSpeedCell = 5;

QQueue<Cell*> Cell::deadList;
char Collider::autorizedDirection = 0b11111111;
char View::View::keysStatment = 0b00000000;

int Settler::ProbMalusCell = 0;
int Settler::ProbBonusCell = 100;
QSemaphore Cell::sem_deadList(1);


Controller::Controller(QWidget *parent) :
    QWidget(parent)
{
    nCells = 20000;

    qsrand(QTime::currentTime().msec());
    qDebug() << "Lancement de l'app";
    //QHBoxLayout *layout = new QHBoxLayout;

    Cell::BaseSpeedCell = 5;

    //Cell::deadList/* = new QQueue<Cell*>*/;


    View::keysStatment=0b00000000;
    map = new CustomScene();
    camera = new View();


    camera->setScene(map);

    camera->show();

    mainCell = new Cell(500);
    mainCell->setBrush(Qt::blue);
    mainCell->setSpeed(Cell::BaseSpeedCell);

    map->addItem(mainCell);

    camera->centerOn((mainCell->pos().x() - mainCell->boundingRect().width()/2), (mainCell->pos().y() - mainCell->boundingRect().height()/2));

    //faire une fonction Settler::initSettling()
    settler = new Settler(100, 10000, mainCell);
    for(int i = 0; i < nCells; i++){
        Cell * cell = new Cell(60);
        map->addItem(cell);
        Cell::deadList.enqueue(cell);
        settler->settle();
        //qDebug() << i;
    }


    Borderguard *borderguard = new Borderguard(11000, mainCell, map);
    borderguard->start();
    mainCollider = new Collider(map, mainCell);
    mainCollider->start();

    startTimer(20);
    /*
    layout->addWidget(map);
    setLayout(layout);*/
}



void Controller::timerEvent(QTimerEvent *e)
{
//CustomScene* myScene = dynamic_cast<CustomScene *>(scene());
    //Move up

    if((View::keysStatment & Collider::autorizedDirection) == 0b00000001){
        map->MoveCell(0.0,-mainCell->getSpeed(), mainCell);
        Collider::autorizedDirection = 0b11111111;
    }

    if((View::keysStatment & Collider::autorizedDirection) == 0b00000011){
        map->MoveCell(-mainCell->getSpeed()*0.707,-mainCell->getSpeed()*0.707, mainCell);
        Collider::autorizedDirection = 0b11111111;
    }

    if((View::keysStatment & Collider::autorizedDirection) == 0b00000010){
        map->MoveCell(-mainCell->getSpeed(),0.0, mainCell);
        Collider::autorizedDirection = 0b11111111;
    }

    if((View::keysStatment & Collider::autorizedDirection) == 0b00000110){
        map->MoveCell(-mainCell->getSpeed()*0.707,mainCell->getSpeed()*0.707, mainCell);
        Collider::autorizedDirection = 0b11111111;
    }

    if((View::keysStatment & Collider::autorizedDirection) == 0b00000100){
         map->MoveCell(0.0,mainCell->getSpeed(), mainCell);
         Collider::autorizedDirection = 0b11111111;
     }

    if((View::keysStatment & Collider::autorizedDirection) == 0b00001100){
        map->MoveCell(mainCell->getSpeed()*0.707,mainCell->getSpeed()*0.707, mainCell);
        Collider::autorizedDirection = 0b11111111;
    }

    if((View::keysStatment & Collider::autorizedDirection) == 0b00001000){
        map->MoveCell(mainCell->getSpeed(),0.0, mainCell);
        Collider::autorizedDirection = 0b11111111;
    }

    if((View::keysStatment & Collider::autorizedDirection) == 0b00001001){
        map->MoveCell(mainCell->getSpeed()*0.707,-mainCell->getSpeed()*0.707, mainCell);
        Collider::autorizedDirection = 0b11111111;
    }

    //qDebug() << "move " <<CustomScene::autorizedDirection;

    camera->centerOn((mainCell->pos().x() + mainCell->boundingRect().width()/2), (mainCell->pos().y() + mainCell->boundingRect().height()/2));

    //Réajustement de la vitesse de la Maincell, les bonus sont temporaires
    mainCell->setSpeed((mainCell->getSpeed()-Cell::BaseSpeedCell)*0.95+Cell::BaseSpeedCell);
    //qDebug() << mainCell->getSpeed();

    settler->settle();
    mainCollider->update();



}


Controller::~Controller()
{

}
