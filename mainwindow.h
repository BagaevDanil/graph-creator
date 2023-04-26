#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QGraphicsItem>
#include "vertex.h"
#include "edge.h"
#include <QtMath>
#include <vector>
#include <QString>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const float RADIUS;
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const int ABSENCE_BORDER_SCREEN;

private:
    TGraph* _Graph;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAddRandomGraph_clicked();
    void on_pushButtonArrangeCircle_clicked();
    void on_pushButtonClearWorkArea_pressed();

    void on_pushButtonClearWorkArea_2_clicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* _Scene;
};
#endif // MAINWINDOW_H
