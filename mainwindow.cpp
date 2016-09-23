#include "mainwindow.h"
#include "narrowablefilterproxymodel.h"
#include "ui_mainwindow.h"

#include <QSortFilterProxyModel>
#include <QStringListModel>

class MyFilter : public QSortFilterProxyModel
{
public:
    MyFilter(QObject *parent = 0) : QSortFilterProxyModel(parent) { counter = 0; }
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
    {
        counter++;
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }
    void resetCounter() { counter = 0; }
    int getCounter() const { return counter; }
private:
    mutable int counter;
};

class MyFilterFactory : public NarrowableFilterProxyModel::IFilterFactory
{
    QSortFilterProxyModel *createFilter(QObject *parent)
    {
        lastCreatedFilter = new MyFilter(parent);
        return lastCreatedFilter;
    }

public:
    MyFilterFactory() { lastCreatedFilter = 0; }
    MyFilter *lastCreatedFilter;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list;
    for (int ii = 0; ii < 30000; ++ii) {
        list.append(QString::number(qrand()));
    }

    QStringListModel *model = new QStringListModel(this);
    model->setStringList(list);

    NarrowableFilterProxyModel *filter = new NarrowableFilterProxyModel(this);
    ui->listView->setModel(filter);

    factory = new MyFilterFactory();

    // Test that we reapply the filters on source changed by applying
    // them **before** setting the source model.
    ui->lineEdit->setText("1");
    ui->lineEdit->setText("11");
    ui->lineEdit->setText("111");
    filter->setSourceModel(model);

    filter->setFilterFactory(factory);
}

MainWindow::~MainWindow()
{
    delete factory;
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    NarrowableFilterProxyModel *filter = (NarrowableFilterProxyModel*) ui->listView->model();
    filter->setFilterFixedString(text);
    if (factory->lastCreatedFilter) {
        qDebug("%d", factory->lastCreatedFilter->getCounter());
    }
}
