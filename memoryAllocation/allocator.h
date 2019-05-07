#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include "hole.h"
#include "myprocess.h"
#include "segment.h"
#include "chart.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include <QDebug>
#include <list>
#include <algorithm>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMessageBox>


class Allocator : public QObject
{
    Q_OBJECT
public:
    Allocator(std::list <Process *> *processes , std::list <Hole *> *holes ,int memorySize=2000);
    void startAllocator(QString allocationMethod);
    void firstFit();
    void bestFit();
    void worstFit();
    void joinHoles();
    void setChartWidget (QVBoxLayout * memoryGroupBoxLayout);
    void drawGraph();
    static bool largerHole(Hole * hole1 , Hole * hole2 ){
        if (hole1->getSize()<hole2->getSize())
            return true;
        return false;
    }
    static bool holeStart(Hole * hole1 , Hole * hole2 ){
        if (hole1->getStartAddress()<hole2->getStartAddress())
            return true;
        return false;
    }
    static bool largerSegment(Segment *segment1 ,Segment *segment2 ){

        if (segment1->getSize()<segment2->getSize())
            return true;
        return false;
    }
    static bool segmentStart(Segment * segment1 , Segment * segment2 ){
        if (segment1->getResidingAddress()<segment2->getResidingAddress())
            return true;
        return false;
    }


signals:
    bool holeAllocated(Hole * allocatedHole);
    void holeEaten(QString holeName);
    std::list <Hole *>  *setHoles();
    std::list <Process *> *setProcesses();
private:
    std::list <Process *>  *processes ;
    void setSegments();
    std::list <Hole *>  *holes;
    std::list <Segment *> *segments;
    Chart * memoryGraph;
    QVBoxLayout * memoryDisplayLayout;
    QMessageBox * messageUser;

};

#endif // ALLOCATOR_H
