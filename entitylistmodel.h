/* Класс созданный для отображения списка сущностей в qml*/

#ifndef ENTITYLISTMODEL_H
#define ENTITYLISTMODEL_H

#include <QAbstractListModel>

#include "entitylist.h"

class EntityListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(EntityList* entity_list READ List WRITE SetList)

public:
    explicit EntityListModel(QObject *parent = nullptr);

    enum {
        XPosRole = Qt::UserRole,
        YPosRole,
        SizeRole,
        DirectionRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    EntityList* List();
    void SetList(EntityList* list);

private:
    EntityList* entity_list_;
};

#endif // ENTITYLISTMODEL_H
