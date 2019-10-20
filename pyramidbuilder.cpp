#include "pyramidbuilder.h"

PyramidBuilder::PyramidBuilder(QWidget *parent) : QMainWindow(parent)
{

}

double PyramidBuilder::CalculateLog(double a, double b)
{
    return qLn(b) / qLn(a);
}

int PyramidBuilder::CountLayer(QPixmap imageInfo, const double ratio)
{
    const int widthImage = imageInfo.width();
    const int heightImage = imageInfo.height();

    return qFloor(CalculateLog(ratio, qMin(widthImage, heightImage)) + 1.);
}
