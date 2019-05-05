#include "controlbuttons.h"
#include <string>
ControlButtons::ControlButtons(QString text, QGroupBox *holdingBox)
{
    this->setText(text);
    this->holdingBox=holdingBox;
    this->setParent(this->holdingBox);
    this->show();
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(this,SIGNAL(clicked()),this,SLOT(buttonClicked()));
}

void ControlButtons::setGroupBox(QGroupBox * holdingBox)
{
    this->holdingBox=holdingBox;

}

void ControlButtons::addQLineEdit(QLineEdit *newQLineEdit)
{
    lineEdits.push_back(newQLineEdit);
}

void ControlButtons::setAssociatedList(QListWidget * associatedListWidget, std::list<int> *associatedList)
{
    this->associatedListWidget=associatedListWidget;
}

void ControlButtons::buttonClicked()
{
//    qDebug()<<this->text();
//        qDebug()<<lineEdits.size();
        for (std::list <QLineEdit *>::iterator i=lineEdits.begin() ;i!=lineEdits.end();i++){
            if ((*i)->text()==""){
//                qDebug()<<"empty text";
                return;
            }
        }
        if(this->text()=="Add"){
            emit clickedSignal(this);
        }
        else if (this->text()=="Pop"){
            emit clickedSignal(this);
        }
        else if (this->text()=="Cancel"){
            emit clickedSignal(this);
        }

}
