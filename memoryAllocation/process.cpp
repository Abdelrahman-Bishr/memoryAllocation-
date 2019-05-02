#include "process.h"

Process::Process(QString name, int id, int segments)
{
    this->name=name;
    this->id=id;
    this->segmentsCount=segments;
    segsListWidget=new QListWidget();
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
    std::list <Segment *>::iterator it=segmentsList.begin();
    int i=0;
    while (i<segmentIndex) {
        it++;
        i++;
    }
    if (segmentIndex>=0 && segmentIndex<segmentsList.size())
        return (*it)->getName();
    return "";
}


int Process::getSegmentSize(QString segmentName){
    for (std::list<Segment *>::iterator i=segmentsList.begin();i!=segmentsList.end() ;i++){
        if ((*i)->getName()==segmentName)
            return (*i)->getSize();
    }
    return -1;
}


int Process::getSegmentSize(int segmentIndex){
    std::list <Segment *>::iterator it=segmentsList.begin();
    int i=0;
    while (i<segmentIndex) {
        it++;
        i++;
    }
    return (*it)->getSize();
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
    newSeg=new Segment (this->name+"::"+newSegmentName,newSegmentSize);
    segmentsList.push_back(newSeg);
    segsListWidget->addItem(newSeg->getName());
    connect(newSeg,SIGNAL(deallocated(Segment*)),this,SLOT(segmentDeallocated(Segment*)));
}

std::list<Segment *> &Process::getSegmentsList()
{
    return  segmentsList;
}

void Process::segmentDeallocated(Segment *deallocatedSegment)
{
    emit deallocated(deallocatedSegment);
}

