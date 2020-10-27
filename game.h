/* Класс, который хранит информацию об игре, обрабатывает пользовательский ввод, реализует логику противников*/
//TODO: убрать дублирование кода перемещения игрока и врагов

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
    explicit Game(std::shared_ptr<Tank> player, quint16 width = 640, quint16 height = 480, quint8 projectile_size = 5, QObject *parent = nullptr);

    quint16 Width() const;
    quint16 Height() const;

    QVariant EnemyList();
    QVariant ProjectileList();

signals:

public slots:
    void MoveNorthSlot();
    void MoveEastSlot();
    void MoveSouthSlot();
    void MoveWestSlot();
    void MoveEnemySlot();
    void ShootSlot();

private:
    const quint16 kWidth;
    const quint16 kHeight;
    const quint8 kProjectileSize;

    bool TankCollisions(quint16 x_pos, quint16 y_pos, const Tank* current_tank);
    void MoveEnemySouth(Tank* enemy_tank);
    void MoveEnemyNorth(Tank* enemy_tank);
    void MoveEnemyWest(Tank* enemy_tank);
    void MoveEnemyEast(Tank* enemy_tank);
    void Shoot(const Tank& tank);

    std::shared_ptr<Tank> player_;

    QList<QObject *> enemy_list_;
    QList<QObject *> projectile_list_;

    std::unique_ptr<QTimer> game_timer_;
};

#endif // GAME_H
