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
    void ChangeRatio();
private:
    Ui::MainWindow *ui;

    QMultiMap <double, QFileInfo> diagFiles;

    void MakeListLayer(int countLayer);
    void SetImageInfo(QPixmap imageMainSize, QPixmap imageNewSize);

    QPixmap GetMainImage();
    QPixmap GenerationLayer(QPixmap image, int numberLayer, double ratio);
};

#endif // MAINWINDOW_H
