#include "chart.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#define  yBlock getYBlock();

Chart::Chart(int memorySize)
{
    x = new int [2];
    this->memorySize=memorySize;
    scene=new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    this->setScene(scene);
    this->setGeometry(20,20,500,1000);
    this->show();
    freeBlocks=new std::vector < int *> ();
    memoryBlocks=new std::list<MemoryBlock *> ();
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
    clearItems();
    qDebug()<<"starting to graph";
    for (std::vector <int *>::iterator i=freeBlocks->begin(); i!=freeBlocks->end(); i++){
        delete (*i);
    }
    freeBlocks->clear();
    drawHoles();
    drawSegments();
    drawFreeBlocks();
}

void Chart::clearItems()
{
    scene->clear();
    qDebug()<<"finished clearing";
    memoryBlocks->clear();
}

///////////////////////******************************///////////////////////////
//////////////          TO BE REVISED TOMORROW                 ////////////////
/////////////////////********************************/////////////////////////

void Chart::drawHoles()
{
    qDebug()<<"in draw holes";
    x=new int [2];
    x[0]=0;
    if(holes->size()>0)
        x[1]=(*holes->begin())->getStartAddress()-1;
    else {
        x[1]=memorySize-1;
        freeBlocks->push_back(x);
        return;
    }
    if(x[0]!=x[1])
        freeBlocks->push_back(x);
    std::list<Hole*>::iterator j=holes->begin();
    j++;
    for(std::list<Hole*>::iterator i=holes->begin();i!=holes->end();i++){
       qDebug()<<"chart::35::holes size is "<<holes->size();
       x=new int [2];
       x[0]=(*j)->getStartAddress()-1;
       if(j!=holes->end())
           x[1]=(*i)->getStartAddress()+(*i)->getSize();
       else
           x[1]=memorySize-1;
       if(x[1]!=x[0])
           freeBlocks->push_back(x);

       qDebug()<<"x is "<<x[0]<<x[1];
       prototypeBlock[0]=new MemoryBlock(nullptr,(*i));
       int y=(*i)->getStartAddress() * yBlock;
       qDebug()<<"y="+QString::number(y);
//       prototypeBlock[0]->setNewY((*i)->getStartAddress()/2);
       prototypeBlock[0]->setNewY(y);
       int tempSize=(*i)->getSize() * yBlock ;
       prototypeBlock[0]->setHeight(tempSize);
       scene->addItem(prototypeBlock[0]);
       qDebug()<<prototypeBlock[0]->boundingRect().y();
        j++;
    }
}

void Chart::drawSegments()
{

    std::list<Segment*>::iterator j=segments->begin();
    j++;
    for(std::list<Segment*>::iterator i=segments->begin();i!=segments->end();i++){
       if(!(*i)->isAllocated()){
            int endAddress=(*i)->getSize()+(*i)->getResidingAddress()-1;
            for (std::vector<int *>::iterator j=freeBlocks->begin() ; j!=freeBlocks->end();j++){
                if (((*j)[1] >= (*i)->getResidingAddress() && (*j)[1] <= endAddress)){
                    (*j)[1]=(*i)->getResidingAddress();
                }
                if (((*j)[0] >= (*i)->getResidingAddress() && (*j)[0] <= endAddress)){
                    (*j)[0]=endAddress;
                }
            }
            continue;
        }
       prototypeBlock[0]=new MemoryBlock(nullptr,(*i));
       int y=(*i)->getResidingAddress() * yBlock;
       qDebug()<<"y="+QString::number(y);
//       prototypeBlock[0]->setNewY((*i)->getResidingAddress()/2);
       prototypeBlock[0]->setNewY(y);
       int tempSize=(*i)->getSize() * yBlock ;
       prototypeBlock[0]->setHeight(tempSize);
       scene->addItem(prototypeBlock[0]);
       qDebug()<<prototypeBlock[0]->boundingRect().y();
       memoryBlocks->push_back(prototypeBlock[0]);
    }
}

void Chart::drawFreeBlocks()
{
    for (std::vector<int *>::iterator i=freeBlocks->begin() ; i!=freeBlocks->end();i++){
        qDebug()<<"free blocks size is"<<freeBlocks->size();
        if((*i)[0]>=(*i)[1]){
            qDebug()<<"found a free block that shall be erased";
            delete *i;
            freeBlocks->erase(i);
            i--;
            continue;
        }
        prototypeBlock[0]=new MemoryBlock (nullptr,(*i)[0],(*i)[1]-(*i)[0]+1);
        int y=(*i)[0] * yBlock;
        qDebug()<<"y="+QString::number(y);
        prototypeBlock[0]->setNewY(y);
        int tempSize=((*i)[1]- (*i)[0] +1 )* yBlock ;
        prototypeBlock[0]->setHeight(tempSize);
        scene->addItem(prototypeBlock[0]);
        qDebug()<<prototypeBlock[0]->boundingRect().y();
    }
}

double Chart::getYBlock()
{
    return (double) this->height()/memorySize;
}
