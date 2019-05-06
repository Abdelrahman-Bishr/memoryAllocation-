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
    messageUser=new QMessageBox();
    messageUser->setText("allocator message");
    messageUser->hide();
    setSegments();
}

void Allocator::startAllocator(QString allocationMethod)
{
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

    drawGraph();
}

void Allocator::firstFit(){
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
                        if(i!=holes->begin())
                            i--;
                        break;
                    }
                }
            }
            else
                break;
        }
    }

    QString alloc="";
    for (std::list<Segment * >::iterator j=segments->begin(); j!=segments->end();j++){
        if(!(*j)->isAllocated()){
            alloc+=(*j)->getName()+" wasn't allocated , no room for it \n";
            }
    }
    messageUser->setText(alloc);
    messageUser->show();
}


void Allocator::worstFit(){
        segments->sort(largerSegment);
        holes->sort(largerHole);
        for (std::list<Segment * >::iterator j=segments->begin(); j!=segments->end();j++){
            if ((*j)->isAllocated())
                continue;
            for (std::list<Hole *>::reverse_iterator i=holes->rbegin(); i!=holes->rend();i++){
                if(i!=holes->rend()){
                    if((*i)->getSize()>=(*j)->getSize()){
                        (*i)->allocate(*j);
                        if(emit holeAllocated(*i)){
//                            holes->sort(largerHole);
//                            if(i!=holes->rbegin())
//                                i--;
//                            break;
                        }
                        holes->sort(largerHole);
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        segments->sort(largerSegment);
        holes->sort(largerHole);
        QString alloc="";
        for (std::list<Segment * >::iterator j=segments->begin(); j!=segments->end();j++){
            if(!(*j)->isAllocated()){
                alloc+=(*j)->getName()+" wasn't allocated , no room for it \n";
                }
        }
        messageUser->setText(alloc);
        messageUser->show();

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
    std::list<Hole * >::iterator dummyIterator;
    for (std::list<Hole * >::iterator i=holes->begin(); j!=holes->end() && i!=holes->end();i++){
        dummyJ=(*j)->getName();
        dummyI=(*i)->getName();
        if (((*j)->getStartAddress()-((*i)->getStartAddress()+(*i)->getSize()))==0){
            (*i)->setNewAttributes((*i)->getSize()+(*j)->getSize(),(*i)->getStartAddress());
            (*j)->setNewAttributes(0,(*j)->getStartAddress());
            if(emit holeAllocated(*i)){
                i--;
            }

            if(emit holeAllocated(*j)){
                j--;
                i--;
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
            for (std::list <Segment *>::iterator j=(*i)->getSegmentsList()->begin() ; j!=(*i)->getSegmentsList()->end() ; j++){
                this->segments->push_back(*j);
            }
    }
}


void Allocator::bestFit(){
    segments->sort(largerSegment);
    holes->sort(largerHole);
    for (std::list<Hole * >::iterator i=holes->begin(); i!=holes->end();i++){
        for (std::list<Segment * >::reverse_iterator j=segments->rbegin(); j!=segments->rend();j++){
            if(i!=holes->end()){
                if ((*j)->isAllocated())
                    continue;
                else if((*i)->getSize()>=(*j)->getSize()){
                    (*i)->allocate(*j);
                    if(emit holeAllocated(*i)){
                        if(i!=holes->begin())
                            i--;
                        break;
                    }
                    else {
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
    QString alloc="";
    for (std::list<Segment * >::iterator j=segments->begin(); j!=segments->end();j++){
        if(!(*j)->isAllocated()){
            alloc+=(*j)->getName()+" wasn't allocated , no room for it \n";
            }
    }

    messageUser->setText(alloc);
    messageUser->show();
}
