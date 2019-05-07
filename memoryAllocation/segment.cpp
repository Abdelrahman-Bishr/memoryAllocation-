#include "segment.h"

Segment::Segment(QString segName, int segSize , int segmentID)
{
    name=segName;
    size=segSize;
    allocated=false;
    residingAddress=-1;
    id=segmentID;
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
    if (allocated==true){
//        allocated=false;
        emit deallocated(this);
    }
    allocated=false;
    residingAddress=-1;
}
bool Segment::isAllocated()
{
    return allocated;
}

int Segment::getID()
{
    return id;
}
