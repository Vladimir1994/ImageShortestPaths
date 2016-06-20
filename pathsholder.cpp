#include "pathsholder.h"

PathsHolder::PathsHolder()
{}

QVector<QPoint> & PathsHolder::pathToTop()
{
    return pathToTop_;
}

QVector<QPoint> & PathsHolder::pathToBottom()
{
    return pathToBottom_;
}

QVector<QPoint> & PathsHolder::pathToLeft()
{
    return pathToLeft_;
}

QVector<QPoint> & PathsHolder::pathToRight()
{
    return pathToRight_;
}

