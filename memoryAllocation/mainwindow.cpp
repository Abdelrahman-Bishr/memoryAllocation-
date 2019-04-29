#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    entry=new EntryUI();
    this->setCentralWidget(entry);
}

MainWindow::~MainWindow()
{
    delete ui;
}
