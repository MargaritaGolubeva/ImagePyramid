#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "pyramidbuilder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void LoadImage();
    void SelectLayer(int index);
private:
    Ui::MainWindow *ui;

    QPixmap imageInfoMain;
    QVector<QVector<int>> pyramid;

    void SetImageInfo(QPixmap imageMainSize, QPixmap imageNewSize);
    void MakeListLayer(QVector<QVector<int>> pyramid);
};

#endif // MAINWINDOW_H
