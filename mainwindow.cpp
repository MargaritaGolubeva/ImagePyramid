#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    QAction *open = file->addAction(tr("&Open"));

    QDoubleValidator validator(1.1, 10000.0, 1);
    validator.setLocale(QLocale::English);
    ui->lineEditRatio->setValidator(&validator);

    connect(open, SIGNAL(triggered()), this, SLOT(LoadImage()));
    connect(ui->comboBoxLayer, SIGNAL(activated(int)), this, SLOT(SelectLayer(int)));
    connect(ui->comboBoxFile, SIGNAL(activated(int)), this, SLOT(SelectFile(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadImage()
{
    ui->labelRatio->setText("2");

    PyramidBuilder build;

    const QString filePath = QFileDialog::getOpenFileName(this, "Open Dialog", "", "*.png *.jpg");
    if (filePath.isEmpty())
        return;

    QPixmap imageInfoMain(filePath);
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString fileFormat = fileInfo.completeSuffix();

    const int pixWidth = imageInfoMain.width();
    const int pixHeight = imageInfoMain.height();
    const double ratio = 2.;

    if (fileFormat == "png" || fileFormat == "jpg")
    {
        if (pixWidth >= 1 && pixHeight >= 1)
        {
            diagFiles.insert((pixWidth * pixHeight) / 2., fileInfo);

            ui->comboBoxFile->clear();
            for(const auto &fileInfo : diagFiles)
            {
                ui->comboBoxFile->addItem(fileInfo.fileName());
            }

            const int countLayer = build.CountLayer(imageInfoMain, ratio);

            MakeListLayer(countLayer);
            SetImageInfo(imageInfoMain, imageInfoMain);

            connect(ui->lineEditRatio, SIGNAL(returnPressed()), this, SLOT(ChangeRatio()));
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

void MainWindow::MakeListLayer(int countLayer)
{
    ui->comboBoxLayer->clear();
    for(int i = 0;i < countLayer; i++)
    {
        ui->comboBoxLayer->addItem(QString::number(i));
    }
}

void MainWindow::SelectLayer(int index)
{
    const double ratio = ui->labelRatio->text().toDouble();

    PyramidBuilder build;
    QPixmap imageInfoMain = GetMainImage();
    QPixmap imageScaled = build.GenerationLayer(imageInfoMain, index, ratio);
    SetImageInfo(imageScaled.scaled(imageInfoMain.width(), imageInfoMain.height()), imageScaled);
}

void MainWindow::SelectFile(int index)
{
   PyramidBuilder build;

   QMultiMap <double, QFileInfo>::const_iterator it = diagFiles.begin() + index;
   QPixmap imageInfoMain(it.value().filePath());

   const double ratio = ui->labelRatio->text().toDouble();
   const int countLayer = build.CountLayer(imageInfoMain, ratio);

   SetImageInfo(imageInfoMain, imageInfoMain);
   MakeListLayer(countLayer);
}

QPixmap MainWindow::GetMainImage()
{
    int indexFile = ui->comboBoxFile->currentIndex();
    QMultiMap <double, QFileInfo>::const_iterator it = diagFiles.begin() + indexFile;
    QPixmap imageInfo(it.value().filePath());
    return imageInfo;
}

void MainWindow::ChangeRatio()
{
   PyramidBuilder build;
   QPixmap imageInfoMain = GetMainImage();
   const double ratio = ui->lineEditRatio->text().toDouble();
   const int countLayer = build.CountLayer(imageInfoMain, ratio);

   ui->labelRatio->setText((ui->lineEditRatio->text()).replace(",","."));

   MakeListLayer(countLayer);
}

