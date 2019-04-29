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
#include "process.h"
#include "hole.h"
#include "segment.h"

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

private:
    void createItems();
    void setLabelTexts();
    void setInitialDisplay();
    void createLayouts();
    void signalsHandler();
    void setAssociatedLists();
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
    QList <Process *> processes;
    QList <Hole *> holes;
    Process * currentProcess;
    Process * newProcess;
    Hole * newHole;
    int processID;
    int enteredSegments;
    int holeID;

};

#endif // GUI_H
