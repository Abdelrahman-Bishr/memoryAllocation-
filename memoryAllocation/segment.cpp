#include "segment.h"

Segment::Segment(QString segName, int segSize)
{
    name=segName;
    size=segSize;
    allocated=false;
    residingAddress=-1;
}

QString Segment::getName()
{
    return name;
}

int Segment::getSize()
{
    return size;
}

int Segment::getResidingAddress()
{
    return residingAddress;
}

void Segment::setName(QString name)
{
    this->name=name;
}

void Segment::setResidingAddress(int address)
{
    residingAddress=address;
}

void Segment::allocate()
{
    allocated=true;
}

void Segment::deallocate()
{
    if (allocated==true)
        emit deallocated(this);
    residingAddress=-1;
    allocated=false;
}

bool Segment::isAllocated()
{
    return allocated;
}
