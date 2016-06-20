#ifndef PIXELMETRIC
#define PIXELMETRIC

#include <QColor>

class PixelMetric {

public:
    virtual ~PixelMetric() {}
    virtual double distance(const QColor &first, const QColor &second) = 0;
};

#endif // PIXELMETRIC

