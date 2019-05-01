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
    residingAddress=-1;
    if (allocated==true)
        emit deallocated(residingAddress);
    allocated=false;
}

bool Segment::isAllocated()
{
    return allocated;
}
