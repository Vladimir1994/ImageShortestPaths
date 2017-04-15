#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H

#include "shortestpathsalgorithm.h"

#include <QHash>

#include <vector>

class DijkstraAlgorithm: public ShortestPathsAlgorithm
{
public:
    DijkstraAlgorithm(QSharedPointer<PixelMetric> metric =
                      QSharedPointer<PixelMetric>(new PixelMetricOne));

    PathsHolder computeShortestPaths(const QImage &image,
                                     const QPoint &startPoint);

private:
    QHash<int, double> distances_;
    QHash<int, int> previous_;
    std::size_t imWidth_;
    std::size_t imHeight_;

private:
    QPoint minInRow(std::size_t row) const;
    QPoint minInColumn(std::size_t col) const;
    std::size_t pointToIndex(const QPoint &p) const;
    QPoint indexToPoint(std::size_t index)  const;
    bool imageContainsIndex(const QPoint &p) const;
    std::vector<int> getNeighbours(int index);
    void restorePath(QVector<QPoint> &path, const QPoint &startPoint,
                     const QPoint &finishPoint) const;
};

#endif // DIJKSTRAALGORITHM_H
