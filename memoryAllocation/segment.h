#ifndef SEGMENT_H
#define SEGMENT_H
#include <QString>
#include <QObject>

class Segment : public QObject
{
    Q_OBJECT
public:
    Segment(QString segName, int segSize, int segmentID);
    QString getName();
    int getSize();
    int getResidingAddress();
    void setName(QString name);
    void setResidingAddress(int address);
    void allocate();
    void deallocate();
    bool isAllocated();
    int getID();
signals:
    void deallocated (Segment * deallocatedSegment);
private:
    QString name;
    int size;
    int residingAddress;
    bool allocated;
    int id;
};

#endif // SEGMENT_H
