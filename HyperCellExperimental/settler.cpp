#include "settler.h"
#include "deadlist.h"
#include "config.h"
#include "customscene.h"

/*============================================*/
//  CONSTRUCTOR / DESTRUCTOR
/*============================================*/

Settler::Settler(double rangeMin, double rangeMax, Cell *refCell)
{
    this->rangeMin = rangeMin;
    this->rangeMax = rangeMax;
    this->refCell = refCell;
}

Settler::~Settler()
{
    //nothings
}

/*============================================*/
//  PUBLIC METHODE
/*============================================*/
void Settler::settle()
{

    //qDebug() << "17";
    //Adapte des ranges selon les tailles de la main cell
    rangeMin = Config::SETTLER_OFF_AREA * qSqrt(qSqrt(refCell->getHealthPoint()/Config::START_LIFE));
    rangeMax = Config::SETTLER_ON_AREA * qSqrt(qSqrt(refCell->getHealthPoint()/Config::START_LIFE));

    if(!DeadList::isEmpty()){
        //qDebug() << "18";
        cellTreated = DeadList::getCell();

        int RandY = Utility::polarizedRandInt(0, rangeMax);
        int RandX = Utility::polarizedRandInt(0, rangeMax);

        if(qAbs(RandY) < rangeMin && qAbs(RandX) < rangeMin){
            if(RandY <= 0)
                RandY-=rangeMin;
            else
                RandY+=rangeMin;

            if(RandX < 0)
                RandX-=rangeMin;
            else
                RandX+=rangeMin;
        }

        //refaire pour pas qu'il apparaisse sur la partie visible
        cellTreated->setPos((refCell->x())+RandY, (refCell->y())+RandX);
        //qDebug() << "19";

        randomTypeCell = Utility::randInt(0, 100);
        //Risque de voir une prolifération de malusCell car le joueur va éviter de les prendre ?
        if(randomTypeCell < Config::PROBABILITY_MALUS_CELL){
            cellTreated->setHealthPoint(0.2*refCell->getHealthPoint());
            cellTreated->setBrush(Qt::red);
            cellTreated->setBonusHealthPoint((-(double)(Utility::randInt(1, 5))/10)*refCell->getHealthPoint());
            cellTreated->setBonusSpeed((-(double)(Utility::randInt(2, 20))/10)*refCell->getSpeed());
        }else if(randomTypeCell < Config::PROBABILITY_BONUS_CELL+Config::PROBABILITY_MALUS_CELL){
            cellTreated->setHealthPoint(0.2*refCell->getHealthPoint());
            cellTreated->setBrush(Qt::green);
            cellTreated->setBonusHealthPoint(((double)(Utility::randInt(1, 5))/10)*refCell->getHealthPoint());
            cellTreated->setBonusSpeed(((double)(Utility::randInt(2, 20))/10)*refCell->getSpeed());
        }else {
            cellTreated->setHealthPoint(((double)(Utility::randInt(3, 20))/10)*refCell->getHealthPoint());
            cellTreated->setBonusHealthPoint(cellTreated->getHealthPoint());
            cellTreated->setBrush(Qt::yellow);
        }
        //qDebug() << "20";
        cellTreated->refreshSize();
        cellTreated->activate();
    }
}

void Settler::initSettle(CustomScene* map,int nbCells, QList<Bot*> &bots, int nbBots)
{
    for(int i = 0; i < nbCells; i++){
        Cell * cell = new Cell(Config::START_LIFE);
        map->addItem(cell);
        DeadList::addCell(cell);
        settle();
        //delete[] cell;
    }
    for(int i = 0; i < nbBots; i++){
        Bot * bot = new Bot(map);
        map->addItem(bot);
        DeadList::addCell(bot);
        bots.push_back(bot);
        settle();
        //delete[] bot;
    }
}
