#include "view.h"
#include <QtDebug>
#include "CustomScene.h"
#include <QTimer>


//configuration
int CustomScene::randomCell = 0;
int CustomScene::ProbMalusCell = 20;
int CustomScene::ProbBonusCell = 20;
double CustomScene::BaseSpeedCell = 5;
char CustomScene::autorizedDirection = 0b11111111;

View::View()
{

    mainCell = new Cell(0.0, 0.0 ,500);

    keysStatment=0b00000000;
    myScene= new CustomScene(mainCell);


    this->setScene(myScene);

    QHBoxLayout * MainLayout = new QHBoxLayout(this);


    setStyleSheet("background-color:white");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);


    mainCell->setBrush(Qt::blue);
    mainCell->setSpeed(CustomScene::BaseSpeedCell);

    //Timer d'animation pour le grossissement, durée d'une séquence : 1 seconde
    QTimeLine *timer = new QTimeLine(1000);
    timer->setFrameRange(0, 100);
    timer->setUpdateInterval(60);
    //Crée l'animation, set l'objet sur lequel ca s'applique, lie le timer et le fait se répéter
    animation = new QGraphicsItemAnimation;
    animation->setItem(mainCell);
    animation->setTimeLine(timer);
    timer->setLoopCount(0);

    //Ces deux tailles se répetent en boucle
    animation->setScaleAt(0.0,1.0,1.0);
    animation->setScaleAt(0.5,0.9,0.9);
    //animation->setTranslationAt(0.5, -(mainCell-> *animation->horizontalScaleAt(0.5)), -(mainCell->scale() *  animation->horizontalScaleAt(0.5))) ;
    animation->setScaleAt(1.0,1.0,1.0);
    //animation->setTranslationAt(1, 0,0 ) ;

    myScene->addItem(mainCell);
    myScene->initSettling(1000, mainCell);

    centerOn((mainCell->pos().x() - mainCell->scale()), (mainCell->pos().y() - mainCell->scale()) );

    //Lance le timer d'animation
    timer->start();

    //Lance le timer de clavier
    startTimer(20);

    //Timer de Borderguards
    QTimer *timerBorderguards = new QTimer(this);
    //connect(timerBorderguards, SIGNAL(timeout()), this, SLOT(timerBorderguard()));
    connect(timerBorderguards, &QTimer::timeout, this, &View::timerBorderguard);

    timerBorderguards->start(1000);
}



void View::keyPressEvent(QKeyEvent* e)
{
    if(!e->isAutoRepeat())
    {
        switch (e->key()) {
        case Qt::Key_W:
            keysStatment=keysStatment | 0b00000001;
            break;

        case Qt::Key_A:
            keysStatment=keysStatment | 0b00000010;
            break;

        case Qt::Key_S:
            keysStatment=keysStatment | 0b00000100;
            break;

        case Qt::Key_D:
            keysStatment=keysStatment | 0b00001000;
            break;

        default:
            break;
        }
     }
}

void View::keyReleaseEvent(QKeyEvent* e)
{
    if(!e->isAutoRepeat())
    {
        switch (e->key()) {
        case Qt::Key_W:
            keysStatment=keysStatment & 0b11111110;
            break;
        case Qt::Key_A:
            keysStatment=keysStatment & 0b11111101;
            break;

        case Qt::Key_S:
            keysStatment=keysStatment & 0b11111011;
            break;

        case Qt::Key_D:
            keysStatment=keysStatment & 0b11110111;
            break;

        default:
            break;
        }
     }
}

void View::timerEvent(QTimerEvent *e)
{
//CustomScene* myScene = dynamic_cast<CustomScene *>(scene());
    //Move up
    if((keysStatment & CustomScene::autorizedDirection) == 0b00000001){
        myScene->MoveCell(0.0,-mainCell->getSpeed(), mainCell);
        CustomScene::autorizedDirection = 0b11111111;
    }

    if((keysStatment & CustomScene::autorizedDirection) == 0b00000011){
        myScene->MoveCell(-mainCell->getSpeed()*0.707,-mainCell->getSpeed()*0.707, mainCell);
        CustomScene::autorizedDirection = 0b11111111;
    }

    if((keysStatment & CustomScene::autorizedDirection) == 0b00000010){
        myScene->MoveCell(-mainCell->getSpeed(),0.0, mainCell);
        CustomScene::autorizedDirection = 0b11111111;
    }

    if((keysStatment & CustomScene::autorizedDirection) == 0b00000110){
        myScene->MoveCell(-mainCell->getSpeed()*0.707,mainCell->getSpeed()*0.707, mainCell);
        CustomScene::autorizedDirection = 0b11111111;
    }

    if((keysStatment & CustomScene::autorizedDirection) == 0b00000100){
         myScene->MoveCell(0.0,mainCell->getSpeed(), mainCell);
         CustomScene::autorizedDirection = 0b11111111;
     }

    if((keysStatment & CustomScene::autorizedDirection) == 0b00001100){
        myScene->MoveCell(mainCell->getSpeed()*0.707,mainCell->getSpeed()*0.707, mainCell);
        CustomScene::autorizedDirection = 0b11111111;
    }

    if((keysStatment & CustomScene::autorizedDirection) == 0b00001000){
        myScene->MoveCell(mainCell->getSpeed(),0.0, mainCell);
        CustomScene::autorizedDirection = 0b11111111;
    }

    if((keysStatment & CustomScene::autorizedDirection) == 0b00001001){
        myScene->MoveCell(mainCell->getSpeed()*0.707,-mainCell->getSpeed()*0.707, mainCell);
        CustomScene::autorizedDirection = 0b11111111;
    }

    //qDebug() << "move " <<CustomScene::autorizedDirection;

    centerOn((mainCell->pos().x() - mainCell->scale()), (mainCell->pos().y() - mainCell->scale()) );

    //Réajustement de la vitesse de la Maincell, les bonus sont temporaires
    mainCell->setSpeed((mainCell->getSpeed()-CustomScene::BaseSpeedCell)*0.95+CustomScene::BaseSpeedCell);
    //qDebug() << mainCell->getSpeed();

    //peut-être un brin sale, pour que ça marche
    myScene->collider(mainCell);
    myScene->settler(mainCell);
}

 void View::timerBorderguard(){
     myScene->borderguard();
}

