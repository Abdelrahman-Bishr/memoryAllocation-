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
    this->show();
    createItems();
    createLayouts();
    setLabelTexts();
    setInitialDisplay();
    signalsHandler();
}

void EntryUI::addHole()
{
    for (int i=0;i<holes.size();i++){
        if ((holesInput[0]->text().toInt() >= holes[i]->getStartAddress() && holesInput[0]->text().toInt() <=  holes[i]->getStartAddress()+ holes[i]->getSize())  ||
                ((holesInput[0]->text().toInt()+holesInput[1]->text().toInt()) >= holes[i]->getStartAddress() &&
                 (holesInput[0]->text().toInt()+holesInput[1]->text().toInt()) <=  holes[i]->getStartAddress()+ holes[i]->getSize()) ){
            qDebug()<<"interlapping holes";
            return;
        }

    }
    qDebug()<<"Adding Hole";
    QString holeName="Hole"+QString::number(holeID);
    newHole=new Hole (holeName,holesInput[0]->text().toInt(),holesInput[1]->text().toInt());
    holes.append(newHole);
    holesListWidget->addItem(holeName+"       "+holesInput[0]->text()+" : "+QString::number( holesInput[0]->text().toInt()+holesInput[1]->text().toInt() ));
    holeID++;
}

void EntryUI::addProcess()
{
    for (int i=0;i<processes.size();i++){
        if(processInput[0]->text()==processes[i]->getName()){
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
        processes.append(newProcess);
        processID++;
        segmentsListWidget=newProcess->getSegmentsListWidget();
        displayListLayout->insertRow(0,processesListWidget,segmentsListWidget);
    }
}
void EntryUI::addSegment()
{
    for (int i=0;i<currentProcess->getNumberOfEnteredSegments();i++){
        if (processInput[2]->text()==currentProcess->getSegmentName(i)){
            qDebug()<<"segment already Enterd";
            return ;
        }
    }
    if(enteredSegments<currentProcess->getNumberOfSegments()){
        qDebug()<<"Adding Segment";
        if(currentProcess!=nullptr){
            enteredSegments++;
            currentProcess->setNewSegment(processInput[2]->text() , processInput[3]->text().toInt());
            currentProcess->addSegment();
        }
    }
}

void EntryUI::buttonClicked(ControlButtons *sourceButton)
{
    if (sourceButton==actionButtons[0])
        addHole();
    else if (sourceButton==actionButtons[3])
        addProcess();
    else if (sourceButton==actionButtons[6])
        addSegment();

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

}

void EntryUI::setAssociatedLists()
{
//    actionButtons[0]->setAssociatedList(holes)
}
