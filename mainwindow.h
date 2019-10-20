#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QMap>

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
    void SelectFile(int index);
private:
    Ui::MainWindow *ui;

    QVector<QVector<int>> pyramid;
    QMultiMap <double, QFileInfo> diagFiles;

    const double ratio = 2.;

    void SetImageInfo(QPixmap imageMainSize, QPixmap imageNewSize);
    void MakeListLayer(QVector<QVector<int>> pyramid);
};

#endif // MAINWINDOW_H
