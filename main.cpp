#include "mainwindow.h"
#include "DatabaseManagementClass.h"
#include <QApplication>
#include "TaskManagerMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = DatabaseManagementClass::initializeDatabase("QMYSQL","127.0.0.1",3306,"root","","taskmanager_db");
    //MainWindow *w = new MainWindow(db);
    //w->show();
    TaskManagerMainWindow *t =new TaskManagerMainWindow(db,1);
    t->show();
    return a.exec();

}
