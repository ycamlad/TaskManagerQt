#ifndef TASKMANAGERMAINWINDOW_H
#define TASKMANAGERMAINWINDOW_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QtCore>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <Qt>
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>

class TaskManagerMainWindow: public QMainWindow{
    Q_OBJECT
public:
    TaskManagerMainWindow(const QSqlDatabase& db,const int id);

private slots:
    void deleteTask(QTableView *taskManagerTableView,QSqlTableModel *taskManagerTableModel,int row);
    void addWindow();
    void updateWindow();
private:
    // properties
    QSqlDatabase m_db;
    int m_id;
    enum{
        TaskName=2,
        Priority=4,
        DueDate=3,
        CompletionStatus=5,
        Description=6,
    }Columns;

    //Widgets
    QSqlTableModel *tasksTableModel;
    QTableView *taskTableView;
    QVBoxLayout *layout;
    QWidget *mainWidget;

    //Push Buttons
    QPushButton *addTaskPushButton;
    QPushButton *updateTaskPushButton;
    QPushButton *deleteTaskPushButton;

    void setupSignalsAndSlots();
    void setupCoreWidgets();
};

#endif // TASKMANAGERMAINWINDOW_H
