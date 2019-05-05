#include "allocator.h"

Allocator::Allocator(std::list<Process *> *processes, std::list<Hole *> *holes, int memorySize)
{
    this->holes=new std::list<Hole *> ();
    this->processes= new std::list<Process *> ();
    this->segments= new std::list<Segment *> ();
    memoryGraph=new Chart(memorySize);
    memoryDisplayLayout=nullptr;
    this->holes=holes;
    this->processes=processes;
    setSegments();
}

void Allocator::startAllocator(QString allocationMethod)
{
    qDebug()<<"starting allocator";
    joinHoles();
    if (allocationMethod=="First Fit"){
        firstFit();
        drawGraph();
    }
    else if (allocationMethod=="Best Fit"){
        bestFit();
        drawGraph();
    }
    else if (allocationMethod=="Worst Fit"){
        worstFit();
        drawGraph();
    }
}

void Allocator::firstFit(){
//    qDebug()<<"first fit allocation";
    setSegments();
    holes->sort(holeStart);
    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
        for (std::list<Segment * >::iterator j=segments->begin(); j!=segments->end();j++){
            if(i!=holes->end()){
                if ((*j)->isAllocated())
                    continue;
                else if((*i)->getSize()>=(*j)->getSize()){
                    (*i)->allocate(*j);
                    if(emit holeAllocated(*i)){
//                        qDebug()<<"popped hole , breaking to get a new one or end";
                        if(i!=holes->begin())
                            i--;
                        break;
                    }
                    else {
//                        qDebug()<<"existing hole with name="+(*i)->getName();
                    }
                }
            }
            else {
                break;
            }

        }
    }


}


void Allocator::worstFit(){
        segments->sort(largerSegment);
        holes->sort(largerHole);
        for (std::list<Hole *>::reverse_iterator i=holes->rbegin(); i!=holes->rend();i++){
            for (std::list<Segment * >::reverse_iterator j=segments->rbegin(); j!=segments->rend();j++){
                if(i!=holes->rend()){
                    if ((*j)->isAllocated())
                        continue;
                    else if((*i)->getSize()>=(*j)->getSize()){
                        (*i)->allocate(*j);
                        if(emit holeAllocated(*i)){
                            if(i!=holes->rbegin())
                                i--;
                            break;
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
    //        qDebug()<<(*j)->getName()<<"    "+alloc;
        }

}

void Allocator::joinHoles()
{
    holes=emit setHoles();
    processes=emit setProcesses();
    setSegments();
    holes->sort(holeStart);
    if(holes->size()<=1)
        return;
    std::list<Hole * >::iterator j=holes->begin();
    j++;
    QString dummyI;
    QString dummyJ;
    dummyJ=(*j)->getName();
//    qDebug()<<"                                         holes initial count of allocator="<<holes->size();
    std::list<Hole * >::iterator dummyIterator;
    for (std::list<Hole * >::iterator i=holes->begin(); j!=holes->end() && i!=holes->end();i++){
//        qDebug()<<"holes size is"<<holes->size();
        dummyJ=(*j)->getName();
        dummyI=(*i)->getName();
        if (((*j)->getStartAddress()-((*i)->getStartAddress()+(*i)->getSize()))==0){
            (*i)->setNewAttributes((*i)->getSize()+(*j)->getSize(),(*i)->getStartAddress());
            (*j)->setNewAttributes(0,(*j)->getStartAddress());
            if(emit holeAllocated(*i)){
//                qDebug()<<"i popped , holes size is "<<holes->size();
            }

            if(emit holeAllocated(*j)){
                j--;
//                qDebug()<<"J popped , holes size is "<<holes->size();
            }
        }
        j++;
    }
    holes->sort(largerHole);
}

void Allocator::setChartWidget(QVBoxLayout *memoryGroupBoxLayout)
{
    memoryGroupBoxLayout->addWidget(memoryGraph);
    memoryDisplayLayout=memoryGroupBoxLayout;
}

void Allocator::drawGraph()
{
//    qDebug()<<"in drawGraph";
    holes=emit setHoles();
    processes=emit setProcesses();
    setSegments();
    holes->sort(holeStart);
    segments->sort(segmentStart);
    memoryGraph->setHoles(holes);
    memoryGraph->setSegments(segments);
    if (memoryDisplayLayout!=nullptr){
        while (memoryDisplayLayout->count()>0)
            memoryDisplayLayout->removeItem(memoryDisplayLayout->itemAt(0));
    }
    memoryGraph->startGraphing();
}

void Allocator::setSegments()
{
    segments->clear();
    for (std::list <Process *>::iterator i=processes->begin();i!=processes->end();i++ ){
//        qDebug()<<"processes count in allocator="<<processes->size();
            for (std::list <Segment *>::iterator j=(*i)->getSegmentsList()->begin() ; j!=(*i)->getSegmentsList()->end() ; j++){
                this->segments->push_back(*j);
//                qDebug()<<"segments count in allocator="<<segments->size();
//                qDebug()<<"segments count in allocator of EntryUI="<<(*i)->getSegmentsList()->size();
            }
    }
}


void Allocator::bestFit(){
//    qDebug()<<"best fit allocation";
    segments->sort(largerSegment);
    holes->sort(largerHole);

//    qDebug()<<"holes count in allocator="<<holes->size();

    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
//        qDebug()<<(*i)->getName()<<"    "<<(*i)->getSize();
    }

    QString xHole;
    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
//        qDebug()<<"holes size is "<<holes->size();
        xHole=(*i)->getName();
        for (std::list<Segment * >::reverse_iterator j=segments->rbegin(); j!=segments->rend();j++){
            if(i!=holes->end()){
                xHole=(*i)->getName();
                if ((*j)->isAllocated())
                    continue;
                else if((*i)->getSize()>=(*j)->getSize()){
                    (*i)->allocate(*j);
                    if(emit holeAllocated(*i)){
//                        qDebug()<<"popped hole , breaking to get a new one or end";
                        if(i!=holes->begin())
                            i--;
                        break;
                    }
                    else {
//                        qDebug()<<"existing hole with name="+(*i)->getName();
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
//        qDebug()<<(*j)->getName()<<"    "+alloc;
    }
}
