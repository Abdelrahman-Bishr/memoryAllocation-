#include "myprocess.h"

Process::Process(QString name, int id, int segments)
{
    this->name=name;
    this->id=id;
    this->segmentsCount=segments;
    this->segments=new std::list<Segment *> ();
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
    return segments->size();
}


QString Process::getSegmentName(int segmentIndex){
    std::list <Segment *>::iterator it=segments->begin();
    int i=0;
    while (i<segmentIndex) {
        it++;
        i++;
    }
    if (segmentIndex>=0 && segmentIndex<segments->size())
        return (*it)->getName();
    return "";
}


int Process::getSegmentSize(QString segmentName){
    for (std::list<Segment *>::iterator i=segments->begin();i!=segments->end() ;i++){
        if ((*i)->getName()==segmentName)
            return (*i)->getSize();
    }
    return -1;
}


int Process::getSegmentSize(int segmentIndex){
    std::list <Segment *>::iterator it=segments->begin();
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
    newSeg=new Segment (this->name+"::"+newSegmentName,newSegmentSize,getNumberOfEnteredSegments()+1);
    segments->push_back(newSeg);
    segsListWidget->addItem(newSeg->getName());
    connect(newSeg,SIGNAL(deallocated(Segment*)),this,SLOT(segmentDeallocated(Segment*)));
}

std::list<Segment *> *Process::getSegmentsList()
{
    return  segments;
}

int Process::getSize()
{
    int size=0;
    for (std::list <Segment *>::iterator i=segments->begin(); i!=segments->end(); i++){
        size+=(*i)->getSize();
    }
    return size;
}

bool Process::isAllocated()
{
    for (std::list <Segment *>::iterator i=segments->begin(); i!=segments->end(); i++){
        if(!(*i)->isAllocated())
            return false;
    }
    return true;
}

int Process::getID()
{
    return id;
}

void Process::segmentDeallocated(Segment *deallocatedSegment)
{
    emit deallocated(deallocatedSegment);
}

