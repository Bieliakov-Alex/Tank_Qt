/* Данный класс хранит список сущностей на карте (вражеские танки, пули и т.д.)*/

#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <QObject>
#include <QVector>

#include "tank.h"

class EntityList : public QObject
{
    Q_OBJECT
public:
    explicit EntityList(QObject *parent = nullptr);

    QVector<Tank> items();

signals:
    void preAddEntity();
    void postAddEntity();

    void preRemoveEntity(int index);
    void postRemoveEntity();

public slots:
    void AddEntity(const Tank& entity);
    void RemoveEntity(int index);

private:
    QVector<Tank> entity_list_;

};

#endif // ENTITYLIST_H
