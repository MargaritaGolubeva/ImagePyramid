#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    QAction *open = file->addAction(tr("&Open"));

    connect(open, SIGNAL(triggered()), this, SLOT(LoadImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadImage()
{
    PyramidBuilder build;

    const QString filePath = QFileDialog::getOpenFileName(this, "Open Dialog", "", "*.png *.jpg");
    if (filePath.isEmpty())
        return;

    const double ratio = 2.;

    QPixmap imageInfo(filePath);
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString fileFormat = fileInfo.completeSuffix();

    const int pixWidth = imageInfo.width();
    const int pixHeight = imageInfo.height();

    if (fileFormat == "png" || fileFormat == "jpg")
    {
        if (pixWidth >= 1 && pixHeight >= 1)
        {
            SetImageInfo(imageInfo, fileName);
            build.BuildPyramid(imageInfo, ratio);
        }
        else QMessageBox::warning(this, "Warning!", "Perhaps the file format is not supported, please, choose another file");
    }
    else QMessageBox::critical(this, "Attention!", "Invalid file format");
}

void MainWindow::SetImageInfo(QPixmap imageInfo, QString fileName)
{
    ui->labelImageName->setText("File name: " + fileName);
    ui->labelImage->setPixmap(imageInfo);
    ui->scrollAreaImage->setWidget(ui->labelImage);
    ui->labelImageSize->setText("Size: " + QString::number(imageInfo.width()) + "x" + QString::number(imageInfo.height()));
}
