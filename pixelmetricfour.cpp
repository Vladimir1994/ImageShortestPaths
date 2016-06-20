#include "pixelmetricfour.h"

double PixelMetricFour::distance(const QColor &first, const QColor &second)
{
    return first.red() * second.red()
            + first.green() * second.green()
            + first.blue() * second.blue();
}

