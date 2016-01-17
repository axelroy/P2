#include "controller.h"
#include "config.h"
#include "deadlist.h"
#include "cell.h"
#include "customscene.h"
#include "view.h"
#include "collider.h"
#include "settler.h"
#include "utility.h"
#include "borderguard.h"

#include <QDebug>
#include <QTime>
#include <QApplication>
#include <QMessageBox>


/*============================================*/
//  CONSTRUCTOR / DESTRUCTOR
/*============================================*/

Controller::Controller(QWidget *parent) :
    QWidget(parent)
{
    qsrand(QTime::currentTime().msec());
    initialisation();
    startTimer(Config::KEYS_TIMER);
}

/*============================================*/
//  OVERRIDE
/*============================================*/

//Est appellé à une fréquence donnée, génère les déplacements
void Controller::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e); // désactive le warning de l'inutilisation de e

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

    camera->centerOn((mainCell->pos().x() + mainCell->boundingRect().width()/2), (mainCell->pos().y() + mainCell->boundingRect().height()/2));

    //Réajustement de la vitesse de la Maincell, les bonus sont temporaires
    mainCell->setSpeed((mainCell->getSpeed()-Config::START_SPEED)*Config::BONUS_SPEED_REGRESSION+Config::START_SPEED);

    settler->settle();
    refreshBestSize();

    if (mainCell->isActive())
    {
        mainCollider->update();
    }
}

Controller::~Controller()
{
    delete map;
    delete camera;
    delete settler;
    borderguard->quit();
    delete borderguard;
    mainCollider->quit();
    delete mainCollider;
}

/*============================================*/
//  SIGNAL / SLOT
/*============================================*/

void Controller::on_collider_collision(Cell &c1, Cell &c2)
{
    eat(c1,c2);
}

/*============================================*/
//  PRIVATE
/*============================================*/

void Controller::eat(Cell &c1, Cell &c2)
{
    if(c1.getHealthPoint() > c2.getHealthPoint())
    {
        c1.setHealthPoint(c1.getHealthPoint() + c2.getBonusHealthPoint());
        c1.setSpeed(c1.getSpeed() + c2.getBonusSpeed());
        c1.setArmor(c1.getArmor() + c2.getBonusArmor());
        manageDeadCell(c2);
        c1.refreshSize();
    }
    else
    {
        c2.setHealthPoint(c2.getHealthPoint() + c1.getBonusHealthPoint());
        c2.setSpeed(c2.getSpeed() + c1.getBonusSpeed());
        c2.setArmor(c2.getArmor() + c1.getBonusArmor());
        manageDeadCell(c1);
        c2.refreshSize();
    }
    //scaleView();
}

void Controller::newGame()
{
    View::keysStatment = Config::INIT_KEYS_STATMENT;

    mainCell->setHealthPoint(Config::START_LIFE);
    mainCell->setBrush(Qt::blue);
    mainCell->setSpeed(Config::START_SPEED);
    mainCell->setArmor(Config::START_ARMOR);
    mainCell->activate();
    mainCell->setX(0);
    mainCell->setY(0);
    mainCell->refreshSize();
    bestSize = 0;

    foreach (QGraphicsItem * item, map->items())
    {
        Cell *c = reinterpret_cast<Cell*>(item);
        if(c->isActive() && (!c->isPlayer()))
        {
            c->desactivate();
            DeadList::addCell(c);
        }
    }

    while(!DeadList::isEmpty())
    {
        settler->settle();
    }
    emit blockMovement(false);
}

void Controller::showMsgBEndGame()
{
    QMessageBox::StandardButton reply;
    QString titre = "Vous avez perdu !";
    QString corps = "Votre masse maximal atteinte :\n%1pg\n\nVoulez-vous recommencer ?";
    corps = corps.arg(bestSize);

    reply = QMessageBox::warning(this, titre, corps, QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        newGame();
    }
    else
    {
        QApplication::quit();
    }
}

void Controller::manageDeadCell(Cell &c)
{
    c.desactivate();
    //qDebug()<<"is player" << c.isPlayer();
    //qDebug()<<"c" << &c;
    //qDebug()<<"mainCell" << &mainCell;
    if(c.isPlayer())
    {
        emit blockMovement(true);                
        showMsgBEndGame();
    }
    else
    {
        DeadList::addCell(&c);
    }
}

//TODO bad code, fix algorithm to calculate ratio. A const factor are defin in ZOOM_OFFSET
/*void Controller::scaleView()
{

    int areaCell = mainCell->getHealthPoint();
    int areaView = camera->width()*camera->height();

    double ratio = 1.0 / areaCell * Config::ZOOM_OFFSET;

    ratio = 1; //avoid bug for now
    camera->scale(ratio,ratio);
}*/

void Controller::initialisation()
{
    //instanciation
    map = new CustomScene(this);
    camera = new View();
    mainCell = new Cell(Config::START_LIFE);
    settler = new Settler(Config::SETTLER_OFF_AREA, Config::SETTLER_ON_AREA, mainCell);
    borderguard = new Borderguard(mainCell, map);
    mainCollider = new Collider(map, mainCell);

    bestSize = 0;

    //parametrize
    mainCell->setBrush(Qt::blue);
    mainCell->setSpeed(Config::START_SPEED);
    mainCell->setIsPlayer(true);
    mainCell->activate();

    map->addItem(mainCell);

    camera->setScene(map);
    camera->show();
    camera->centerOn((mainCell->pos().x() - mainCell->boundingRect().width()/2), (mainCell->pos().y() - mainCell->boundingRect().height()/2));
    settler->initSettle(map,Config::NB_CELLS);

    //connects
    connect(mainCollider, SIGNAL(collision(Cell&,Cell&)),this, SLOT(on_collider_collision(Cell&,Cell&)));
    connect(this, SIGNAL(blockMovement(bool)),mainCollider, SLOT(on_Controller_BlockMovement(bool)));

    //start the thread if config active
    if(Config::ACTIVE_BORDERGUARD)
    {
        borderguard->start();
    }
    mainCollider->start();
}

void Controller::refreshBestSize()
{
    if(bestSize < mainCell->getHealthPoint() )
    {
        bestSize =  mainCell->getHealthPoint();
    }
}

