#include "narrowablefilterproxymodel.h"

#include <QSortFilterProxyModel>

NarrowableFilterProxyModel::NarrowableFilterProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
    realSourceModel = 0;
}

NarrowableFilterProxyModel::~NarrowableFilterProxyModel()
{

}

void NarrowableFilterProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    realSourceModel = sourceModel;

    // QSortFilterProxyModel doesn't discard its filter on source model change, instead
    // it just reapplies it. We want to mimic that behavior. Filters have a source changed
    // event/signal, so it's enough to set the bottom-most filter in tha stack to the new
    // source model and the change will propagade all the way through to the top-most
    // filter.
    if (!filters.isEmpty()) {
        filters.front()->setSourceModel(realSourceModel);
    } else {
        QIdentityProxyModel::setSourceModel(realSourceModel);
    }
}

void NarrowableFilterProxyModel::setFilterFixedString(const QString &s)
{
    QSortFilterProxyModel *model = new QSortFilterProxyModel(this);
    model->setFilterFixedString(s);

    QAbstractItemModel *topModel = realSourceModel;
    while (!filters.isEmpty()) {
        if (s.contains(filters.top()->filterRegExp().pattern())) {
            topModel = filters.top();
            break;
        } else {
            delete filters.pop();
        }
    }

    model->setSourceModel(topModel);
    QIdentityProxyModel::setSourceModel(model);
    filters.push(model);
}
