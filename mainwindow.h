#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QGraphicsItem>
#include "vertex.h"
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int _NumVertex = 0;
    float _Radius = 200;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetVerticesAroundCircle();

private slots:
    void on_pushButtonMinus_clicked();

    void on_pushButtonPlus_clicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* _Scene;
};
#endif // MAINWINDOW_H
