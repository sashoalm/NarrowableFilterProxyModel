#ifndef ABSTRACTPROXYCHAINMODEL_H
#define ABSTRACTPROXYCHAINMODEL_H

#include <QStack>
#include <QIdentityProxyModel>

/// An abstract class representing a proxy chain. It does not know anything
/// about the proxies, it just manages the chain using the "canBeChained"
/// function. It pops the stack automatically until it finds a suitable model,
/// or it reaches the original source.
///
/// It takes ownership over the proxies and deletes them, but not over the
/// proxies, but not over the original source.
class AbstractProxyChainModel : public QIdentityProxyModel
{
public:
    AbstractProxyChainModel(QObject *parent = 0);
    ~AbstractProxyChainModel();

    /// Reimplemented because we need to cleanup the stack of filters and set
    /// realSourceModel.
    void setSourceModel(QAbstractItemModel *sourceModel);

    /// Add a new proxy model to the chain.
    void addToChain(QAbstractProxyModel *model);

    /// Removes all the proxy models and sets the original data
    /// as our source.
    void clearChain();

protected:
    enum RelationType { Identical, Narrower, Different };

    /// Check if the model is identical, narrower or just different from sourceModel.
    /// Identical is used to avoid chaining redundant identical filters. Note that
    /// relationTo() is never called on the real source model, so derived classes
    /// need to check for an "empty" filter and explicitly call clearChain().
    virtual RelationType relationTo(QAbstractProxyModel *model, QAbstractProxyModel *sourceModel) = 0;

private:
    // The stack of chained models.
    QStack<QAbstractProxyModel*> chain;

    // QIdentityProxyModel's source model will point to the last filter model,
    // so we need a new variable to hold the **actual** source.
    QAbstractItemModel *realSourceModel;
};

#endif // ABSTRACTPROXYCHAINMODEL_H
