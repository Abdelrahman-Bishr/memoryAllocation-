#include "chart.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#define  yBlock getYBlock();

Chart::Chart(int memorySize)
{
    this->memorySize=memorySize;
    scene=new QGraphicsScene();
    this->setScene(scene);
    this->setGeometry(20,20,500,1000);
    this->show();
    qDebug()<<"this.yBlock is "<<yBlock;
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
    qDebug()<<"starting to graph";
    int LowerLimit=0;
    int upperLimit=memorySize-1;
//    for (int i=0;i<memorySize;i++){

//    }
    for(std::list<Hole*>::iterator i=holes->begin();i!=holes->end();i++){
       prototypeBlock[0]=new MemoryBlock(nullptr,(*i));
       int y=(*i)->getStartAddress() * yBlock;
       qDebug()<<"y="+QString::number(y);
//       prototypeBlock[0]->setNewY((*i)->getStartAddress()/2);
       prototypeBlock[0]->setNewY(y);
       int tempSize=(*i)->getSize() * yBlock ;
       prototypeBlock[0]->setHeight(tempSize);
       scene->addItem(prototypeBlock[0]);
       qDebug()<<prototypeBlock[0]->boundingRect().y();
    }
    for(std::list<Segment*>::iterator i=segments->begin();i!=segments->end();i++){
       if(!(*i)->isAllocated())
           continue;
        prototypeBlock[0]=new MemoryBlock(nullptr,(*i));
       int y=(*i)->getResidingAddress() * yBlock;
       qDebug()<<"y="+QString::number(y);
//       prototypeBlock[0]->setNewY((*i)->getResidingAddress()/2);
       prototypeBlock[0]->setNewY(y);
       int tempSize=(*i)->getSize() * yBlock ;
       prototypeBlock[0]->setHeight(tempSize);
       scene->addItem(prototypeBlock[0]);
       qDebug()<<prototypeBlock[0]->boundingRect().y();
    }
}

double Chart::getYBlock()
{
    return (double) this->height()/memorySize;
}
