#include "mainwindow.h"
#include "ui_mainwindow.h"

const int SCREEN_WIDTH = 494;
const int SCREEN_HEIGHT = 494;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(_Scene);
    _Scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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

    int ind = 1;
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

        float x = xZ * _Radius * qSin(qDegreesToRadians(cur_angel)) + SCREEN_WIDTH/2;
        float y = yZ * _Radius * qCos(qDegreesToRadians(cur_angel)) + SCREEN_HEIGHT/2;
        // qDebug() << angel << " " << cur_angel << " |" <<  x << "  " << y << " = " << (x*x + y*y);
        auto* vertex = new TVertex(QString::number(ind++));
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
    // qDebug() << pointFirst.x() << " " << pointFirst.y() << " | " << pointSecond.x() << " " << pointSecond.y();

    TEdge* edge = new TEdge(_ArrVertex[rand1], _ArrVertex[rand2]);
    _Scene->addItem(edge);
}

