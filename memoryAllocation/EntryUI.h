#ifndef ENTRYUI_H
#define ENTRYUI_H
#include <QKeyEvent>
//#include <QObject>
#include <controlbuttons.h>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QListWidget>
#include <QList>
#include "allocator.h"
#include <QInputDialog>

class EntryUI: public QWidget
{
    Q_OBJECT
public:
    EntryUI();
private slots:
    void addHole();
    void addProcess();
    void addSegment();
    std::list <Hole *>::iterator popHole();
    void popProcess();
    void popSegment();
    void buttonClicked(ControlButtons * sourceButton);
    void startAllocation();
    void processSelected(QListWidgetItem* selectedProcess);
    void holeSelected(QListWidgetItem* selectedHole);
    void segmentSelected(QListWidgetItem* selectedSegment);
    void setMemorySize(QString sizeText);
    bool holeAllocated(Hole * allocatedHole);
    void segmentDeallocated(Segment * deallocatedSegment);
    void removeHoleFromListWidget(QString holeName);
    void deallocateProcess(Process * processToDeallocate);
    std::list <Process *> * getProcesses();
    std::list <Hole *> * getHoles();
    void deallocateProcess();
private:
    void createItems();
    void keyPressEvent (QKeyEvent * event);
    void setLabelTexts();
    void setInitialDisplay();
    void createLayouts();
    void signalsHandler();
    void addNewHole(QString holeName,int startingAddress,int size);

    QInputDialog * memorySizeInput;
    QVBoxLayout * memoryLayout;
    int memorySize;
    Allocator * memoryAllocator;
    QPushButton * startButton;
    QPushButton * deallocationButton;
    QGroupBox * memoryDisplayGroup,*holesGroup,*processGroup,*segmentsGroup, *listingGroup;
    QLineEdit ** holesInput , **processInput;     //holesStart & size |||| process name , numSegments , sizeOfSegment , segmenName
    QComboBox * fittingMethod;
    QLabel ** holesInputLabel , ** processInputLabel;    //holesStart & size |||| process name , numSegments , sizeOfSegment , segmenName
    QFormLayout * holesInputLayout, *segsLayout,* processInputLayout,*displayListLayout;
    QVBoxLayout * entryLayout;
    QHBoxLayout * windowLayout;
    QSpacerItem * verSpacer,* horSpacer;
    QListWidget * processesListWidget , * segmentsListWidget,*holesListWidget;
    ControlButtons ** actionButtons;
    std::list <Process *> *processes;
    std::list <Hole *> *holes;
    Process * currentProcess;
    Process * newProcess;
    Hole * currentHole;
    Hole * newHole;
    Segment * currentSegment;
    int processID;
    int enteredSegments;
    int holeID;
    QString allocationMethod;
    QMessageBox * messageUser;

};

#endif // GUI_H
