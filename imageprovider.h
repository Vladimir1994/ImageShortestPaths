#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "dijkstraalgorithm.h"
#include "pixelmetric.h"
#include "legendholder.h"
#include "pathsholder.h"

#include <QObject>
#include <QQuickImageProvider>
#include <QString>
#include <QPoint>
#include <QColor>
#include <QSharedPointer>
#include <QVector>

#include <cstdlib>

class ImageProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT
    Q_PROPERTY(bool imageExists READ imageExists NOTIFY imageChanged)
    Q_PROPERTY(bool startPointSelected READ startPointSelected
               NOTIFY startPointChanged)
    Q_PROPERTY(QColor startPointColor READ startPointColor
               NOTIFY startPointColorChanged)
    Q_PROPERTY(QColor pathOneColor READ pathOneColor NOTIFY pathColorChanged)
    Q_PROPERTY(QColor pathTwoColor READ pathTwoColor NOTIFY pathColorChanged)
    Q_PROPERTY(QColor pathThreeColor READ pathThreeColor
               NOTIFY pathColorChanged)
    Q_PROPERTY(QColor pathFourColor READ pathFourColor NOTIFY pathColorChanged)
    Q_PROPERTY(bool algorithmInProcess READ algorithmInProcess
               WRITE setAlgorithmInProcess NOTIFY algorithmInProcessChanged)

public:
    explicit
        ImageProvider(QObject *parent = nullptr,
                      QSharedPointer<ShortestPathsAlgorithm> algorithm
                      = QSharedPointer<ShortestPathsAlgorithm>(new DijkstraAlgorithm));

    QImage requestImage(const QString &id, QSize *size,
                        const QSize &requestedSize) override;

    Q_INVOKABLE void setImage(const QImage &image);
    Q_INVOKABLE bool loadImage(const QString &url);
    Q_INVOKABLE bool saveImage(const QString &url) const;
    Q_INVOKABLE bool imageExists() const;

    Q_INVOKABLE void setStartPoint(const QPoint &startPoint);
    Q_INVOKABLE void setStartPoint(int x, int y);
    Q_INVOKABLE bool startPointSelected() const;
    Q_INVOKABLE void changeStartPointColor();
    Q_INVOKABLE QColor startPointColor() const;

    Q_INVOKABLE void computePaths();

    Q_INVOKABLE void clearResults();

    Q_INVOKABLE void changePathColor(unsigned int pathIndex);
    Q_INVOKABLE QColor pathOneColor();
    Q_INVOKABLE QColor pathTwoColor();
    Q_INVOKABLE QColor pathThreeColor();
    Q_INVOKABLE QColor pathFourColor();

    Q_INVOKABLE void setPathEnabled(unsigned int pathIndex, bool enabled);

    Q_INVOKABLE bool algorithmInProcess() const;
    Q_INVOKABLE void setAlgorithmInProcess(bool algorithmInProcess);

signals:
    void imageChanged();
    void startPointChanged();
    void startPointColorChanged();

    void pathColorChanged();
    void pathEnabledChanged();

    void algorithmInProcessChanged();

private:
    QImage imageOnScreen_;
    QImage originalImage_;

    QPoint startPoint_;
    bool startPointSelected_;
    std::size_t startPointColorIndex_;

    QSharedPointer<ShortestPathsAlgorithm> algorithm_;

    const std::size_t metricsCount_;
    QVector<QSharedPointer<PixelMetric>> metrics_;
    QVector<LegendHolder> legends_;
    QVector<PathsHolder> paths_;

    bool algorithmInProcess_;

private:
    void updateImage();
};

#endif // IMAGEPROVIDER_H
