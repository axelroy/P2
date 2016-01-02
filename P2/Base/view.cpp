#include "view.h"


View::View()
{
    keysStatment=0b00000000;
    myScene= new CustomScene();

    this->setScene(myScene);

    setStyleSheet("background-color:white");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);

    mainCell = new Cell(0.0, 0.0 ,500);
    mainCell->setBrush(Qt::blue);

    ////////////////////////////////////////////// TEST ANIMATION

    QTimeLine *timer = new QTimeLine(1000);
    timer->setFrameRange(0, 100);
    timer->setUpdateInterval(60);
    animation = new QGraphicsItemAnimation;
    animation->setItem(mainCell);
    animation->setTimeLine(timer);
    timer->setLoopCount(0);

    animation->setScaleAt(0.5,1.1,1.1);
    animation->setScaleAt(1,1.,1.);

    ////////// FIN  TEST
    ///
    myScene->addItem(mainCell);
    myScene->initSettling(1000);

    centerOn(mainCell);

    //TEST ANIMATIOn
     timer->start();
    //FIN TEST

    startTimer(20);
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
    if(keysStatment == 0b00000001)
        myScene->MoveCell(0.0,-5.0, mainCell);

    if(keysStatment == 0b00000011)
        myScene->MoveCell(-3.0,-3.0, mainCell);

    if(keysStatment == 0b00000010)
        myScene->MoveCell(-5.0,0.0, mainCell);

    if(keysStatment == 0b00000110)
        myScene->MoveCell(-3.0,3.0, mainCell);

    if(keysStatment == 0b00000100)
         myScene->MoveCell(0.0,5.0, mainCell);

    if(keysStatment == 0b00001100)
        myScene->MoveCell(3.0,3.0, mainCell);

    if(keysStatment == 0b00001000)
        myScene->MoveCell(5.0,0.0, mainCell);

    if(keysStatment == 0b00001001)
        myScene->MoveCell(3.0,-3.0, mainCell);

    centerOn(mainCell);

    //peut-être un brin sale, pour que ça marche
    myScene->collider(mainCell);
    myScene->settler(mainCell);
}
