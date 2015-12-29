#include "view.h"


View::View()
{
    keysStatment=0b00000000;
    myScene= new CustomScene();

    this->setScene(myScene);

    QHBoxLayout * MainLayout = new QHBoxLayout(this);


    setStyleSheet("background-color:white");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);

    mainCell = new Cell(0.0, 0.0 ,500);
    myScene->addItem(mainCell);
    myScene->initSettling(1000);


    //this->show();
    centerOn(mainCell);



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
    myScene->settler();
}
