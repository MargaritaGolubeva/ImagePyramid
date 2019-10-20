#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

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
private:
    Ui::MainWindow *ui;

    void SetImageInfo(QPixmap imageMain, QString fileName);
};

#endif // MAINWINDOW_H
