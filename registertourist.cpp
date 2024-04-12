#include "registertourist.h"
#include "ui_registertourist.h"
#include <QMessageBox>

RegisterTourist::RegisterTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterTourist)
{
    ui->setupUi(this);
}

RegisterTourist::~RegisterTourist()
{
    qDebug() << "in ~RegisterTourist()";
    delete ui;
}

void RegisterTourist::on_btnSave_clicked()
{
    QString firstName = ui->txtFirstName->text().trimmed();
    QString middleName = ui->txtMiddleName->text().trimmed();
    QString lastName = ui->txtLastName->text().trimmed();
    QString passportNo = ui->txtPassportNo->text().trimmed();
    QString contactNo = ui->txtContactNo->text().trimmed();
    QString permanentAddress = ui->txtPermanentAddress->text().trimmed();
    QString packageName = ui->cmbChoosePackage->currentText().trimmed();

    if (firstName.isEmpty() || lastName.isEmpty() || passportNo.isEmpty() || packageName.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please fill in all required fields.");
        return;
    }

    QSqlDatabase database = QSqlDatabase::database("DB1");
    QSqlQuery query(database);

    query.prepare("INSERT INTO Tourist (FirstName, MiddleName, LastName, PassportNo, ContactNo, PermanentAddress, PackageName) "
                  "VALUES (:firstName, :middleName, :lastName, :passportNo, :contactNo, :permanentAddress, :packageName)");
    query.bindValue(":firstName", firstName);
    query.bindValue(":middleName", middleName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":passportNo", passportNo);
    query.bindValue(":contactNo", contactNo);
    query.bindValue(":permanentAddress", permanentAddress);
    query.bindValue(":packageName", packageName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to register tourist: " + query.lastError().text());
        qDebug() << "Failed to execute insert query:" << query.lastError().text();
        return;
    }

    QMessageBox::information(this, "Success", "Tourist registered successfully.");
    on_btnReset_clicked();
}

void RegisterTourist::on_loadPakcage_clicked()
{
    QSqlDatabase database = QSqlDatabase::database("DB1");
    QSqlQuery query(database);

    query.prepare("SELECT PackageName FROM Package");
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    // Clear the combo box before repopulating it
    ui->cmbChoosePackage->clear();

    while (query.next())
    {
        QString packageName = query.value(0).toString().trimmed();

        // Check if the package name is empty or contains unexpected characters
        if (!packageName.isEmpty() && packageName != "asdfasdf") {
            ui->cmbChoosePackage->addItem(packageName);
            qDebug() << "Filling Combobox" << packageName;
        }
    }

    qDebug() << "Last query:" << query.lastQuery();
    qDebug() << "Last error:" << query.lastError().text();
}

void RegisterTourist::on_cmbChoosePackage_currentIndexChanged(int index)
{
    QString packageName = ui->cmbChoosePackage->currentText();
    QSqlDatabase database = QSqlDatabase::database("DB1");
    QSqlQuery query(database);

    query.prepare("SELECT PackageDescription FROM Package WHERE PackageName = :packageName");
    query.bindValue(":packageName", packageName);
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString packageDescription = query.value(0).toString();
        ui->txtPackageDescription->setText(packageDescription);
    } else {
        ui->txtPackageDescription->clear();
    }

    qDebug() << "Last query:" << query.lastQuery();
    qDebug() << "Last error:" << query.lastError().text();
}

void RegisterTourist::on_btnReset_clicked()
{
    ui->txtFirstName->clear();
    ui->txtLastName->clear();
    ui->txtMiddleName->clear();
    ui->txtContactNo->clear();
    ui->txtPassportNo->clear();
    ui->txtPermanentAddress->clear();
    ui->txtPackageDescription->clear();
}
