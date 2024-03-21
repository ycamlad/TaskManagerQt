#include "TaskManagerMainWindow.h"
#include "DatabaseManagementClass.h"
#include "UserSingleton.h"
#include "addTaskWindow.h"
#include "updateTaskWindow.h"

DatabaseManagementClass *dbmc = new DatabaseManagementClass();

TaskManagerMainWindow::TaskManagerMainWindow(const QSqlDatabase& db,const int id):m_db(db),m_id(id){
    //Window
    setWindowTitle("Task Manager");
    setFixedSize(500,500);

    //Methods
    setupCoreWidgets();
    setupSignalsAndSlots();

    //Layout
    layout->addWidget(taskTableView);
    layout->addWidget(addTaskPushButton);
    layout->addWidget(updateTaskPushButton);
    layout->addWidget(deleteTaskPushButton);

    //Main
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
    UserSingleton::getInstance().setLoginId(m_id);
}

void TaskManagerMainWindow::setupCoreWidgets(){
    tasksTableModel = new QSqlTableModel(0,m_db);
    taskTableView = new QTableView();

    //Initialize widget and layout
    mainWidget = new QWidget();
    layout = new QVBoxLayout();

    //Push Button
    addTaskPushButton = new QPushButton("Add Task");
    updateTaskPushButton = new QPushButton("Update Task");
    deleteTaskPushButton = new QPushButton("Delete Task");

    //Table Model
    tasksTableModel->setTable("task");
    tasksTableModel->select();
    tasksTableModel->setHeaderData(TaskName,Qt::Horizontal,QObject::tr("Task Name"));
    tasksTableModel->setHeaderData(Priority,Qt::Horizontal,QObject::tr("Priority"));
    tasksTableModel->setHeaderData(DueDate,Qt::Horizontal,QObject::tr("Due date"));
    tasksTableModel->setHeaderData(CompletionStatus,Qt::Horizontal,QObject::tr("Status"));
    tasksTableModel->setHeaderData(Description,Qt::Horizontal,QObject::tr("Description"));
    tasksTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);// edit strategy

    //Table View
    taskTableView->setModel(tasksTableModel);
    taskTableView->setColumnHidden(0,true);
    taskTableView->setColumnHidden(1,true);
    taskTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    taskTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *header = taskTableView->horizontalHeader();
    header->setStretchLastSection(true);
}

void TaskManagerMainWindow::setupSignalsAndSlots(){

    //Setup Signals and Slots
    QObject::connect(addTaskPushButton,&QPushButton::clicked,tasksTableModel,[=](){
        AddTaskWindow *aw = new AddTaskWindow(tasksTableModel,m_db,m_id);
        aw->setAttribute(Qt::WA_DeleteOnClose);
        aw->show();
    });

    QObject::connect(updateTaskPushButton,&QPushButton::clicked,tasksTableModel,[=](){
        QModelIndexList selectedRows = taskTableView->selectionModel()->selectedRows();
        if(!selectedRows.isEmpty()){
            int row = selectedRows.first().row();
            QModelIndex taskIndex = tasksTableModel->index(row,0);
            QVariant taskIdData = tasksTableModel->data(taskIndex);
            if(taskIdData.isValid()){
                int taskId = taskIdData.toInt();
                UpdateTaskWindow *uw = new UpdateTaskWindow(tasksTableModel,m_db,taskId);
                uw->setAttribute(Qt::WA_DeleteOnClose);
                uw->show();
            }
        }
    });

    QObject::connect(deleteTaskPushButton,&QPushButton::clicked,tasksTableModel,[=](){
        QModelIndexList selectedRows = taskTableView->selectionModel()->selectedRows();
        if(!selectedRows.isEmpty()){
            int row = selectedRows.first().row();
            QModelIndex taskIndex = tasksTableModel->index(row,2);
            QVariant taskIdData = tasksTableModel->data(taskIndex);
            if(taskIdData.isValid()){
                //int taskId = taskIdData.toInt();
                qDebug()<<taskIdData.toString();
            }
            //int taskToDelete = selectedRows.first().row();
            //deleteTask(taskTableView,tasksTableModel,taskToDelete);
        }
    });
}

void TaskManagerMainWindow::addWindow(){
    AddTaskWindow *aw = new AddTaskWindow(tasksTableModel,m_db,m_id);
    aw->setAttribute(Qt::WA_DeleteOnClose);
    aw->show();
}

void TaskManagerMainWindow::updateWindow(){


}

void TaskManagerMainWindow::deleteTask(QTableView *taskManagerTableView,QSqlTableModel *taskManagerTableModel,int row){
    if(taskManagerTableView){
        QMessageBox msgBox;
        msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        msgBox.setText("Delete task?");
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes){
            taskManagerTableView->model()->removeRow(row);
            taskManagerTableModel->submitAll();
            msgBox.information(this,tr("Task Deleted"),tr("Task deleted successfully."));
        }else{
            msgBox.close();
        }
    }
}
