#ifndef PIXELMETRICTWO_H
#define PIXELMETRICTWO_H

#include "pixelmetric.h"

class PixelMetricTwo : public PixelMetric
{
public:
    double distance(const QColor &first, const QColor &second) override;
};

#endif // PIXELMETRICTWO_H
