#ifndef DIRECTION_H
#define DIRECTION_H

#include <QObject>
#include <QtGlobal>
class Direction: public QObject{
    Q_OBJECT
public:
    enum class Enum: quint8 {
        kNorth = 0,
        kEast = 1,
        kSouth = 2,
        kWest = 3
    };
    Q_ENUM(Enum);
};



#endif // DIRECTION_H
