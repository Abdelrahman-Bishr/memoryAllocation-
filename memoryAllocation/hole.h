#ifndef HOLE_H
#define HOLE_H
#include <segment.h>

class Hole
{
//    Q_OBJECT
public:
    Hole(QString name,int startAddress,int size);
    int getStartAddress();
    int getSize();
    QString getName();
    void setName(QString name);
    void setNewAttributes(int newSize,int newStartAddress);
    void allocate(Segment * seg);
private:
    int startAddress,size;
    QString name;
};

#endif // HOLE_H
