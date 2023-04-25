#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this); //ToDo: TTest -> TScene

    ui->graphicsView->setScene(_Scene);
    _Scene->setSceneRect(-247, -247, 494, 494);
}

void MainWindow::SetVerticesAroundCircle() {
    _Scene->clear();
    if (_NumVertex <= 0) {
        return;
    }
    float angelStep = 360.0 / _NumVertex;


    for (float angel = 0; angel < 360; angel += angelStep) {
        float cur_angel = angel;
        int quarter = 0;
        while (cur_angel >= 90) {
            cur_angel -= 90;
            quarter++;
        }

        int xZ = 1, yZ = 1;
        if (quarter == 0) {
            xZ *= -1;
        }
        if (quarter == 1) {
            yZ *= -1;
            xZ *= -1;
            cur_angel = 90 - cur_angel;
        }
        if (quarter == 2) {
            yZ *= -1;
        }
        if (quarter == 3) {
            cur_angel = 90 - cur_angel;
        }

        float x = xZ * _Radius * qSin(qDegreesToRadians(cur_angel));
        float y = yZ * _Radius * qCos(qDegreesToRadians(cur_angel));
        // qDebug() << angel << " " << cur_angel << " |" <<  x << "  " << y << " = " << (x*x + y*y);
        // _Scene->addEllipse(QRect(x, y, 20, 20));
        auto* vertex = new TVertex();
        vertex->setPos(x, y);
        _Scene->addItem(vertex);
    }
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

