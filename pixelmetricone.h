#ifndef PIXELMETRICONE_H
#define PIXELMETRICONE_H

#include "pixelmetric.h"

class PixelMetricOne : public PixelMetric
{
public:
    double distance(const QColor &first, const QColor &second) override;
};

#endif // PIXELMETRICONE_H
