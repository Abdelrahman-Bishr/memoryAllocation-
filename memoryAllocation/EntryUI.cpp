#include "EntryUI.h"
#define holesInputs 2
#define processInputs 4
#define buttonsNum 9

EntryUI::EntryUI()
{

    enteredSegments=0;
    holeID=0;
    processID=1;
    currentProcess=nullptr;
    newHole=nullptr;
    newProcess=nullptr;
    currentHole=nullptr;
    currentSegment=nullptr;
    memoryAllocator=nullptr;
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
    for (std::list <Hole *>::iterator i=holes.begin() ;i!=holes.end();i++){
        if ((holesInput[0]->text().toInt() >= (*i)->getStartAddress() && holesInput[0]->text().toInt() < (*i)->getStartAddress()+ (*i)->getSize())  ||
                ((holesInput[0]->text().toInt()+holesInput[1]->text().toInt()) > (*i)->getStartAddress() &&
                 (holesInput[0]->text().toInt()+holesInput[1]->text().toInt()) <=  (*i)->getStartAddress()+ (*i)->getSize()) ){
            qDebug()<<"interlapping holes";
            return;
        }

    }
    qDebug()<<"Adding Hole";
    QString holeName="Hole"+QString::number(holeID);
    newHole=new Hole (holeName,holesInput[0]->text().toInt(),holesInput[1]->text().toInt());
    currentHole=newHole;
    holes.push_back(newHole);
    holesListWidget->addItem(holeName+"       "+holesInput[0]->text()+" : "+QString::number( holesInput[0]->text().toInt()+holesInput[1]->text().toInt()-1 ));
    holeID++;
}

void EntryUI::addProcess()
{
    for (std::list <Process *>::iterator i=processes.begin() ;i!=processes.end();i++){
        if(processInput[0]->text()==(*i)->getName()){
            qDebug()<<"process Enterted before";
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
        processes.push_back(newProcess);
        processID++;
        segmentsListWidget=newProcess->getSegmentsListWidget();
        displayListLayout->insertRow(0,processesListWidget,segmentsListWidget);
    }
}
void EntryUI::addSegment()
{
    if(newProcess==NULL){
        qDebug()<<"No processes entered";
        return;
    }
    for (int i=0;i<newProcess->getNumberOfEnteredSegments();i++){
        if (processInput[2]->text()==newProcess->getSegmentName(i)){
            qDebug()<<"segment already Enterd";
            return ;
        }
    }
    if(enteredSegments<newProcess->getNumberOfSegments()){
        qDebug()<<"Adding Segment";
        if(newProcess!=nullptr){
            enteredSegments++;
            newProcess->setNewSegment(processInput[2]->text() , processInput[3]->text().toInt());
            newProcess->addSegment();
        }
    }
}

void EntryUI::buttonClicked(ControlButtons *sourceButton)
{
    qDebug()<<"clicked button is "<<sourceButton->text();
    if (sourceButton==actionButtons[0])
        addHole();
    else if (sourceButton==actionButtons[3])
        addProcess();
    else if (sourceButton==actionButtons[6])
        addSegment();
    else if (sourceButton==actionButtons[1])
        popHole();
    else if (sourceButton==actionButtons[4]){
        popProcess();
    }
    else if (sourceButton==actionButtons[7])
        addSegment();

}

void EntryUI::startAllocation()
{
    qDebug()<<"creating allocator";
    memoryAllocator=new Allocator (processes,holes);
    memoryAllocator->startAllocator("Best Fit");
}

void EntryUI::processSelected(QListWidgetItem *selectedProcess)
{
    for (std::list<Process *>::iterator i=processes.begin(); i!=processes.end();i++){
        if ((*i)->getName()==selectedProcess->text()){

            displayListLayout->removeWidget(segmentsListWidget);
            displayListLayout->removeWidget(processesListWidget);
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
    for (std::list <Hole *>::iterator i=holes.begin() ;i!=holes.end();i++){
        if(selectedHole->text()==(*i)->getName()){
            currentHole=(*i);
            break;
        }
    }
}

void EntryUI::segmentSelected(QListWidgetItem *selectedSegment)
{
    for (std::list<Segment *>::iterator i=currentProcess->getSegmentsList().begin(); i!=currentProcess->getSegmentsList().end();i++){
        if(selectedSegment->text()==(*i)->getName()){
            currentSegment=(*i);
        }
    }
}

void EntryUI::popSegment()
{
    qDebug()<<"popping Segment";
    if(currentSegment==nullptr || currentProcess==nullptr)
        return ;
    qDebug()<<"passed to popping";
    for (std::list<Segment *>::iterator i=currentProcess->getSegmentsList().begin();i!=currentProcess->getSegmentsList().end();i++){
        if (currentSegment==(*i)){
            for (int j=0;j<holesListWidget->count();j++){
                if(segmentsListWidget->item(j)->text()==currentSegment->getName()){
                    segmentsListWidget->setItemHidden(segmentsListWidget->item(j),true);
                    segmentsListWidget->removeItemWidget(segmentsListWidget->item(j));
                    break;
                }
            }
            currentSegment->deallocate();
            if (memoryAllocator!=nullptr)
                memoryAllocator->joinHoles();
            delete (*i);
            currentProcess->getSegmentsList().erase(i);
            currentSegment=nullptr;
            break;
        }
    }
}


void EntryUI::popHole()
{
    qDebug()<<"popping hole";
    if(currentHole==nullptr)
        return ;
    qDebug()<<"passed to popping";
    for (std::list<Hole *>::iterator i=holes.begin();i!=holes.end();i++){
        if(currentHole==(*i)){
            for (int j=0;j<holesListWidget->count();j++){
                if(holesListWidget->item(j)->text()==currentHole->getName()){
                    holesListWidget->setItemHidden(holesListWidget->item(j),true);
                    holesListWidget->removeItemWidget(holesListWidget->item(j));
                    break;
                }
            }

            delete (*i);
            holes.erase(i);
            currentHole=nullptr;
            break;
        }
    }
}

void EntryUI::popProcess()
{
    if(currentProcess==nullptr)
        return ;
    for (std::list <Process *>::iterator j=processes.begin(); j!=processes.end();j++){
        if((*j)==currentProcess){
            qDebug()<<"process to be removed :: "<<(*j)->getName();
            segmentsListWidget=currentProcess->getSegmentsListWidget();
            int k=0;
            for (std::list<Segment *>::iterator i=(*j)->getSegmentsList().begin();i!=(*j)->getSegmentsList().end();i++){
                (*i)->deallocate();
                segmentsListWidget->setItemHidden(segmentsListWidget->item(k),true);
                segmentsListWidget->removeItemWidget(segmentsListWidget->item(j));
                delete (*i);
                k++;
            }
            for (int i=0;i<processesListWidget->count();i++){
                if(processesListWidget->item(i)->text()==currentProcess->getName()){
                    qDebug()<<"process label to be removed from list is "<<processesListWidget->item(i)->text();
                    processesListWidget->setItemHidden(processesListWidget->item(i),true);
                    processesListWidget->removeItemWidget(processesListWidget->item(i));
                    break;
                }
            }

            (*j)->getSegmentsList().clear();
            delete (*j);
            processes.erase(j);

            break;
        }
    }

    if (memoryAllocator!=nullptr)
        memoryAllocator->joinHoles();
}

void EntryUI::createItems()
{
    startButton=new QPushButton("Start Allocation");

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

    memoryDisplayGroup->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);
    processesListWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
}



void EntryUI::setLabelTexts()
{
    fittingMethod->addItem("First Fit");
    fittingMethod->addItem("Best Fit");
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
}
