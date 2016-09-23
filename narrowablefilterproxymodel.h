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

    class IFilterFactory
    {
    public:
        virtual QSortFilterProxyModel *createFilter(QObject *parent = 0) = 0;
    };

    /// We use a filter factory so our class can work with classes inheriting
    /// from QSortFilterProxyModel, which can specialize filterAcceptsRows(),
    /// for example.
    void setFilterFactory(IFilterFactory *factory);

private:
    // This is the stack of chained filters.
    QStack<QSortFilterProxyModel*> filters;

    // The base class's source model needs to point to the last filter model,
    // so we need a new variable to hold the **actual** source.
    QAbstractItemModel *realSourceModel;

    IFilterFactory *factory;
};

#endif // NARROWABLEFILTERPROXYMODEL_H
