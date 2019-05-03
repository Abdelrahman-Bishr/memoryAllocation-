#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H
#include <QGraphicsRectItem>
#include <QLabel>
#include "hole.h"
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QDebug>
#include <math.h>
class MemoryBlock : public QGraphicsRectItem
{
public:
    MemoryBlock(QGraphicsItem * parent,Hole * hole);                              //state 0
    MemoryBlock(QGraphicsItem * parent,Segment * allocatedSegment);               //state 1
    MemoryBlock(QGraphicsItem * parent , int startAddress , int size);            //state 2
    ~MemoryBlock();
    void setSize(int length);
    void setStartAddress(int startAddress);
    void setName(QString name);
    void allocate(Segment * allocatedSegment);
    void deallocate(Hole * deallocatedHole);
    void changeAttributes(int state,int length,int startAddress);
    void setNewY(int y);
    void setHeight(int height);
    int getLength();
    int getStartAddress();
    int getState();
    QString getName();
private:
    void positionLabels();
    int currentState,startAddress,length;
    QGraphicsSimpleTextItem * addressLabel, * blockName;
    QBrush * brush;

};

#endif // MEMORYBLOCK_H
