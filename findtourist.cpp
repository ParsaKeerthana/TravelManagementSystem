#include "findtourist.h"
#include "ui_findtourist.h"
#include <QMessageBox>

FindTourist::FindTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindTourist)
{
    ui->setupUi(this);
    model = NULL;
}

FindTourist::~FindTourist()
{
    qDebug() << "In ~FindTourist()";
    delete ui;
    delete model;
}

void FindTourist::on_btnFind_clicked()
{
    QString firstName = ui->txtTourstfName->text().trimmed();
    if (firstName.isEmpty()) {
        QMessageBox::information(this, "Input Required", "Please enter a first name to search.");
        return;
    }

    qDebug() << "First Name : " << firstName;
    QSqlDatabase database = QSqlDatabase::database("DB1");

    if (!model)
        model = new QSqlQueryModel();

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Tourist WHERE FirstName LIKE :firstName");
    query.bindValue(":firstName", '%' + firstName + '%');

    if (!query.exec()) {
        QMessageBox::critical(this, "Search Error", "Failed to search tourists: " + query.lastError().text());
        return;
    }

    model->setQuery(std::move(query));  // Adjusted to use move semantics
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No tourists found matching the criteria.");
    } else {
        ui->tableView->setModel(model);
    }
}


