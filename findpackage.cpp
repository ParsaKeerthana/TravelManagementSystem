#include "findpackage.h"
#include "ui_findpackage.h"
#include <QMessageBox>

FindPackage::FindPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPackage)
{
    ui->setupUi(this);
}

FindPackage::~FindPackage()
{
    qDebug() << "~ Findpackage()";
    delete ui;
    delete model;
}

void FindPackage::on_btnFindPackage_clicked()
{
    QString packageName = ui->txtPackageName->text().trimmed();
    if (packageName.isEmpty()) {
        QMessageBox::information(this, "Input Required", "Please enter a package name to search.");
        return;
    }

    qDebug() << "Package Name : " << packageName;
    QSqlDatabase database = QSqlDatabase::database("DB1");

    if (!model)
        model = new QSqlQueryModel();

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Package WHERE PackageName LIKE :packageName");
    query.bindValue(":packageName", '%' + packageName + '%');

    if (!query.exec()) {
        QMessageBox::critical(this, "Search Error", "Failed to search packages: " + query.lastError().text());
        return;
    }

    model->setQuery(std::move(query));  // Adjusted to use move semantics
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No packages found matching the criteria.");
    } else {
        ui->tableView->setModel(model);
    }
}
