#ifndef PYRAMIDBUILDER_H
#define PYRAMIDBUILDER_H

#include <QMainWindow>
#include <QtMath>

class PyramidBuilder : public QMainWindow
{
    Q_OBJECT
public:
    explicit PyramidBuilder(QWidget *parent = nullptr);

    QVector<QVector<int>> BuildPyramid(QPixmap imageInfo, const double ratio);
private:
    double CalculateLog(double a, double b);
signals:

public slots:
};

#endif // PYRAMIDBUILDER_H
