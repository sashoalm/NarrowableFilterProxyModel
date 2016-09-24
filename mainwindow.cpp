#include "mainwindow.h"
#include "narrowablefilterproxymodel.h"
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

    NarrowableFilterProxyModel *filter = new NarrowableFilterProxyModel(this);
    ui->listView->setModel(filter);

    // Test that we reapply the filters on source changed by applying
    // them **before** setting the source model.
    ui->lineEdit->setText("1");
    ui->lineEdit->setText("11");
    ui->lineEdit->setText("111");
    filter->setSourceModel(model);
    filter->printRowCounts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    NarrowableFilterProxyModel *filter = (NarrowableFilterProxyModel*) ui->listView->model();
    filter->setFilterFixedString(text);
    filter->printRowCounts();
}
