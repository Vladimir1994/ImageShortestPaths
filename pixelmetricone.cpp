#include "pixelmetricone.h"

#include <QtMath>

double PixelMetricOne::distance(const QColor &first, const QColor &second)
{
    return qFabs(first.red() - second.red())
            + qFabs(first.green() - second.green())
            + qFabs(first.blue() - second.blue());
}
