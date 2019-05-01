#ifndef SEGMENT_H
#define SEGMENT_H
#include <QString>
#include <QObject>

class Segment : public QObject
{
    Q_OBJECT
public:
    Segment(QString segName, int segSize);
    QString getName();
    int getSize();
    void setName(QString name);
    void setResidingAddress(int address);
    void allocate();
    void deallocate();
    bool isAllocated();

signals:
    void deallocated (int startingAddress);
private:
    QString name;
    int size;
    int residingAddress;
    bool allocated;
};

#endif // SEGMENT_H
