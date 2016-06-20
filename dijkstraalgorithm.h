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

    PathsHolder computeShortestPaths(const QImage &image, const QPoint &startPoint);

private:
    QHash<int, double> distances_;
    QHash<int, int> previous_;
    std::vector<int> notVisited_;
    size_t imWidth_;
    size_t imHeight_;

private:
    QPoint minInRow(size_t row) const;
    QPoint minInColumn(size_t col) const;
    size_t pointToIndex(const QPoint &p) const;
    QPoint indexToPoint(size_t index)  const;
    bool imageContainsIndex(const QPoint &p) const;
    std::vector<int> getNeighbours(int index);
    void restorePath(QVector<QPoint> &path, const QPoint &startPoint,
                     const QPoint &finishPoint) const;
};

#endif // DIJKSTRAALGORITHM_H
