#include "DatabaseManagementClass.h"

DatabaseManagementClass::DatabaseManagementClass(){

}

QSqlDatabase DatabaseManagementClass::m_database;

QSqlDatabase DatabaseManagementClass::initializeDatabase(const QString& driver,const QString& hostName,int port,const QString& userName,const QString& passWord,const QString& dbName){
    m_database = QSqlDatabase::addDatabase(driver);
    m_database.setHostName(hostName);
    m_database.setPort(port);
    m_database.setUserName(userName);
    m_database.setPassword(passWord);
    m_database.setDatabaseName(dbName);

    if(!m_database.open()){
        qDebug() << m_database.lastError();
    }else{
        qDebug()<<"Database connection established !";
    }
    return m_database;
}
