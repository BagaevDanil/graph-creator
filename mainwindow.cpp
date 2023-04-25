#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

const int MainWindow::SCREEN_WIDTH = 600;
const int MainWindow::SCREEN_HEIGHT = 600;
const int MainWindow::ABSENCE_BORDER_SCREEN = 30;
const float MainWindow::RADIUS = fmin(SCREEN_HEIGHT, SCREEN_WIDTH)/2  - ABSENCE_BORDER_SCREEN;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _Graph(nullptr)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(_Scene);
    _Scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddRandomGraph_clicked()
{
    if (_Graph != nullptr) {
        delete _Graph;
        _Graph = nullptr;
    }

    bool okInpusVertex, okInpusEdges;
    int numVertex = ui->lineEditNumVertex->text().toInt(&okInpusVertex);
    int numEdge = ui->lineEditNumEdge->text().toInt(&okInpusEdges);
    if (!okInpusVertex || !okInpusEdges) {
        QMessageBox::warning(this, "Ошибка", "Некорректные введенные данные!");
        return;
    }
    if (numVertex < 0 || numEdge < 0 || numEdge > numVertex*(numVertex-1)) {
        QMessageBox::warning(this, "Ошибка", "Некорректный диапазон введенных данных!");
        return;
    }
    _Graph = new TGraph(numVertex, numEdge);
    _Graph->ArrangeCircle(RADIUS, SCREEN_WIDTH, SCREEN_HEIGHT);
    _Graph->AddToScene(_Scene);
}


void MainWindow::on_pushButtonArrangeCircle_clicked()
{
    if (_Graph == nullptr) {
        QMessageBox::warning(this, "Ошибка", "Грaф не создан!");
        return;
    }
    _Graph->ArrangeCircle(RADIUS, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void MainWindow::on_pushButtonClearWorkArea_pressed()
{
    if (_Graph == nullptr) {
        QMessageBox::warning(this, "Ошибка", "Рабочая область пуста!");
        return;
    }
    delete _Graph;
    _Graph = nullptr;
}

