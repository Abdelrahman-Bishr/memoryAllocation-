#include "EntryUI.h"
#define holesInputs 2
#define processInputs 4
#define buttonsNum 9

EntryUI::EntryUI()
{    

    allocationMethod="";
    processes= new std::list<Process *> ();
    holes= new std::list<Hole *> ();
    enteredSegments=0;
    holeID=0;
    processID=1;
    memorySize=2000;
    currentProcess=nullptr;
    newHole=nullptr;
    newProcess=nullptr;
    currentHole=nullptr;
    currentSegment=nullptr;
    memoryAllocator=nullptr;
    this->setEnabled(true);
    this->setFocus();
    createItems();
    createLayouts();
    setLabelTexts();
    setInitialDisplay();
    signalsHandler();
}





void EntryUI::addHole()
{
    if (holesInput[0]->text()=="" || holesInput[1]->text()=="")
        return;
    if (holesInput[1]->text().toInt()<=0)
        return;
    for (std::list <Hole *>::iterator i=holes->begin() ;i!=holes->end();i++){
        if ((holesInput[0]->text().toInt() >= (*i)->getStartAddress() && holesInput[0]->text().toInt() < (*i)->getStartAddress()+ (*i)->getSize())  ||
                ((holesInput[0]->text().toInt()+holesInput[1]->text().toInt()) > (*i)->getStartAddress() &&
                 (holesInput[0]->text().toInt()+holesInput[1]->text().toInt()) <=  (*i)->getStartAddress()+ (*i)->getSize()) ){
            messageUser->setText("interlapping holes");
            messageUser->show();
            return;
        }
    }
    QString holeName="Hole"+QString::number(holeID)+"       "+holesInput[0]->text()+" : "+QString::number( holesInput[0]->text().toInt()+holesInput[1]->text().toInt()-1);
    addNewHole(holeName,holesInput[0]->text().toInt(),holesInput[1]->text().toInt());
    if (memoryAllocator!=nullptr){
        memoryAllocator->joinHoles();
        memoryAllocator->drawGraph();
    }
}






void EntryUI::addProcess()
{
    if (processInput[0]->text()=="" || processInput[1]->text()=="")
        return;

    for (std::list <Process *>::iterator i=processes->begin() ;i!=processes->end();i++){
        if(processInput[0]->text()==(*i)->getName()){
            messageUser->setText("process enterted before");
            messageUser->show();
            return ;
        }
    }
    if(currentProcess==nullptr || currentProcess->getNumberOfSegments()==enteredSegments){
        segmentsListWidget->hide();
        displayListLayout->removeWidget(segmentsListWidget);
        displayListLayout->removeWidget(processesListWidget);
        enteredSegments=0;
        newProcess=new Process(processInput[0]->text(),processID,processInput[1]->text().toInt());
        processesListWidget->addItem(processInput[0]->text());
        currentProcess=newProcess;
        processes->push_back(newProcess);
        processID++;
        segmentsListWidget=newProcess->getSegmentsListWidget();
        displayListLayout->insertRow(0,processesListWidget,segmentsListWidget);
        connect(currentProcess->getSegmentsListWidget(),SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(segmentSelected(QListWidgetItem*)));
        connect(currentProcess,SIGNAL(deallocated(Segment *)),this,SLOT(segmentDeallocated(Segment *)));
    }
}





void EntryUI::addSegment()
{    
    if(currentProcess==nullptr){
        return;
    }
    if (processInput[2]->text()=="" || processInput[3]->text()=="")
        return;
    for (int i=0;i<currentProcess->getNumberOfEnteredSegments();i++){
        if (currentProcess->getName()+"::"+processInput[2]->text()==currentProcess->getSegmentName(i)){
            messageUser->setText("segment already enterd before");
            messageUser->show();
            return ;
        }
    }
    if(currentProcess->getNumberOfEnteredSegments()<currentProcess->getNumberOfSegments()){
        if(currentProcess!=nullptr){
            enteredSegments++;
            currentProcess->setNewSegment(processInput[2]->text()+"     "+processInput[3]->text() , processInput[3]->text().toInt());
            currentProcess->addSegment();
        }
    }
//    adding segment has nothing to do with allocator , allocating or deallocating it is what is relevant to allocator
}


std::list <Hole *>::iterator EntryUI::popHole()
{
    if(currentHole==nullptr){
        messageUser->setText("Select a hole first");
        messageUser->show();
        return holes->end();
    }
//    qDebug()<<"popping hole in EntryUI";
    for (std::list<Hole *>::iterator i=holes->begin();i!=holes->end();i++){
        if(currentHole==(*i)){
//remove hole from display
            for (int j=0;j<holesListWidget->count();j++){
                if(holesListWidget->item(j)->text()==currentHole->getName()){
//                    qDebug()<<"removing from holes list widget hole "<<currentHole->getName();
                    holesListWidget->setItemHidden(holesListWidget->item(j),true);
                    holesListWidget->removeItemWidget(holesListWidget->item(j));
                    break;
                }
            }
//remove hole from holes list
            delete (*i);
//            holes->erase(i);
            currentHole=nullptr;
            return i;
        }
    }
    return holes->end();
}



void EntryUI::popProcess()
{
    if(currentProcess==nullptr)
        return ;
    for (std::list <Process *>::iterator j=processes->begin(); j!=processes->end();j++){
        if((*j)==currentProcess){                                                                   //find the required process to be popped
//            qDebug()<<"process to be removed :: "<<(*j)->getName();
            segmentsListWidget=currentProcess->getSegmentsListWidget();
//            int k=0;
            for (std::list<Segment *>::iterator i=(*j)->getSegmentsList()->begin();i!=(*j)->getSegmentsList()->end();i++){      //pop its segments one by one
                currentSegment=*i;
                popSegment();
                i--;
//                (*i)->deallocate();
//                segmentsListWidget->setItemHidden(segmentsListWidget->item(k),true);
//                segmentsListWidget->removeItemWidget(segmentsListWidget->item(k));
//                delete (*i);
//                k++;
            }
            for (int i=0;i<processesListWidget->count();i++){
                if(processesListWidget->item(i)->text()==currentProcess->getName()){
//                    qDebug()<<"process label to be removed from list is "<<processesListWidget->item(i)->text();
                    processesListWidget->setItemHidden(processesListWidget->item(i),true);
                    processesListWidget->removeItemWidget(processesListWidget->item(i));
                    break;
                }
            }

            (*j)->getSegmentsList()->clear();
            delete (*j);
            processes->erase(j);

            break;
        }
    }

    currentProcess=*processes->begin();
    processSelected(processesListWidget->item(0));
    if (memoryAllocator!=nullptr){
        memoryAllocator->drawGraph();
    }
}


void EntryUI::popSegment()
{
//    qDebug()<<"trying to pop a Segment";
    if(currentSegment==nullptr || currentProcess==nullptr){
    if(currentSegment==nullptr ){
        messageUser->setText("You must select a segment");
        messageUser->show();
    }
    else if(currentProcess==nullptr ){
        messageUser->setText("You must select a process");
        messageUser->show();
    }
        return ;
    }
//    qDebug()<<"popping segment";
    for (std::list<Segment *>::iterator i=currentProcess->getSegmentsList()->begin();i!=currentProcess->getSegmentsList()->end();i++){
        if (currentSegment==(*i)){
            for (int j=0;j<segmentsListWidget->count();j++){
                if(segmentsListWidget->item(j)->text()==currentSegment->getName()){
                    segmentsListWidget->setItemHidden(segmentsListWidget->item(j),true);
                    segmentsListWidget->removeItemWidget(segmentsListWidget->item(j));
//                    qDebug()<<"segment popping from list confirmed";
                    break;
                }
            }
//            qDebug()<<"segment popping confirmed";
            currentSegment->deallocate();
            if (memoryAllocator!=nullptr)
                memoryAllocator->joinHoles();
            delete (*i);
            currentProcess->getSegmentsList()->erase(i);
            currentSegment=nullptr;
            break;
        }
    }
//    if (memoryAllocator!=nullptr){
//        memoryAllocator->drawGraph();
//    }
}


void EntryUI::buttonClicked(ControlButtons *sourceButton)
{
    if (sourceButton==actionButtons[0])
        addHole();
    else if (sourceButton==actionButtons[3])
        addProcess();
    else if (sourceButton==actionButtons[6])
        addSegment();
    else if (sourceButton==actionButtons[1]){
        std::list <Hole *>::iterator i=popHole();
        if (i!=holes->end())
            holes->erase(i);
        if (memoryAllocator!=nullptr){
//            memoryAllocator->startAllocator(allocationMethod);
            memoryAllocator->drawGraph();
        }
    }
    else if (sourceButton==actionButtons[4]){
        popProcess();
    }
    else if (sourceButton==actionButtons[7]){
        popSegment();
        if (memoryAllocator!=nullptr){
            memoryAllocator->drawGraph();
        }
    }
}

void EntryUI::startAllocation()
{
    if(memoryAllocator!=nullptr)
        delete memoryAllocator;
//    qDebug()<<"creating allocator";
    memoryAllocator=new Allocator (processes,holes,memorySize);
    memoryAllocator->setChartWidget(memoryLayout);
    connect(memoryAllocator,SIGNAL(holeAllocated(Hole *)),this,SLOT(holeAllocated(Hole *)));
    connect(memoryAllocator,SIGNAL(holeEaten(QString)),this,SLOT(removeHoleFromListWidget(QString)));
    connect(memoryAllocator,SIGNAL(setHoles()),this,SLOT(getHoles()));
    connect(memoryAllocator,SIGNAL(setProcesses()),this,SLOT(getProcesses()));
    connect(memoryAllocator,SIGNAL(deallocateProcess(Process *)),this,SLOT(deallocateProcess(Process *)));
    allocationMethod=fittingMethod->currentText();
    memoryAllocator->startAllocator(allocationMethod);


}

void EntryUI::processSelected(QListWidgetItem *selectedProcess)
{
    for (std::list<Process *>::iterator i=processes->begin(); i!=processes->end();i++){
        if ((*i)->getName()==selectedProcess->text()){

            displayListLayout->removeWidget(segmentsListWidget);
            displayListLayout->removeWidget(processesListWidget);
            if (currentProcess!= nullptr)
                currentProcess->getSegmentsListWidget()->hide();
            currentProcess=(*i);
            currentProcess->getSegmentsListWidget()->show();
            segmentsListWidget=(*i)->getSegmentsListWidget();
            displayListLayout->insertRow(0,processesListWidget,(*i)->getSegmentsListWidget());
            break;
        }
    }
}

void EntryUI::holeSelected(QListWidgetItem *selectedHole)
{
    for (std::list <Hole *>::iterator i=holes->begin() ;i!=holes->end();i++){
        if(selectedHole->text()==(*i)->getName()){
            currentHole=(*i);
            break;
        }
    }
}

void EntryUI::segmentSelected(QListWidgetItem *selectedSegment)
{
    if (currentProcess==nullptr)
        return ;
    for (std::list<Segment *>::iterator i=currentProcess->getSegmentsList()->begin(); i!=currentProcess->getSegmentsList()->end();i++){
        if(selectedSegment->text()==(*i)->getName()){
            currentSegment=(*i);
        }
    }
}

void EntryUI::setMemorySize(QString sizeText)
{
    memorySize=sizeText.toInt();
}

bool EntryUI::holeAllocated(Hole *allocatedHole)
{
//    qDebug()<<"EntryUI:: new hole start address="<<allocatedHole->getStartAddress();
    if (allocatedHole->getSize()<=0){
        currentHole=allocatedHole;
        std::list <Hole *>::iterator i=popHole();
        if (i!=holes->end())
            holes->erase(i);
        return true;
    }
    for (int j=0;j<holesListWidget->count();j++){
        if(holesListWidget->item(j)->text()==allocatedHole->getName()){
            holesListWidget->hide();
            holesListWidget->setItemHidden(holesListWidget->item(j),true);
            holesListWidget->removeItemWidget(holesListWidget->item(j));
            QString newName=allocatedHole->getName().split(" ")[0]+"       "+QString::number(allocatedHole->getStartAddress())+" : "+
                    QString::number(allocatedHole->getStartAddress()+allocatedHole->getSize()-1);
            holesListWidget->insertItem(j,newName);
            allocatedHole->setName(newName);
            holesListWidget->show();
            return false;
        }
    }
    return false;
}

void EntryUI::segmentDeallocated(Segment *deallocatedSegment)
{
    int residingAddress=deallocatedSegment->getResidingAddress();
    if (residingAddress<0)
        return;
    QString holeName="Hole"+QString::number(holeID)+" "+QString::number(residingAddress)+" : "+QString::number(residingAddress+deallocatedSegment->getSize()-1);
    addNewHole(holeName,residingAddress,deallocatedSegment->getSize());
}

void EntryUI::removeHoleFromListWidget(QString holeName)
{
//    qDebug()<<"responding to an eaten hole , HUUMMMMMMM";
    for (int j=0;j<holesListWidget->count();j++){
        if(holesListWidget->item(j)->text()==holeName){
            holesListWidget->setItemHidden(holesListWidget->item(j),true);
            holesListWidget->removeItemWidget(holesListWidget->item(j));
            return;
        }
    }
}

void EntryUI::deallocateProcess(Process *processToDeallocate)
{
    currentProcess=processToDeallocate;
    deallocateProcess();
}

std::list<Process *> *EntryUI::getProcesses()
{
    return processes;
}

std::list<Hole *> *EntryUI::getHoles()
{
    return holes;
}

void EntryUI::deallocateProcess()
{
    if(currentProcess==nullptr)
        return;
    for (std::list <Process *>::iterator j=processes->begin() ;j!=processes->end();j++){
        if(currentProcess==(*j)){
            for (std::list<Segment *>::iterator i=(*j)->getSegmentsList()->begin();i!=(*j)->getSegmentsList()->end();i++){
                (*i)->deallocate();
            }
        }
    }

    if(memoryAllocator!=nullptr){
        memoryAllocator->joinHoles();
        memoryAllocator->drawGraph();
    }
}


void EntryUI::createItems()
{
    startButton=new QPushButton("Start Allocation");
    deallocationButton=new QPushButton("Deallocate Process");
    messageUser=new QMessageBox();
    messageUser->setText("entry message");
    messageUser->hide();

    memoryDisplayGroup=new QGroupBox("Memory",this);
    holesGroup=new QGroupBox("Holes",this);
    processGroup=new QGroupBox("Process",this);
    segmentsGroup=new QGroupBox("Segments",this);
    listingGroup=new QGroupBox ("Exisiting Processes && Segments",this);

    actionButtons=new ControlButtons * [buttonsNum];
    processesListWidget =new QListWidget(this);
    segmentsListWidget =new QListWidget();
    holesListWidget=new QListWidget(this);

    actionButtons[0]=new ControlButtons("Add"   ,holesGroup);
    actionButtons[1]=new ControlButtons("Pop"   ,holesGroup);
    actionButtons[2]=new ControlButtons("Cancel",holesGroup);
    actionButtons[3]=new ControlButtons("Add"   ,processGroup);
    actionButtons[4]=new ControlButtons("Pop"   ,processGroup);
    actionButtons[5]=new ControlButtons("Cancel",processGroup);
    actionButtons[6]=new ControlButtons("Add"   ,segmentsGroup);
    actionButtons[7]=new ControlButtons("Pop"   ,segmentsGroup);
    actionButtons[8]=new ControlButtons("Cancel",segmentsGroup);


    holesInput=new QLineEdit * [holesInputs];
    holesInputLabel=new QLabel * [holesInputs];
    for (int i=0;i<holesInputs;i++){
        holesInput[i]=new QLineEdit(this);
        holesInputLabel[i]=new QLabel(this);
        holesInput[i]->setValidator( new QIntValidator(1, 100000) );
    }
    processInput=new QLineEdit * [processInputs];
    processInputLabel=new QLabel * [processInputs];
    for (int i=0;i<processInputs;i++){
        processInput[i]=new QLineEdit(this);
        if(i%2==1)
            processInput[i]->setValidator( new QIntValidator(1, 100000) );
        processInputLabel[i]=new QLabel(this);
    }

    fittingMethod=new QComboBox(this);
    memorySizeInput=new QInputDialog();
    memorySizeInput->setLabelText("Enter Memory Size");
    memorySizeInput->show();
    memorySizeInput->setInputMode(QInputDialog::IntInput);
    memorySizeInput->setIntRange(1,999999999);
    memorySizeInput->setIntValue(2000);
    memoryDisplayGroup->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);
    processesListWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
}

void EntryUI::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return ){
        if (holesInput[0]->hasFocus() || holesInput[1]->hasFocus() ){
            addHole();
        }
        else if (processInput[0]->hasFocus() || processInput[1]->hasFocus() ){
            addProcess();
        }
        else if (processInput[2]->hasFocus() || processInput[3]->hasFocus() ){
            addSegment();
        }
    }
    else if (event->key()==Qt::Key_Delete){
        if (holesListWidget->hasFocus()){
            std::list <Hole *>::iterator i=popHole();
            if (i!=holes->end())
                holes->erase(i);
            if (memoryAllocator!=nullptr){
//                memoryAllocator->startAllocator(allocationMethod);
                memoryAllocator->drawGraph();
            }

        }
        if (processesListWidget->hasFocus()){
            popProcess();
        }
        if (segmentsListWidget->hasFocus()){
            popSegment();
            if (memoryAllocator!=nullptr){
                memoryAllocator->drawGraph();
            }
        }
    }

}



void EntryUI::setLabelTexts()
{
    fittingMethod->addItem("Best Fit");
    fittingMethod->addItem("First Fit");
    fittingMethod->addItem("Worst Fit");

    holesInputLabel[0]->setText("Start Address: ");
    holesInputLabel[1]->setText("Size: ");

    processInputLabel[0]->setText("Name");
    processInputLabel[1]->setText("Number Of Segments");
    processInputLabel[2]->setText("Name");
    processInputLabel[3]->setText("Size");

}



void EntryUI::setInitialDisplay()
{
    this->setLayout(windowLayout);
    windowLayout->addLayout(entryLayout);
    memoryDisplayGroup->setLayout(memoryLayout);
    windowLayout->addWidget(listingGroup);
    windowLayout->addWidget(memoryDisplayGroup);
    listingGroup->setLayout(displayListLayout);
    entryLayout->addWidget(fittingMethod);
    entryLayout->addWidget(holesGroup);
    entryLayout->addWidget(processGroup);


    for (int i=0;i<holesInputs;i++) {
        holesInputLayout->addRow(holesInputLabel[i],holesInput[i]);
        actionButtons[0]->addQLineEdit(holesInput[i]);
    }
    holesInputLayout->addRow(actionButtons[0],actionButtons[1]);
    holesInputLayout->addWidget(actionButtons[2]);
    holesGroup->setLayout(holesInputLayout);

    processGroup->setLayout(processInputLayout);
    processInputLayout->addRow(processInputLabel[0],processInput[0]);
    processInputLayout->addRow(processInputLabel[1],processInput[1]);
    actionButtons[3]->addQLineEdit(processInput[0]);
    actionButtons[3]->addQLineEdit(processInput[1]);
    for (int i=2;i<processInputs;i++) {
        processInputLabel[i]->setParent(segmentsGroup);
        processInput[i]->setParent(segmentsGroup);
        segsLayout->addRow(processInputLabel[i],processInput[i]);
        actionButtons[6]->addQLineEdit(processInput[i]);
    }
    segsLayout->addRow(actionButtons[6],actionButtons[7]);
    segsLayout->addWidget(actionButtons[8]);
    processInputLayout->addRow(actionButtons[3],actionButtons[4]);
    processInputLayout->addWidget(actionButtons[5]);
    processInputLayout->addRow(segmentsGroup);
    segmentsGroup->setLayout(segsLayout);

    displayListLayout->addRow(processesListWidget,segmentsListWidget);
    displayListLayout->addRow(holesListWidget);
    displayListLayout->addRow(startButton);
    displayListLayout->addRow(deallocationButton);


}

void EntryUI::createLayouts()
{
    holesInputLayout=new QFormLayout();
    segsLayout=new QFormLayout();
    displayListLayout=new QFormLayout();
    entryLayout=new QVBoxLayout();
    windowLayout=new QHBoxLayout();
    processInputLayout=new QFormLayout();
    verSpacer=new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding);
    horSpacer=new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
    memoryLayout=new QVBoxLayout();
    memoryLayout->setSizeConstraint(memoryLayout->SetMinimumSize);
}

void EntryUI::signalsHandler()
{
    for (int i=0;i<buttonsNum;i++) {
        connect(actionButtons[i],SIGNAL(clickedSignal(ControlButtons *)),this,SLOT(buttonClicked(ControlButtons *)));
        }
    connect(startButton,SIGNAL(clicked()),this,SLOT(startAllocation()));
    connect(processesListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(processSelected(QListWidgetItem*)));
    connect(holesListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(holeSelected(QListWidgetItem*)));
    connect(segmentsListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(segmentSelected(QListWidgetItem*)));
    connect(memorySizeInput,SIGNAL(textValueSelected(QString)),this,SLOT(setMemorySize(QString)));
    connect(deallocationButton,SIGNAL(clicked()),this,SLOT(deallocateProcess()));
}

void EntryUI::addNewHole(QString holeName, int startingAddress, int size)
{
    newHole=new Hole (holeName,startingAddress,size);
    currentHole=newHole;
    holes->push_back(newHole);
    holesListWidget->addItem(holeName);
    holeID++;
}
