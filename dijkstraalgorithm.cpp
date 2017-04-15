#include "dijkstraalgorithm.h"

#include <limits>
#include <queue>

DijkstraAlgorithm::DijkstraAlgorithm(QSharedPointer<PixelMetric> metric)
    : ShortestPathsAlgorithm(metric)
{}

PathsHolder DijkstraAlgorithm::computeShortestPaths(const QImage &image,
                                                    const QPoint &startPoint)
{
    imWidth_ = image.width();
    imHeight_ = image.height();

    distances_.clear();
    previous_.clear();

    auto comparator = [&] (int left, int right) {
        return distances_[left] > distances_[right];
    };

    std::priority_queue<int, std::vector<int>,
        decltype(comparator)> notVisited_(comparator);

    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            QPoint vertex = QPoint(i, j);
            if (vertex == startPoint)
                distances_[pointToIndex(vertex)] = 0.;
            else
                distances_[pointToIndex(vertex)]
                    = std::numeric_limits<double>::max();
        }
    }

    notVisited_.push(pointToIndex(startPoint));

    while (!notVisited_.empty()) {
        int smallest = notVisited_.top();
        notVisited_.pop();

        std::vector<int> neighbours = getNeighbours(smallest);

        for (auto& neighbour : neighbours) {
            int alt = distances_[smallest]
                + metric()->distance(image.pixel(indexToPoint(smallest)),
                                     image.pixel(indexToPoint(neighbour)));
            if (alt < distances_[neighbour]) {
                distances_[neighbour] = alt;
                previous_[neighbour] = smallest;
                notVisited_.push(neighbour);
            }
        }
    }

    QPoint minPointTop = minInRow(0);
    QPoint minPointBottom = minInRow(image.height() - 1);
    QPoint minPointLeft = minInColumn(0);
    QPoint minPointRight = minInColumn(image.width() - 1);

    PathsHolder paths;
    restorePath(paths.pathToTop(), startPoint, minPointTop);
    restorePath(paths.pathToBottom(), startPoint, minPointBottom);
    restorePath(paths.pathToLeft(), startPoint, minPointLeft);
    restorePath(paths.pathToRight(), startPoint, minPointRight);

    return paths;
}

QPoint DijkstraAlgorithm::minInRow(std::size_t row) const
{
    QPoint minPoint = QPoint(0, row);
    double min = distances_[pointToIndex(minPoint)];
    for (std::size_t i = 0u; i < imWidth_; ++i) {
        QPoint p = QPoint(i, row);
        if (distances_[pointToIndex(p)] < min) {
            minPoint = p;
            min = distances_[pointToIndex(p)];
        }
    }
    return minPoint;
}

QPoint DijkstraAlgorithm::minInColumn(std::size_t col) const
{
    QPoint minPoint = QPoint(col, 0);
    double min = distances_[pointToIndex(minPoint)];
    for (std::size_t i = 0u; i < imHeight_; ++i) {
        QPoint p = QPoint(col, i);
        if (distances_[pointToIndex(p)] < min) {
            minPoint = p;
            min = distances_[pointToIndex(p)];
        }
    }
    return minPoint;
}

std::size_t DijkstraAlgorithm::pointToIndex(const QPoint &p) const
{
    return p.y() * imWidth_ + p.x();
}

QPoint DijkstraAlgorithm::indexToPoint(std::size_t index)  const
{
    QPoint p;
    p.setY(index / imWidth_);
    p.setX(index % imWidth_);
    return p;
}

bool DijkstraAlgorithm::imageContainsIndex(const QPoint &p) const
{
    if (p.x() >= 0
        && static_cast<std::size_t>(p.x()) < imWidth_
        && p.y() >= 0
        && static_cast<std::size_t>(p.y()) < imHeight_)
        return true;
    else
        return false;
}

std::vector<int> DijkstraAlgorithm::getNeighbours(int index)
{
    std::vector<int> neighbours;

    QPoint neighbour = indexToPoint(index);
    neighbour.setX(neighbour.x() - 1);
    if (imageContainsIndex(neighbour))
        neighbours.push_back(pointToIndex(neighbour));

    neighbour = indexToPoint(index);
    neighbour.setX(neighbour.x() + 1);
    if (imageContainsIndex(neighbour))
        neighbours.push_back(pointToIndex(neighbour));

    neighbour = indexToPoint(index);
    neighbour.setY(neighbour.y() - 1);
    if (imageContainsIndex(neighbour))
        neighbours.push_back(pointToIndex(neighbour));

    neighbour = indexToPoint(index);
    neighbour.setY(neighbour.y() + 1);
    if (imageContainsIndex(neighbour))
        neighbours.push_back(pointToIndex(neighbour));

    return neighbours;
}

void DijkstraAlgorithm::restorePath(QVector<QPoint> &path,
                                    const QPoint &startPoint,
                                    const QPoint &finishPoint) const
{
    QPoint point = finishPoint;
    path.append(point);
    while (point != startPoint) {
       QPoint prevPoint = indexToPoint(previous_[pointToIndex(point)]);
       point = prevPoint;
       path.append(point);
    }
}
