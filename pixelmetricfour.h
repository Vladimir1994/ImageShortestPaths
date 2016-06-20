#ifndef PIXELMETRICFOUR_H
#define PIXELMETRICFOUR_H

#include "pixelmetric.h"

class PixelMetricFour : public PixelMetric
{
public:
    double distance(const QColor &first, const QColor &second) override;
};

#endif // PIXELMETRICFOUR_H
