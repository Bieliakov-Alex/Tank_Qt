#include "entitylist.h"

EntityList::EntityList(QObject *parent) : QObject(parent)
{
    entity_list_.append(Tank(80, 80));
}

QVector<Tank> EntityList::items()
{
    return entity_list_;
}

void EntityList::AddEntity(const Tank& entity)
{
    emit preAddEntity();

    entity_list_.append(Tank(entity));

    emit postAddEntity();
}

void EntityList::RemoveEntity(int index)
{
    emit preRemoveEntity(index);

    entity_list_.removeAt(index);

    emit postRemoveEntity();
}
