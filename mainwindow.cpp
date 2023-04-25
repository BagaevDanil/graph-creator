#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ttest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this); //ToDo: TTest -> TScene

    ui->graphicsView->setScene(_Scene);
    _Scene->setSceneRect(-247, -247, 494, 494);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonMinus_clicked()
{
    _NumVertex--;
    SetVerticesAroundCircle();
}


void MainWindow::on_pushButtonPlus_clicked()
{
    _NumVertex++;
    SetVerticesAroundCircle();
}

