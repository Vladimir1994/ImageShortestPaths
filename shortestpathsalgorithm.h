#ifndef SHORTESTPATHSALGORITHM_H
#define SHORTESTPATHSALGORITHM_H

#include "pixelmetric.h"
#include "pixelmetricone.h"
#include "pathsholder.h"

#include <QPoint>
#include <QSharedPointer>
#include <QImage>

class ShortestPathsAlgorithm
{
public:
    ShortestPathsAlgorithm(QSharedPointer<PixelMetric> metric);
    virtual ~ShortestPathsAlgorithm();

    virtual PathsHolder computeShortestPaths(const QImage &image,
                                             const QPoint &startPoint) = 0;

    void setMetric(QSharedPointer<PixelMetric> metric);
    QSharedPointer<PixelMetric> metric() const;

private:
    QSharedPointer<PixelMetric> metric_;
};

#endif // SHORTESTPATHSALGORITHM_H
