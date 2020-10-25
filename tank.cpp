#include "tank.h"

#include <limits>

Tank::Tank(quint16 x_pos, quint16 y_pos, Direction::Enum direction, quint8 speed, quint8 size, QObject *parent):
    QObject{parent},
    kSize{size},
    kSpeed{speed},
    x_pos_{x_pos},
    y_pos_{y_pos},
    direction_{direction}
{}

Tank::Tank(const Tank &tank):
    kSize{tank.Size()},
    kSpeed{tank.Speed()},
    x_pos_{tank.XPos()},
    y_pos_{tank.YPos()},
    direction_{tank.Direction()}
{
}

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
    return kSpeed;
}

quint8 Tank::Size() const
{
    return kSize;
}

Direction::Enum Tank::Direction() const
{
    return direction_;
}

void Tank::MoveNorth()
{
    if(y_pos_ >= kSpeed) {
        y_pos_ -= kSpeed;
        emit YPosChanged();
    }
}

void Tank::MoveEast()
{
    if(x_pos_ <= (std::numeric_limits<qint16>::max() - kSpeed)) {
        x_pos_ += kSpeed;
        emit XPosChanged();
    }
}

void Tank::MoveSouth()
{
    if(y_pos_ <= (std::numeric_limits<qint16>::max() - kSpeed)) {
        y_pos_ += kSpeed;
        emit YPosChanged();
    }
}

void Tank::MoveWest()
{
    if(x_pos_ >= kSpeed) {
        x_pos_ -= kSpeed;
        emit XPosChanged();
    }
}
