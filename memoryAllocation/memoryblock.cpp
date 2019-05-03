#include "memoryblock.h"
#define memoryX 10
#define widthOfBlock 200

MemoryBlock::MemoryBlock(QGraphicsItem * parent,Hole * hole)
{
    this->setParentItem(parent);
    this->setRect(memoryX,10,widthOfBlock,80);
    addressLabel=new QGraphicsSimpleTextItem(this);
    blockName=new QGraphicsSimpleTextItem(hole->getName(),this);
    currentState=0;
    setSize(hole->getSize());
    setStartAddress(hole->getStartAddress());
    positionLabels();
    this->setBrush(Qt::green);
    qDebug()<<"memory bolck 0";
}

MemoryBlock::MemoryBlock(QGraphicsItem * parent,Segment * allocatedSegment){

    if (allocatedSegment->getResidingAddress()<0){
        qDebug()<<"memory block allocated wrongly to an unallocated segment";
    //        delete this;
        return;
    }
    this->setParentItem(parent);
    this->setRect(memoryX,10,widthOfBlock,80);
    addressLabel=new QGraphicsSimpleTextItem(QString::number(allocatedSegment->getResidingAddress()),this);
    blockName=new QGraphicsSimpleTextItem(allocatedSegment->getName(),this);
    currentState=1;
    setSize(allocatedSegment->getSize());
    setStartAddress(allocatedSegment->getResidingAddress());
    positionLabels();
    this->setBrush(Qt::red);
    qDebug()<<"memory bolck 1";
}

MemoryBlock::MemoryBlock(QGraphicsItem *parent, int startAddress , int size)
{
    this->setParentItem(parent);
    this->setRect(memoryX,10,widthOfBlock,80);
    addressLabel=new QGraphicsSimpleTextItem("Address Label",this);
    blockName=new QGraphicsSimpleTextItem("Block Name",this);
    currentState=2;
    setSize(size);
    setStartAddress(startAddress);
    this->setBrush(Qt::gray);
    positionLabels();
//    qDebug()<<this->boundingRect().x()<<this->boundingRect().y()<<this->boundingRect().height();
}

MemoryBlock::~MemoryBlock()
{
    qDebug()<<"deleting memory bolck";
}

void MemoryBlock::setSize(int length){
    this->length=length;
    positionLabels();
}

void MemoryBlock::setStartAddress(int startAddress){
    this->startAddress=startAddress;
    addressLabel->setText(QString::number(startAddress));
    positionLabels();
}

void MemoryBlock::setName(QString name)
{
    blockName->setText(name);
    positionLabels();
}

void MemoryBlock::allocate(Segment *allocatedSegment)
{
    if (allocatedSegment->getResidingAddress()>=0)
        setStartAddress(allocatedSegment->getResidingAddress());
    else {
        qDebug()<<"memory block allocated wrongly to an unallocated segment";
        return;
    }
    setStartAddress(allocatedSegment->getResidingAddress());
    setName(allocatedSegment->getName());
    currentState=1;
    setSize(allocatedSegment->getSize());
    this->setBrush(Qt::red);
}

void MemoryBlock::deallocate(Hole *deallocatedHole)
{
    addressLabel->setText(QString::number(deallocatedHole->getStartAddress()));
    blockName->setText(deallocatedHole->getName());
    currentState=0;
    addressLabel->boundingRect().setRect(this->boundingRect().width()+5,5,60,60);
    blockName->boundingRect().setRect(10,10,60,60);
    setSize(deallocatedHole->getSize());
    setStartAddress(deallocatedHole->getStartAddress());
    this->setBrush(Qt::green);
}

void MemoryBlock::changeAttributes(int state,int length,int startAddress){
    currentState=state;
    this->length=length;
    this->startAddress=startAddress;
    setStartAddress(this->startAddress);
    setSize(this->length);
}

void MemoryBlock::setNewY(int y)
{
    this->setY(y);
    positionLabels();
}

void MemoryBlock::setHeight(int height)
{
    this->setRect(memoryX,ceil(this->boundingRect().y()),widthOfBlock,height);
    positionLabels();
}

int MemoryBlock::getLength(){
    return length;
}

int MemoryBlock::getStartAddress(){
    return startAddress;
}

int MemoryBlock::getState(){
    return currentState;
}

QString MemoryBlock::getName()
{
    return blockName->text();
}

void MemoryBlock::positionLabels()
{
    blockName->setPos(this->boundingRect().left(),this->boundingRect().top()+this->boundingRect().height()/2-blockName->boundingRect().height()/2);
    addressLabel->setPos(this->boundingRect().topRight());
}
