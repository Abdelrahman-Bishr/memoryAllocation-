#include "segment.h"

Segment::Segment(QString segName, int segSize)
{
    name=segName;
    size=segSize;
}

QString Segment::getName()
{
    return name;
}

int Segment::getSize()
{
    return size;
}
