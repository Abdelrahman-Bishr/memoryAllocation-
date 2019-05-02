#include "chart.h"
#include <QGraphicsScene>
#include <QGraphicsView>

Chart::Chart(int size)
{
    this->size=size;
    scene=new QGraphicsScene();
    this->setScene(scene);
    this->setGeometry(20,20,160,1000);
    this->show();

}

void Chart::setSegments(std::list<Segment *> *segmentsList)
{
    this->segments=segmentsList;
}

void Chart::setHoles(std::list<Hole *> *holes)
{
    this->holes=holes;
}

void Chart::startGraphing()
{
    int LowerLimit=0;
    int upperLimit=size-1;
    for (int i=0;i<size;i++){
        //
    }
}
