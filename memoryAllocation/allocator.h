#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include "hole.h"
#include "process.h"
#include "segment.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include <QDebug>
#include <list>
#include <algorithm>

class Allocator : public QObject
{
    Q_OBJECT
public:
    Allocator(std::list <Process *> & processes , std::list <Hole *> & holes );
    void startAllocator(QString allocationMethod);
    void firstFit();
    void bestFit();
    void worstFit();
    void joinHoles();

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


signals:
    void holeAllocated(Hole * allocatedHole);
private:
    std::list <Process *>  processes ;
    std::list <Hole *>  holes;
    std::list <Segment *> segments;
};

#endif // ALLOCATOR_H
