#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>

const int MainWindow::SCREEN_WIDTH = 600;
const int MainWindow::SCREEN_HEIGHT = 600;
const int MainWindow::ABSENCE_BORDER_SCREEN = 30;
const float MainWindow::RADIUS = fmin(SCREEN_HEIGHT, SCREEN_WIDTH)/2  - ABSENCE_BORDER_SCREEN;

// using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _Graph(nullptr)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(_Scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
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

QVector<QVector<double>> MainWindow::GetMatrixFromStream(std::ifstream& input) {
    QVector<double> arr;
    while(!input.eof()) {
        std::string str;
        input >> str;

        bool ok;
        arr.push_back(QString::fromStdString(str).toDouble(&ok));

        if (!ok) {
            return {};
        }
    }

    int n = qSqrt(arr.size());
    if (n*n != arr.size()) {
        return {};
    }

    QVector<QVector<double>> matrix;
    for (int i = 0; i < n; i++) {
        QVector<double> row;
        for (int j = 0; j < n; j++) {
            row.push_back(arr[i*n + j]);
        }
        matrix.push_back(row);
    }
    return std::move(matrix);
}

void MainWindow::on_pushButtonClearWorkArea_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                        this,
                        "Open matrix",
                        "C://",
                        "Text file (*.txt)"
                    );
    std::ifstream input;
    input.open(path.toStdString());
    if (!input.is_open()) {
        QMessageBox::warning(this, "Ошибка", "Неверный путь");
        return;
    }
    QVector<QVector<double>> matrix = GetMatrixFromStream(input);
    if (matrix.empty()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный данные в файле");
    }

    for (auto& row : matrix) {
        for (auto& num : row) {
            qDebug() << num;
        }
    }

    if (_Graph != nullptr) {
        delete _Graph;
        _Graph = nullptr;
    }
    _Graph = new TGraph(matrix);
    _Graph->ArrangeCircle(RADIUS, SCREEN_WIDTH, SCREEN_HEIGHT);
    _Graph->AddToScene(_Scene);
}

