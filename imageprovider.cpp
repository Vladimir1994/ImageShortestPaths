#include "imageprovider.h"
#include "palette.h"
#include "pixelmetricone.h"
#include "pixelmetrictwo.h"
#include "pixelmetricthree.h"
#include "pixelmetricfour.h"

#include <QDebug>
#include <QPainter>

ImageProvider::ImageProvider(QObject *parent,
                             QSharedPointer<ShortestPathsAlgorithm> algorithm)
    : QObject(parent)
    , QQuickImageProvider(QQuickImageProvider::Image)
    , startPointSelected_(false)
    , startPointColorIndex_(0)
    , algorithm_(algorithm)
    , metricsCount_(4)
    , metrics_(QVector<QSharedPointer<PixelMetric>>(metricsCount_))
    , legends_(QVector<LegendHolder>(metricsCount_))
    , paths_(QVector<PathsHolder>(metricsCount_))
    , algorithmInProcess_(false)
{
    metrics_[0] = QSharedPointer<PixelMetric>(new PixelMetricOne);
    metrics_[1] = QSharedPointer<PixelMetric>(new PixelMetricTwo);
    metrics_[2] = QSharedPointer<PixelMetric>(new PixelMetricThree);
    metrics_[3] = QSharedPointer<PixelMetric>(new PixelMetricFour);
}

QImage ImageProvider::requestImage(const QString &, QSize *, const QSize &)
{
    if (imageOnScreen_.isNull())
        qDebug() << "No image to output";

    return imageOnScreen_;
}

void ImageProvider::setImage(const QImage &image)
{
    imageOnScreen_ = image;
    clearResults();
    updateImage();
}

bool ImageProvider::loadImage(const QString &url)
{
    QString path = url.mid(8);
    if (!originalImage_.load(path))
        return false;
    clearResults();
    updateImage();
    return true;
}

bool ImageProvider::saveImage(const QString &url) const
{
    QString path = url.mid(8);
    if (!imageOnScreen_.save(path))
        return false;
    return true;
}

bool ImageProvider::imageExists() const
{
    return !imageOnScreen_.isNull();
}

void ImageProvider::setStartPoint(const QPoint &startPoint)
{
    startPoint_ = startPoint;
    startPointSelected_ = true;
    updateImage();
    startPointChanged();
}

void ImageProvider::setStartPoint(int x, int y)
{
    startPoint_.setX(x);
    startPoint_.setY(y);
    startPointSelected_ = true;
    for (auto &legend: legends_) {
        legend.setComputed(false);
    }
    updateImage();
    startPointChanged();
}

bool ImageProvider::startPointSelected() const
{
    return startPointSelected_;
}

void ImageProvider::changeStartPointColor()
{
    if (startPointColorIndex_ < Palette::instance().size() - 1)
        startPointColorIndex_ ++;
    else
        startPointColorIndex_ = 0;
    updateImage();
    startPointColorChanged();
}

QColor ImageProvider::startPointColor() const
{
    return Palette::instance().getColor(startPointColorIndex_);
}

void ImageProvider::computePaths()
{
    for (std::size_t i = 0u; i < metricsCount_; ++i) {
        algorithm_->setMetric(metrics_[i]);
        if (!legends_[i].computed() && legends_[i].enabled()) {
            paths_[i] = algorithm_->computeShortestPaths(originalImage_,
                                                         startPoint_);
            legends_[i].setComputed(true);
        }
    }
    updateImage();
    setAlgorithmInProcess(false);
}

void ImageProvider::clearResults()
{
    startPointSelected_ = false;
    for (auto &path: paths_) {
        path.pathToTop().clear();
        path.pathToBottom().clear();
        path.pathToLeft().clear();
        path.pathToRight().clear();
    }
    for (auto &legend: legends_) {
        legend.setComputed(false);
    }
    updateImage();
    startPointChanged();
}

void ImageProvider::changePathColor(unsigned int pathIndex)
{
    if (pathIndex >= metricsCount_)
        return;

    legends_[pathIndex].changeColor();
    updateImage();
    pathColorChanged();
}

QColor ImageProvider::pathOneColor()
{
    return legends_[0].color();
}

QColor ImageProvider::pathTwoColor()
{
    return legends_[1].color();
}

QColor ImageProvider::pathThreeColor()
{
    return legends_[2].color();
}

QColor ImageProvider::pathFourColor()
{
    return legends_[3].color();
}

void ImageProvider::setPathEnabled(unsigned int pathIndex, bool enabled)
{
    if (pathIndex >= metricsCount_)
        return;

    legends_[pathIndex].setEnabled(enabled);
    updateImage();
}

bool ImageProvider::algorithmInProcess() const
{
    return algorithmInProcess_;
}

void ImageProvider::setAlgorithmInProcess(bool algorithmInProcess)
{
    algorithmInProcess_ = algorithmInProcess;
    algorithmInProcessChanged();
}

void ImageProvider::updateImage()
{
    imageOnScreen_ = originalImage_;

    for (std::size_t i = 0u; i < metricsCount_; ++i) {
        if (legends_[i].computed() && legends_[i].enabled()) {
            QPainter pathsPainter(&imageOnScreen_);
            pathsPainter.setBrush(Qt::NoBrush);
            pathsPainter.setPen(legends_[i].color());
            pathsPainter.drawLines(paths_[i].pathToTop());
            pathsPainter.drawLines(paths_[i].pathToBottom());
            pathsPainter.drawLines(paths_[i].pathToLeft());
            pathsPainter.drawLines(paths_[i].pathToRight());
        }
    }

    if (startPointSelected_) {
        QPainter startPointPainter(&imageOnScreen_);
        startPointPainter.setBrush(Qt::NoBrush);
        startPointPainter.setPen(Palette::instance().
                                 getColor(startPointColorIndex_));
        startPointPainter.drawLine(startPoint_.x() - 5, startPoint_.y(),
                                   startPoint_.x() + 5, startPoint_.y());
        startPointPainter.drawLine(startPoint_.x(), startPoint_.y() - 5,
                                   startPoint_.x(), startPoint_.y() + 5);
        startPointPainter.end();
    }
    imageChanged();
}
