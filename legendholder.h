#ifndef LEGENDHOLDER_H
#define LEGENDHOLDER_H

#include <QColor>

#include <cstdlib>

class LegendHolder
{
public:
    LegendHolder();

    void changeColor();
    QColor color();

    bool enabled() const;
    void setEnabled(bool enabled);

    bool computed() const;
    void setComputed(bool computed);

private:
    size_t colorIndex_;
    bool enabled_;
    bool computed_;
};

#endif // LEGENDHOLDER_H
