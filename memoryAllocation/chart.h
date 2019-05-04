#ifndef CHART_H
#define CHART_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "memoryblock.h"
#include <vector>

class Chart : public QGraphicsView
{
public:
    Chart(int memorySize);
    void setSegments(std::list <Segment *> * segmentsList);
    void setHoles   (std::list <Hole *> * holes);
    void startGraphing();
    void clearItems();
    void drawHoles();
    void drawSegments();
    void drawFreeBlocks();
private:
    double getYBlock();
    int memorySize;
    QGraphicsScene * scene;
    std::list <Segment *> * segments;
    std::list <Hole *> * holes;
    std::list <MemoryBlock *> * memoryBlocks;
    MemoryBlock * prototypeBlock[2];
    std::vector < int *> * freeBlocks;
    int * x;
};

#endif // CHART_H
