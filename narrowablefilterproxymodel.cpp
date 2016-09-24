#include "narrowablefilterproxymodel.h"

#include <QSortFilterProxyModel>

NarrowableFilterProxyModel::NarrowableFilterProxyModel(QObject *parent)
    : AbstractProxyChainModel(parent)
{

}

NarrowableFilterProxyModel::~NarrowableFilterProxyModel()
{

}

NarrowableFilterProxyModel::RelationType NarrowableFilterProxyModel::relationTo(QAbstractProxyModel *model, QAbstractProxyModel *sourceModel)
{
    QSortFilterProxyModel *filter = (QSortFilterProxyModel *) model;
    QSortFilterProxyModel *sourceFilter = (QSortFilterProxyModel *) sourceModel;
    const QString &pattern = filter->filterRegExp().pattern();
    const QString &sourcePattern = sourceFilter->filterRegExp().pattern();
    if (pattern == sourcePattern) {
        return Identical;
    } else if (pattern.contains(sourcePattern)) {
        return Narrower;
    } else {
        return Different;
    }
}

void NarrowableFilterProxyModel::setFilterFixedString(const QString &s)
{
    if (s.isEmpty()) {
        clearChain();
    } else {
        QSortFilterProxyModel *model = new QSortFilterProxyModel(this);
        model->setFilterFixedString(s);
        addToChain(model);
    }
}
