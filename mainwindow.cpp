#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSortFilterProxyModel>
#include <QStringListModel>

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

    QSortFilterProxyModel *filter = new QSortFilterProxyModel(this);
    filter->setSourceModel(model);

    ui->listView->setModel(filter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    QSortFilterProxyModel *filter = (QSortFilterProxyModel*) ui->listView->model();
    filter->setFilterFixedString(text);
}
