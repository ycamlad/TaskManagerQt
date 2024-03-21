#ifndef DATABASEMANAGEMENTCLASS_H
#define DATABASEMANAGEMENTCLASS_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

class DatabaseManagementClass{
public:
    DatabaseManagementClass();
    static QSqlDatabase initializeDatabase(const QString& driver,const QString& hostName,int port,const QString& userName,const QString& passWord,const QString& dbName);
    void selectQuery();
    void selectAllQuery();
    void deleteQuery();
    void insertQuery();

private:
    static QSqlDatabase m_database;
};

#endif // DATABASEMANAGEMENTCLASS_H
