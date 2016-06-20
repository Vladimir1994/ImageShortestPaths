#include "pixelmetricthree.h"

double PixelMetricThree::distance(const QColor &, const QColor &second)
{
    return second.red() + second.green() + second.blue();
}

