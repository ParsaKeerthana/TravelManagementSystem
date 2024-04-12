#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DatabaseManager.h"
#include "registertourist.h" // Include the RegisterTourist header file
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrAddPackge = new AddPackage();
    ptrRegisterTourist = new RegisterTourist(); // Create an instance of the RegisterTourist class
    ptrFindPackage = new FindPackage();
    ptrFindTourist = new FindTourist();

    // Initialize database connection
    if (!DatabaseManager::instance().openDatabase("/Users/keerthanaparsa/Desktop/202_final_project/Travel/MyTourstManager.db")) {
        qDebug() << "Failed to open database:" << DatabaseManager::instance().lastError().text();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrAddPackge;
    delete ptrRegisterTourist;
    delete ptrFindPackage;
    delete ptrFindTourist;
}

void MainWindow::on_pushButton_clicked() {
    ptrAddPackge->show();
}

void MainWindow::on_pushButton_2_clicked() {
    ptrRegisterTourist->show(); // Show the RegisterTourist dialog when the button is clicked
}

void MainWindow::on_pushButton_3_clicked() {
    ptrFindPackage->show();
}

void MainWindow::on_pushButton_4_clicked() {
    ptrFindTourist->show();
}
