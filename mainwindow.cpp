#include "mainwindow.h"
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

    QSortFilterProxyModel *filter = new MyFilter(this);
    filter->setSourceModel(model);

    ui->listView->setModel(filter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    MyFilter *filter = (MyFilter*) ui->listView->model();
    filter->resetCounter();
    filter->setFilterFixedString(text);
    qDebug("%d", filter->getCounter());
}
