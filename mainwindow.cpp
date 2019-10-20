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
    connect(ui->comboBoxLayer, SIGNAL(activated(int)), this, SLOT(SelectLayer(int)));
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

    imageInfoMain = filePath;
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString fileFormat = fileInfo.completeSuffix();

    const int pixWidth = imageInfoMain.width();
    const int pixHeight = imageInfoMain.height();

    if (fileFormat == "png" || fileFormat == "jpg")
    {
        if (pixWidth >= 1 && pixHeight >= 1)
        {
            SetImageInfo(imageInfoMain, imageInfoMain);
            pyramid = build.BuildPyramid(imageInfoMain, ratio);

            MakeListLayer(pyramid);
        }
        else QMessageBox::warning(this, "Warning!", "Perhaps the file format is not supported, please, choose another file");
    }
    else QMessageBox::critical(this, "Attention!", "Invalid file format");
}

void MainWindow::SetImageInfo(QPixmap imageMainSize, QPixmap imageNewSize)
{
    ui->labelImage->setPixmap(imageMainSize);
    ui->scrollAreaImage->setWidget(ui->labelImage);
    ui->labelImageSize->setText("Size: " + QString::number(imageNewSize.width()) + "x" + QString::number(imageNewSize.height()));
}

void MainWindow::MakeListLayer(QVector<QVector<int>> pyramid)
{
    ui->comboBoxLayer->clear();
    for(int i = 0;i < pyramid.size(); i++)
    {
        ui->comboBoxLayer->addItem(QString::number(i));
    }
}

void MainWindow::SelectLayer(int index)
{
    QPixmap imageMain = imageInfoMain;
    QPixmap imageScaled = imageMain.scaled(pyramid[index][0], pyramid[index][1]);
    SetImageInfo(imageScaled.scaled(imageMain.width(), imageMain.height()), imageScaled);
}
