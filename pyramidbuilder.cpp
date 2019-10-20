#include "pyramidbuilder.h"

PyramidBuilder::PyramidBuilder(QWidget *parent) : QMainWindow(parent)
{

}

QVector<QVector<int>> PyramidBuilder::BuildPyramid(QPixmap imageInfo, const double ratio)
{
    int widthImage = imageInfo.width();
    int heightImage = imageInfo.height();

    int countLayer = qFloor(CalculateLog(ratio, qMin(widthImage, heightImage)) + 1.);

    QVector<QVector<int>> pyramid;
    for(int i = 0;i < countLayer;i++)
    {
        pyramid.push_back({widthImage, heightImage});
        widthImage /= ratio;
        heightImage /= ratio;
    }
    return pyramid;
}

double PyramidBuilder::CalculateLog(double a, double b)
{
    return qLn(b) / qLn(a);
}
