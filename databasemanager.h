#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool openDatabase(const QString& path);
    void closeDatabase();
    QSqlError lastError();

private:
    QSqlDatabase db;
    DatabaseManager();
    ~DatabaseManager();

    // Disable copying
    DatabaseManager(const DatabaseManager& rhs) = delete;
    DatabaseManager& operator=(const DatabaseManager& rhs) = delete;
};

#endif // DATABASEMANAGER_H
