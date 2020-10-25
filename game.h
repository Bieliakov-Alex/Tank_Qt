#ifndef GAME_H
#define GAME_H

#include <memory>

#include <QObject>
#include <QTimer>

#include "tank.h"

class Game : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint16 width READ Width CONSTANT)
    Q_PROPERTY(quint16 height READ Height CONSTANT)
public:
    explicit Game(std::shared_ptr<Tank> player, quint16 width = 640, quint16 height = 480, QObject *parent = nullptr);

    quint16 Width() const;
    quint16 Height() const;

    QVariant EnemyList();

signals:

public slots:
    void MoveNorthSlot();
    void MoveEastSlot();
    void MoveSouthSlot();
    void MoveWestSlot();
    void MoveEnemySlot();

private:
    const quint16 kWidth;
    const quint16 kHeight;

    bool TankCollisions(quint16 x_pos, quint16 y_pos, const Tank* current_tank);
    void MoveEnemySouth(Tank* enemy_tank);
    void MoveEnemyNorth(Tank* enemy_tank);
    void MoveEnemyWest(Tank* enemy_tank);
    void MoveEnemyEast(Tank* enemy_tank);

    std::shared_ptr<Tank> player_;

    QList<QObject *> enemy_list_;

    std::unique_ptr<QTimer> game_timer_;
};

#endif // GAME_H
