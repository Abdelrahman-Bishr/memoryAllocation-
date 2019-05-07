#ifndef PROCESS_H
#define PROCESS_H
#include <QList>
#include <QListWidget>
#include "segment.h"

class Process : public QObject
{
    Q_OBJECT
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
    std::list<Segment *> *getSegmentsList();

signals:
    void deallocated(Segment * deallocatedSegment);
private slots:
    void segmentDeallocated(Segment * deallocatedSegment);
private:
    QString name;
    QString newSegmentName;
    int segmentsCount;
    int id;
    int newSegmentSize;
    std::list <Segment *> *segments;
    QListWidget * segsListWidget;
    Segment * newSeg;
};

#endif // PROCESS_H
