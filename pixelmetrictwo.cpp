#include "pixelmetrictwo.h"

#include <QtMath>

double PixelMetricTwo::distance(const QColor &first, const QColor &second)
{
    return qSqrt(qPow(first.red() - second.red(), 2)
            + qPow(first.green() - second.green(), 2)
            + qPow(first.blue() - second.blue(), 2));
}

