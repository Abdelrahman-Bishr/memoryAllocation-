#include "allocator.h"

Allocator::Allocator(std::list<Process *> &processes, std::list<Hole *> &holes)
{
    this->holes=holes;
    this->processes=processes;
    for (std::list <Process *>::iterator i=processes.begin();i!=processes.end();i++ ){
        for (std::list <Segment *>::iterator j=(*i)->getSegmentsList().begin() ; j!=(*i)->getSegmentsList().end() ; j++){
            (*j)->setName((*i)->getName()+"::"+(*j)->getName());
            this->segments.push_back(*j);
        }
    }
}

void Allocator::startAllocator(QString allocationMethod)
{
    if (allocationMethod=="First Fit"){
        firstFit();
    }
    else if (allocationMethod=="Best Fit"){
        bestFit();
    }
    else if (allocationMethod=="Worst Fit"){
        worstFit();
    }
}

void Allocator::firstFit(){
    qDebug()<<"first fit allocation";
    for (std::list<Hole * >::iterator i=holes.begin(); i!=holes.end();i++){
        for (std::list<Segment * >::iterator j=segments.begin(); j!=segments.end();j++){
            if((*i)->getSize()>=(*j)->getSize()){
                (*i)->allocate(*j);
            }
        }
    }


}


void Allocator::worstFit(){
    qDebug()<<"worst fit allocation";
    segments.sort(largerSegment);
    holes.sort(largerHole);

    qDebug()<<"sorted segments and holes";

    for (std::list<Hole * >::iterator i=holes.begin(); i!=holes.end();i++){
        qDebug()<<(*i)->getName()<<"    "<<(*i)->getSize();
    }

}

void Allocator::joinHoles()
{
    holes.sort(holeStart);
    std::list<Hole * >::iterator j=holes.begin();
    j++;
    for (std::list<Hole * >::iterator i=holes.begin(); j!=holes.end();i++){
        if (((*j)->getStartAddress()-((*i)->getStartAddress()+(*i)->getSize()))==1){
            (*i)->setNewAttributes((*i)->getSize()+(*j)->getSize(),(*i)->getStartAddress());
            holes.erase(j);
        }
        j++;
    }
    holes.sort(largerHole);
}


void Allocator::bestFit(){
    qDebug()<<"best fit allocation";
    segments.sort(largerSegment);
    holes.sort(largerHole);

    qDebug()<<"sorted segments and holes";

    for (std::list<Hole * >::iterator i=holes.begin(); i!=holes.end();i++){
        qDebug()<<(*i)->getName()<<"    "<<(*i)->getSize();
    }
    for (std::list<Hole * >::iterator i=holes.begin(); i!=holes.end();i++){
        for (std::list<Segment * >::iterator j=segments.begin(); j!=segments.end();j++){
            if((*i)->getSize()>=(*j)->getSize()){
                (*i)->allocate(*j);
            }
        }
    }
    segments.sort(largerSegment);
    holes.sort(largerHole);
    QString alloc;
    for (std::list<Segment * >::iterator j=segments.begin(); j!=segments.end();j++){
        alloc=((*j)->getSize()<<(*j)->isAllocated()) ? "Allocated" : "Not Allocated";
        qDebug()<<(*j)->getName()<<"    "+alloc;
    }
}
