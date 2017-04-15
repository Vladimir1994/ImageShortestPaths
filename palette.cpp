#include "palette.h"

Palette::Palette()
    : colorPalette_({Qt::red, Qt::blue, Qt::green,
                     Qt::yellow, Qt::black, Qt::darkMagenta, Qt::darkCyan})
{}

Palette & Palette::instance()
{
    static Palette instance;
    return instance;
}

QColor Palette::getColor(int idx)
{
    return colorPalette_[idx];
}

std::size_t Palette::size()
{
    return colorPalette_.size();
}
