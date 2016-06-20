#include "shortestpathsalgorithm.h"

ShortestPathsAlgorithm::ShortestPathsAlgorithm(QSharedPointer<PixelMetric> metric) :
    metric_(metric)
{}

void ShortestPathsAlgorithm::setMetric(QSharedPointer<PixelMetric> metric)
{
    metric_= metric;
}

QSharedPointer<PixelMetric> ShortestPathsAlgorithm::metric() const
{
    return metric_;
}
