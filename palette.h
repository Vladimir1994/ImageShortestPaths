#ifndef PALETTE_H
#define PALETTE_H

#include <QVector>
#include <QColor>

#include <cstdlib>

class Palette
{
public:
    static Palette & instance();

    QColor getColor(int idx);
    std::size_t size();

    Palette(const Palette &) = delete;
    Palette & operator=(const Palette &) = delete;

private:
    QVector<QColor> colorPalette_;

private:
    Palette();
};

#endif // PALETTE_H
