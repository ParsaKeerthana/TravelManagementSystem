#include "addpackage.h"
#include "ui_addpackage.h"
#include <QMessageBox>


AddPackage::AddPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPackage)
{
    ui->setupUi(this);
}

AddPackage::~AddPackage()
{   qDebug() << "~ AddPackage()";
    delete ui;
}

void AddPackage::on_btnSave_clicked()
{
    QString packageName = ui->txtPackageName->text();
    QString packageDescription = ui->txtDescription->toPlainText();
    QString amount = ui->txtAmount->text();
    // Validate input fields
    if (packageName.isEmpty() || packageDescription.isEmpty() || amount.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields before saving.");
        return; // Prevent database operation if validation fails
    }
    qDebug() << "Package Name : " << packageName << " Package Description : " << packageDescription << " Amount : " << amount;

    QSqlDatabase database = QSqlDatabase::database("DB1");
    QSqlQuery query(database);
    query.prepare("INSERT INTO Package (PackageName, PackageDescription, Amount) VALUES (?, ?, ?)");
    query.addBindValue(packageName);
    query.addBindValue(packageDescription);
    query.addBindValue(amount);

    if (!query.exec()) {
        qDebug() << "Error inserting data: " << query.lastError().text();
    } else {
        qDebug() << "Data inserted successfully";
    }

    on_btnReset_clicked();
}



void AddPackage::on_btnReset_clicked()
{
    ui->txtPackageName->clear();
    ui->txtDescription->clear();
    ui->txtAmount->clear();
}

