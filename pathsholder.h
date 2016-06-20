#ifndef PATHSHOLDER_H
#define PATHSHOLDER_H

#include <QVector>
#include <QPoint>

class PathsHolder
{
public:
    PathsHolder();

    QVector<QPoint> & pathToTop();
    QVector<QPoint> & pathToBottom();
    QVector<QPoint> & pathToLeft();
    QVector<QPoint> & pathToRight();

private:
    QVector<QPoint> pathToTop_;
    QVector<QPoint> pathToBottom_;
    QVector<QPoint> pathToLeft_;
    QVector<QPoint> pathToRight_;
};

#endif // PATHSHOLDER_H
