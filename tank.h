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
    Q_PROPERTY(enum Direction direction READ Direction NOTIFY DirectionChanged)

public:
    Tank(quint16 x_pos, quint16 y_pos, enum Direction direction = Direction::kNorth, quint8 speed = 10, quint8 size = 50, QObject *parent = nullptr);

    quint16 XPos() const;
    quint16 YPos() const;
    quint8 Speed() const;
    quint8 Size() const;
    enum Direction Direction() const;

signals:
    void XPosChanged();
    void YPosChanged();
    void DirectionChanged();

private:
    const quint8 kSize_;
    const quint8 kSpeed_;

    quint16 x_pos_;
    quint16 y_pos_;

    enum Direction direction_;
};

#endif // TANK_H
