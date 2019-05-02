#ifndef CHART_H
#define CHART_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "memoryblock.h"

class Chart : public QGraphicsView
{
public:
    Chart(int size);
    void setSegments(std::list <Segment *> * segmentsList);
    void setHoles   (std::list <Hole *> * holes);
    void startGraphing();
private:
    int size;
    QGraphicsScene * scene;
    std::list <Segment *> * segments;
    std::list <Hole *> * holes;
};

#endif // CHART_H
