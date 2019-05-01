#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H
#include <QPushButton>
#include <QGroupBox>
#include <QDebug>
#include <QLineEdit>
#include <QList>
#include <QListWidget>

//namespace control {
//    class ControlButtons;
//}

class ControlButtons : public QPushButton
{
    Q_OBJECT
public:
    ControlButtons(QString text="New PushButton",QGroupBox *holdingBox=NULL);
    void setGroupBox(QGroupBox *holdingBox);
    void addQLineEdit(QLineEdit * newQLineEdit);
    void setAssociatedList(QListWidget * associatedListWidget,std::list <int> * associatedList);

signals:
    void clickedSignal(ControlButtons * sourceButton);
public slots:
    void buttonClicked();
private:
    QGroupBox * holdingBox;
    std::list <QLineEdit*> lineEdits;
    QListWidget * associatedListWidget;
};

#endif // CONTROLBUTTONS_H
