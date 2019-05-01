#include "hole.h"

Hole::Hole(QString name,int startAddress, int size)
{
    this->name=name;
    this->startAddress=startAddress;
    this->size=size;
}

int Hole::getStartAddress()
{
    return startAddress;
}

int Hole::getSize()
{
    return size;
}

QString Hole::getName()
{
    return name;
}

void Hole::setName(QString name)
{
    this->name=name;
}


void Hole::setNewAttributes(int newSize, int newStartAddress)
{
    startAddress=newStartAddress;
    size=newSize;
}

void Hole::allocate(Segment *seg)
{
    seg->setResidingAddress(startAddress);
    startAddress=startAddress+seg->getSize();
    size-=seg->getSize();
    seg->allocate();
}
