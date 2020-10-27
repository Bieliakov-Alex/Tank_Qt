#include "entitylistmodel.h"

EntityListModel::EntityListModel(QObject *parent)
    : QAbstractListModel(parent), entity_list_{nullptr}
{
}

int EntityListModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return entity_list_->items().size();
}

QVariant EntityListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = entity_list_->items().at(index.row());
    switch(role) {
    case XPosRole:
        return QVariant(item.XPos());
    case YPosRole:
        return QVariant(item.YPos());
    case SizeRole:
        return QVariant(item.Size());
    default:
        break;
    }

    return QVariant();
}

bool EntityListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags EntityListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> EntityListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[XPosRole] = "x_pos";
    names[YPosRole] = "y_pos";
    names[SizeRole] = "entity_size";
    names[DirectionRole] = "direction";
    return names;
}

EntityList* EntityListModel::List()
{
    return entity_list_;
}

void EntityListModel::SetList(EntityList* list)
{
    beginResetModel();

    if(entity_list_) {
        entity_list_->disconnect(this);
    }

    entity_list_ = list;

    if(entity_list_) {
        connect(entity_list_, &EntityList::preAddEntity, this, [=](){
            const int index = list->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(entity_list_, &EntityList::postAddEntity, this, [=](){
            endInsertRows();
        });

        connect(entity_list_, &EntityList::preRemoveEntity, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(entity_list_, &EntityList::postRemoveEntity, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
