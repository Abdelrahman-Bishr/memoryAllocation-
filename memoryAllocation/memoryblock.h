#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H
#include <QGraphicsRectItem>
#include <QLabel>
#include "hole.h"

class MemoryBlock : public QRect
{
public:
    MemoryBlock(QWidget * parent ,int state);                               //0 for hole , 1 for segment , 2 for being occupied by something else (not a user input )
    MemoryBlock(QWidget * parent,Hole * hole);                              //state 0
    MemoryBlock(QWidget * parent,Segment * allocatedSegment);               //state 1
    MemoryBlock(QWidget * parent);                                          //state 2
    void setSize(int length);
    void setStartAddress(int startAddress);
    void changeAttributes(int state,int length,int startAddress);
    int getLength();
    int getStartAddress();
    int getState();

private:
    int currentState;
    int startAddress;
    int length;
};

#endif // MEMORYBLOCK_H
