#ifndef PIXELMETRICTHREE_H
#define PIXELMETRICTHREE_H

#include "pixelmetric.h"

class PixelMetricThree : public PixelMetric
{
public:
    double distance(const QColor &first, const QColor &second) override;
};

#endif // PIXELMETRICTHREE_H
