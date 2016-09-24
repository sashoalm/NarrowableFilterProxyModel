#include "abstractproxychainmodel.h"

AbstractProxyChainModel::AbstractProxyChainModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
    realSourceModel = 0;
}

AbstractProxyChainModel::~AbstractProxyChainModel()
{

}

void AbstractProxyChainModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    realSourceModel = sourceModel;

    // QSortFilterProxyModel doesn't discard its filter on source model change, instead
    // it just reapplies it. We want to mimic that behavior. Filters have a source changed
    // event/signal, so it's enough to set the bottom-most filter in tha stack to the new
    // source model and the change will propagade all the way through to the top-most
    // filter.
    if (!chain.isEmpty()) {
        chain.front()->setSourceModel(realSourceModel);
    } else {
        QIdentityProxyModel::setSourceModel(realSourceModel);
    }
}

void AbstractProxyChainModel::addToChain(QAbstractProxyModel *model)
{
    // We take ownership over the proxy model.
    model->setParent(this);

    // Pop the stack until we find a suitable proxy to use as a source for the
    // new one. If no suitable proxy, we just chain it to the original source
    // directly.
    // We initialize it in case the chain is empty.
    RelationType relation = Different;
    while (!chain.isEmpty()) {
        relation = relationTo(model, chain.top());
        if (Different != relation) {
            break;
        }

        delete chain.pop();
    }

    if (Identical == relation) {
        // New model is redundant, discard it and just reuse the top model.
        delete model;
    } else {
        model->setSourceModel(chain.isEmpty() ? realSourceModel : chain.top());
        chain.push(model);
    }

    if (QIdentityProxyModel::sourceModel() != chain.top()) {
        QIdentityProxyModel::setSourceModel(chain.top());
    }
}

void AbstractProxyChainModel::clearChain()
{
    QIdentityProxyModel::setSourceModel(realSourceModel);
    qDeleteAll(chain);
    chain.clear();
}
