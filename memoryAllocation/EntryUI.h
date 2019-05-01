#ifndef ENTRYUI_H
#define ENTRYUI_H
#include <QDebug>

#include <QObject>
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

class EntryUI: public QWidget
{
    Q_OBJECT
public:
    EntryUI();
private slots:
    void addHole();
    void addProcess();
    void addSegment();
    void buttonClicked(ControlButtons * sourceButton);
    void startAllocation();
    void processSelected(QListWidgetItem* selectedProcess);
    void holeSelected(QListWidgetItem* selectedHole);
    void segmentSelected(QListWidgetItem* selectedSegment);
    void popSegment();
    void popHole();
    void popProcess();
private:
    void createItems();
    void setLabelTexts();
    void setInitialDisplay();
    void createLayouts();
    void signalsHandler();

    Allocator * memoryAllocator;
    QPushButton * startButton;
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
    std::list <Process *> processes;
    std::list <Hole *> holes;
    Process * currentProcess;
    Process * newProcess;
    Hole * currentHole;
    Hole * newHole;
    Segment * currentSegment;
    int processID;
    int enteredSegments;
    int holeID;

};

#endif // GUI_H
