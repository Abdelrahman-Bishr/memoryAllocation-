#include "process.h"

Process::Process(QString name, int id, int segments)
{
    this->name=name;
    this->id=id;
    this->segmentsCount=segments;
    segsListWidget=new QListWidget();
//    segmentsList=new QList <Segment *> ();
}


QString Process::getName(){
    return name;
}

int Process::getNumberOfSegments(){
    return segmentsCount;
}

int Process::getNumberOfEnteredSegments()
{
    return segmentsList.size();
}


QString Process::getSegmentName(int segmentIndex){
    if (segmentIndex>=0 && segmentIndex<segmentsList.size())
        return segmentsList[segmentIndex]->getName();
    return "";
}


int Process::getSegmentSize(QString segmentName){
    for (int i=0;i<segmentsList.size();i++){
        if (segmentsList[i]->getName()==segmentName)
            return segmentsList[i]->getSize();
    }
    return -1;
}


int Process::getSegmentSize(int segmentIndex){
    return segmentsList[segmentIndex]->getSize();
}

QListWidget *Process::getSegmentsListWidget()
{
    return segsListWidget;
}

void Process::setNewSegment(QString name, int size)
{
    newSegmentName=name;
    newSegmentSize=size;
}

void Process::addSegment()
{
    newSeg=new Segment (newSegmentName,newSegmentSize);
    segmentsList.append(newSeg);
    segsListWidget->addItem(newSeg->getName());
}

