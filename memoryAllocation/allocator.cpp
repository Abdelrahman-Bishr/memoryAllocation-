#include "allocator.h"

Allocator::Allocator(std::list<Process *> &processes, std::list<Hole *> &holes)
{
    this->holes=holes;
    this->processes=processes;
//    for (std::list <Process *>::iterator i=processes.begin();i!=this->processes.end();i++ ){
//        for (std::list <Segment *>::iterator j=(*i)->getSegmentsList().begin() ; j!=(*i)->getSegmentsList().end() ; j++){
//            (*j)->setName((*j)->getName());
//            this->segments.push_back(*j);
//        }
//    }
}

void Allocator::startAllocator(QString allocationMethod)
{
    qDebug()<<"starting allocator";
    joinHoles();
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
    QString dummyI;
    QString dummyJ;
    dummyJ=(*j)->getName();
    for (std::list<Hole * >::iterator i=holes.begin(); j!=holes.end() && i!=holes.end();i++){
        dummyJ=(*j)->getName();
        dummyI=(*i)->getName();
        if (((*j)->getStartAddress()-((*i)->getStartAddress()+(*i)->getSize()))==0){
            (*i)->setNewAttributes((*i)->getSize()+(*j)->getSize(),(*i)->getStartAddress());
            (*j)->setNewAttributes(0,(*j)->getStartAddress());
            emit holeAllocated(*i);
            emit holeAllocated(*j);
            qDebug()<<"found holes to join";
//            delete *j;
//            holes.erase(j);
//            j--;
            qDebug()<<"                                         holes count of allocator="<<holes.size();
            j--;
            i--;
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
        for (std::list<Segment * >::reverse_iterator j=segments.rbegin(); j!=segments.rend();j++){
            if(i!=holes.end()){
                if ((*j)->isAllocated())
                    continue;
                else if((*i)->getSize()>=(*j)->getSize()){
                    (*i)->allocate(*j);
                    emit holeAllocated(*i);
                }
            }
            else {
                break;
            }
        }
    }
    segments.sort(largerSegment);
    holes.sort(largerHole);
    QString alloc;
    for (std::list<Segment * >::iterator j=segments.begin(); j!=segments.end();j++){
        alloc=((*j)->isAllocated()) ? "Allocated at "+QString::number((*j)->getResidingAddress())+" with size="+QString::number((*j)->getSize()) : "Not Allocated";
        qDebug()<<(*j)->getName()<<"    "+alloc;
    }
}
