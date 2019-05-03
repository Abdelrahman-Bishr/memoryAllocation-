#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    entry=new EntryUI();
    this->setCentralWidget(entry);
    this->setWindowTitle("Memory Allocation Simulator");
//    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
