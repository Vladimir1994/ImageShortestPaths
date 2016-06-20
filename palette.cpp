#include "palette.h"

Palette::Palette()
{
    colorPalette_.append(Qt::red);
    colorPalette_.append(Qt::blue);
    colorPalette_.append(Qt::green);
    colorPalette_.append(Qt::yellow);
    colorPalette_.append(Qt::black);
    colorPalette_.append(Qt::darkMagenta);
    colorPalette_.append(Qt::darkCyan);
}

Palette & Palette::instance()
{
    static Palette instance;
    return instance;
}

QColor Palette::getColor(int idx)
{
    return colorPalette_[idx];
}

size_t Palette::size()
{
    return colorPalette_.size();
}
