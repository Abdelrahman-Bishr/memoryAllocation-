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
//    this->setGeometry(120,90,1200,900);
    this->setWindowState(Qt::WindowState::WindowMaximized);
//    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
