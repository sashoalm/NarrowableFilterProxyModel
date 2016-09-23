#ifndef NARROWABLEFILTERPROXYMODEL_H
#define NARROWABLEFILTERPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QStack>

class QSortFilterProxyModel;

class NarrowableFilterProxyModel : public QIdentityProxyModel
{
public:
    NarrowableFilterProxyModel(QObject *parent = 0);
    ~NarrowableFilterProxyModel();

    /// Like QSortFilterProxyModel's function.
    void setFilterFixedString(const QString &s);

    /// Reimplemented because we need to cleanup the stack of filters and set
    /// realSourceModel.
    void setSourceModel(QAbstractItemModel *sourceModel);

private:
    // This is the stack of chained filters.
    QStack<QSortFilterProxyModel*> filters;

    // The base class's source model needs to point to the last filter model,
    // so we need a new variable to hold the **actual** source.
    QAbstractItemModel *realSourceModel;
};

#endif // NARROWABLEFILTERPROXYMODEL_H
