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


void Hole::setNewAttributes(int newSize, int newStartAddress)
{
    startAddress=newStartAddress;
    size=newSize;
}
