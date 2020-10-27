#include "game.h"

#include <memory>

#include <QRandomGenerator>
#include <QtMath>
#include <QVariant>

namespace  {

bool WallCollisions(quint16 width, quint16 height, quint16 x_pos, quint16 y_pos, quint8 size) {
    return x_pos + size <= width && y_pos + size <= height;
}

bool EnemyCollisions(const QList<QObject *>& enemy_list_, quint16 x_pos, quint16 y_pos, quint8 size) {
    for(auto enemy: enemy_list_) {
        auto enemy_x_pos = static_cast<Tank*>(enemy)->XPos();
        auto enemy_y_pos = static_cast<Tank*>(enemy)->YPos();
        if(qFabs(enemy_x_pos-x_pos) < size && qFabs(enemy_y_pos-y_pos) < size) {
            return false;
        }
    }
    return true;
}

}

Game::Game(std::shared_ptr<Tank> player, quint16 width, quint16 height, quint8 projectile_size, QObject *parent):
    QObject(parent),
    kWidth{width},
    kHeight{height},
    kProjectileSize{projectile_size},
    player_{player},
    enemy_list_{new Tank(10, 10), new Tank(580, 10), new Tank(10, 420), new Tank(580, 420)},
    game_timer_{std::make_unique<QTimer>(this)}
{
    connect(game_timer_.get(), SIGNAL(timeout()), this, SLOT(MoveEnemySlot()));
    game_timer_->start(1000);
}

quint16 Game::Width() const
{
    return kWidth;
}

quint16 Game::Height() const
{
    return kHeight;
}

QVariant Game::EnemyList()
{
    return QVariant::fromValue(enemy_list_);
}

QVariant Game::ProjectileList()
{
    return QVariant::fromValue(projectile_list_);
}

void Game::MoveNorthSlot()
{
    auto y_pos = player_->YPos() - player_->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, player_->XPos(), y_pos, player_->Size()) && TankCollisions(player_->XPos(), y_pos, player_.get());
    if(collisions) {
        player_->MoveNorth();
    }
}

void Game::MoveEastSlot()
{
    auto x_pos = player_->XPos() + player_->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, x_pos, player_->YPos(), player_->Size()) && TankCollisions(x_pos, player_->YPos(), player_.get());
    if(collisions) {
        player_->MoveEast();
    }
}

void Game::MoveSouthSlot()
{
    auto y_pos = player_->YPos() + player_->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, player_->XPos(), y_pos, player_->Size()) && TankCollisions(player_->XPos(), y_pos, player_.get());
    if(collisions) {
        player_->MoveSouth();
    }
}

void Game::MoveWestSlot()
{
    auto x_pos = player_->XPos() - player_->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, x_pos, player_->YPos(), player_->Size()) && TankCollisions(x_pos, player_->YPos(), player_.get());
    if(collisions) {
        player_->MoveWest();
    }
}

void Game::MoveEnemySlot()
{
    for(auto enemy: enemy_list_) {
        auto direction = QRandomGenerator::global()->bounded(4);
        switch (direction) {
        case 0:
            MoveEnemyNorth(static_cast<Tank*>(enemy));
            break;
        case 1:
            MoveEnemyEast(static_cast<Tank*>(enemy));
            break;
        case 2:
            MoveEnemySouth(static_cast<Tank*>(enemy));
            break;
        case 3:
            MoveEnemyWest(static_cast<Tank*>(enemy));
            break;
        default:
            break;
        }
    }
}

void Game::ShootSlot()
{
    Shoot(*player_);
}

bool Game::TankCollisions(quint16 x_pos, quint16 y_pos, const Tank *current_tank)
{
    if(current_tank == player_.get()) {
        return EnemyCollisions(enemy_list_, x_pos, y_pos, player_->Size());
    }

    auto player_x_pos = player_->XPos();
    auto player_y_pos = player_->YPos();
    if(qFabs(player_x_pos-x_pos) < current_tank->Size() && qFabs(player_y_pos-y_pos) < current_tank->Size()) {
        return false;
    }

    for(auto enemy: enemy_list_){
        if(static_cast<Tank*>(enemy)!=current_tank){
            auto enemy_x_pos = static_cast<Tank*>(enemy)->XPos();
            auto enemy_y_pos = static_cast<Tank*>(enemy)->YPos();
            if(qFabs(enemy_x_pos-x_pos) < current_tank->Size() && qFabs(enemy_y_pos-y_pos) < current_tank->Size()) {
                return false;
            }
        }
    }
    return true;
}

void Game::MoveEnemySouth(Tank *enemy_tank)
{
    auto y_pos = enemy_tank->YPos() + enemy_tank->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, enemy_tank->XPos(), y_pos, enemy_tank->Size()) && TankCollisions(enemy_tank->XPos(), y_pos, enemy_tank);
    if(collisions) {
        enemy_tank->MoveSouth();
    }
}

void Game::MoveEnemyNorth(Tank *enemy_tank)
{
    auto y_pos = enemy_tank->YPos() - enemy_tank->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, player_->XPos(), y_pos, enemy_tank->Size()) && TankCollisions(enemy_tank->XPos(), y_pos, enemy_tank);
    if(collisions) {
        enemy_tank->MoveNorth();
    }
}

void Game::MoveEnemyWest(Tank *enemy_tank)
{
    auto x_pos = enemy_tank->XPos() - enemy_tank->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, x_pos, enemy_tank->YPos(), enemy_tank->Size()) && TankCollisions(x_pos, enemy_tank->YPos(), enemy_tank);
    if(collisions) {
        enemy_tank->MoveWest();
    }
}

void Game::MoveEnemyEast(Tank *enemy_tank)
{
    auto x_pos = enemy_tank->XPos() + enemy_tank->Speed();
    bool collisions = WallCollisions(kWidth, kHeight, x_pos, enemy_tank->YPos(), enemy_tank->Size()) && TankCollisions(x_pos, enemy_tank->YPos(), enemy_tank);
    if(collisions) {
        enemy_tank->MoveEast();
    }
}

void Game::Shoot(const Tank& tank) {
    auto direction = tank.Direction();
    switch(direction) {
    case Direction::Enum::kNorth:
        if(tank.YPos() > kProjectileSize) {
            quint16 x_pos = tank.XPos() + tank.Size() / 2 - kProjectileSize / 2;
            quint16 y_pos = tank.YPos() + kProjectileSize;
            projectile_list_.append(new Tank(x_pos, y_pos, direction, 15, 5));
        }
        break;
    default:
        break;
    }
}

