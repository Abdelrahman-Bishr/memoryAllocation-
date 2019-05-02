#include "allocator.h"

Allocator::Allocator(std::list<Process *> *processes, std::list<Hole *> *holes)
{
    this->holes=new std::list<Hole *> ();
    this->processes= new std::list<Process *> ();
    this->segments= new std::list<Segment *> ();

    this->holes=holes;
    this->processes=processes;
    for (std::list <Process *>::iterator i=processes->begin();i!=processes->end();i++ ){
            for (std::list <Segment *>::iterator j=(*i)->getSegmentsList()->begin() ; j!=(*i)->getSegmentsList()->end() ; j++){
                (*j)->setName((*j)->getName());
                this->segments->push_back(*j);
            }
    }

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
    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
        for (std::list<Segment * >::iterator j=segments->begin(); j!=segments->end();j++){
            if((*i)->getSize()>=(*j)->getSize()){
                (*i)->allocate(*j);
            }
        }
    }


}


void Allocator::worstFit(){
    qDebug()<<"worst fit allocation";
    segments->sort(largerSegment);
    holes->sort(largerHole);


    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
        qDebug()<<(*i)->getName()<<"    "<<(*i)->getSize();
    }

}

void Allocator::joinHoles()
{
    holes->sort(holeStart);
    if(holes->size()<=1)
        return;
    std::list<Hole * >::iterator j=holes->begin();
    j++;
    QString dummyI;
    QString dummyJ;
    dummyJ=(*j)->getName();
//    qDebug()<<"                                         holes initial count of allocator="<<holes->size();

    for (std::list<Hole * >::iterator i=holes->begin(); j!=holes->end() && i!=holes->end();i++){
        dummyJ=(*j)->getName();
        dummyI=(*i)->getName();
        if (((*j)->getStartAddress()-((*i)->getStartAddress()+(*i)->getSize()))==0){
            (*i)->setNewAttributes((*i)->getSize()+(*j)->getSize(),(*i)->getStartAddress());
            (*j)->setNewAttributes(0,(*j)->getStartAddress());
            emit holeAllocated(*i);
            emit holeEaten((*j)->getName());
//            qDebug()<<"found holes to join";
            delete *j;
            holes->erase(j);
            i--;
            j--;
//            qDebug()<<"                                         holes count of allocator="<<holes->size();
//            dummyJ=(*j)->getName();
        }
        j++;
    }
    holes->sort(largerHole);
}


void Allocator::bestFit(){
    qDebug()<<"best fit allocation";
    segments->sort(largerSegment);
    holes->sort(largerHole);


    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
        qDebug()<<(*i)->getName()<<"    "<<(*i)->getSize();
    }
    Hole * xHole;
    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
        qDebug()<<"holes size is "<<holes->size();
        xHole=*i;
        for (std::list<Segment * >::reverse_iterator j=segments->rbegin(); j!=segments->rend();j++){
            if(i!=holes->end()){
                xHole=*i;
                if ((*j)->isAllocated())
                    continue;
                else if((*i)->getSize()>=(*j)->getSize()){
                    (*i)->allocate(*j);
                    if(emit holeAllocated(*i)){
                        qDebug()<<"popped hole , breaking to get a new one or end";
                        i--;
                        break;
                    }
                    else {
                        qDebug()<<"existing hole with name="+(*i)->getName();
                    }
                }
            }
            else {
                break;
            }
        }
    }
    segments->sort(largerSegment);
    holes->sort(largerHole);
    QString alloc;
    for (std::list<Segment * >::iterator j=segments->begin(); j!=segments->end();j++){
        alloc=((*j)->isAllocated()) ? "Allocated at "+QString::number((*j)->getResidingAddress())+" with size="+QString::number((*j)->getSize()) : "Not Allocated";
        qDebug()<<(*j)->getName()<<"    "+alloc;
    }
}
