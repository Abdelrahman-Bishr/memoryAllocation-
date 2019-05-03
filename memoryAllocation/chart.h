#ifndef CHART_H
#define CHART_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "memoryblock.h"

class Chart : public QGraphicsView
{
public:
    Chart(int memorySize);
    void setSegments(std::list <Segment *> * segmentsList);
    void setHoles   (std::list <Hole *> * holes);
    void startGraphing();
private:
    double getYBlock();
    int memorySize;
    QGraphicsScene * scene;
    std::list <Segment *> * segments;
    std::list <Hole *> * holes;
    MemoryBlock * prototypeBlock[2];
};

#endif // CHART_H
