#ifndef PROCESS_H
#define PROCESS_H
#include <QList>
#include <QListWidget>
#include "segment.h"

class Process
{
public:
    Process(QString name,int id,int segments=1);
    QString getName();
    int getNumberOfSegments();
    int getNumberOfEnteredSegments();
    QString getSegmentName(int segmentIndex);
    int getSegmentSize(QString segmentName);
    int getSegmentSize(int segmentIndex);
    QListWidget * getSegmentsListWidget();
    void setNewSegment(QString name,int size);
    void addSegment();

private:
    QString name;
    QString newSegmentName;
    int segmentsCount;
    int id;
    int newSegmentSize;
    QList <Segment *> segmentsList;
    QListWidget * segsListWidget;
    Segment * newSeg;
};

#endif // PROCESS_H
