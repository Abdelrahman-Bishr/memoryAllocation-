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
    lineEdits.append(newQLineEdit);
}

void ControlButtons::setAssociatedList(QListWidget * associatedListWidget, QList<int> *associatedList)
{
    this->associatedListWidget=associatedListWidget;
}

void ControlButtons::buttonClicked()
{
    qDebug()<<this->text();
    if(!lineEdits.empty()){
        qDebug()<<lineEdits.size();
        for (int i=0;i<lineEdits.size();i++){
            if (lineEdits[i]->text()==""){
                qDebug()<<"empty text";
                return;
            }
        }
        if(this->text()=="Add"){
            emit clickedSignal(this);
        }
        else if (this->text()=="Pop"){

        }
        else if (this->text()=="Cancel"){

        }

    }


}
