#include "tank.h"


Tank::Tank(quint16 x_pos, quint16 y_pos, enum Direction direction, quint8 speed, quint8 size, QObject *parent):
    QObject{parent},
    kSize_{size},
    kSpeed_{speed},
    x_pos_{x_pos},
    y_pos_{y_pos},
    direction_{direction}
{}

quint16 Tank::XPos() const
{
    return x_pos_;
}

quint16 Tank::YPos() const
{
    return y_pos_;
}

quint8 Tank::Speed() const
{
    return kSpeed_;
}

quint8 Tank::Size() const
{
    return kSize_;
}

enum Direction Tank::Direction() const
{
    return direction_;
}

