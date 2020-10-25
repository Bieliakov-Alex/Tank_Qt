#ifndef TANK_H
#define TANK_H

#include <QObject>

#include "direction.h"

class Tank : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint16 x_pos READ XPos NOTIFY XPosChanged)
    Q_PROPERTY(quint16 y_pos READ YPos NOTIFY YPosChanged)
    Q_PROPERTY(quint8 tank_size READ Size CONSTANT)
    Q_PROPERTY(Direction::Enum direction READ Direction NOTIFY DirectionChanged)

public:
    Tank(quint16 x_pos = 0, quint16 y_pos = 0, Direction::Enum direction = Direction::Enum::kNorth, quint8 speed = 5, quint8 size = 50, QObject *parent = nullptr);
    Tank(const Tank& tank);
    ~Tank() = default;

    quint16 XPos() const;
    quint16 YPos() const;
    quint8 Speed() const;
    quint8 Size() const;
    Direction::Enum Direction() const;

    void MoveNorth();
    void MoveEast();
    void MoveSouth();
    void MoveWest();

signals:
    void XPosChanged();
    void YPosChanged();
    void DirectionChanged();

private:
    const quint8 kSize;
    const quint8 kSpeed;

    quint16 x_pos_;
    quint16 y_pos_;

    Direction::Enum direction_;
};
Q_DECLARE_METATYPE(Tank)

#endif // TANK_H
