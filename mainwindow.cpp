#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(_Scene);
    _Scene->setSceneRect(0, 0, 494, 494);
}

void MainWindow::SetVerticesAroundCircle() {
    for (auto& vertex : _ArrVertex) {
        delete vertex;
    }
    _ArrVertex.clear();
    _Scene->clear();

    if (_NumVertex <= 0) {
        return;
    }
    float angelStep = 360.0 / _NumVertex;


    for (float angel = 0; angel < 360.0; angel += angelStep) {
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

        float x = xZ * _Radius * qSin(qDegreesToRadians(cur_angel)) + 247;
        float y = yZ * _Radius * qCos(qDegreesToRadians(cur_angel)) + 247;
        // qDebug() << angel << " " << cur_angel << " |" <<  x << "  " << y << " = " << (x*x + y*y);
        auto* vertex = new TVertex();
        vertex->setPos(x, y);
        _ArrVertex.push_back(vertex);
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


void MainWindow::on_pushButtonAddEdge_clicked()
{
    int rand1 = rand() % _ArrVertex.size();
    int rand2 = rand() % _ArrVertex.size();
    while (rand1 == rand2) {
        rand2 = rand() % _ArrVertex.size();
    }

    const QPointF& pointFirst = _ArrVertex[rand1]->pos();
    const QPointF& pointSecond = _ArrVertex[rand2]->pos();
    qDebug() << pointFirst.x() << " " << pointFirst.y() << " | " << pointSecond.x() << " " << pointSecond.y();

    TEdge* edge = new TEdge(_ArrVertex[rand1], _ArrVertex[rand2]);
    _Scene->addItem(edge);
}

