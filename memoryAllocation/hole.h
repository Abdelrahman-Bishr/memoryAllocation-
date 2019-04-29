#ifndef HOLE_H
#define HOLE_H
#include <QList>

class Hole
{
//    Q_OBJECT
public:
    Hole(QString name,int startAddress,int size);
    int getStartAddress();
    int getSize();
    QString getName();
    void setNewAttributes(int newSize,int newStartAddress);
private:
    int startAddress,size;
    QString name;
};

#endif // HOLE_H
