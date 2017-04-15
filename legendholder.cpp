#include "legendholder.h"
#include "palette.h"

LegendHolder::LegendHolder()
    : colorIndex_(0)
    , enabled_(false)
    , computed_(false)
{}

void LegendHolder::changeColor()
{
    if (colorIndex_ < Palette::instance().size() - 1)
        colorIndex_++;
    else
        colorIndex_ = 0;
}

QColor LegendHolder::color()
{
    return Palette::instance().getColor(colorIndex_);
}

bool LegendHolder::enabled() const
{
    return enabled_;
}

void LegendHolder::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

bool LegendHolder::computed() const
{
    return computed_;
}

void LegendHolder::setComputed(bool computed)
{
    computed_ = computed;
}

