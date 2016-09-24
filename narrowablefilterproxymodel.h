#ifndef NARROWABLEFILTERPROXYMODEL_H
#define NARROWABLEFILTERPROXYMODEL_H

#include "abstractproxychainmodel.h"

class QSortFilterProxyModel;

class NarrowableFilterProxyModel : public AbstractProxyChainModel
{
public:
    NarrowableFilterProxyModel(QObject *parent = 0);
    ~NarrowableFilterProxyModel();

    /// Like QSortFilterProxyModel's function.
    void setFilterFixedString(const QString &s);

private:
    typedef AbstractProxyChainModel::RelationType RelationType;
    RelationType relationTo(QAbstractProxyModel *model, QAbstractProxyModel *sourceModel);
};

#endif // NARROWABLEFILTERPROXYMODEL_H
