#include "updateTaskWindow.h"

UpdateTaskWindow::UpdateTaskWindow(QSqlTableModel *model,const QSqlDatabase& db,const int t_id):m_db(db),m_model(model),m_id(t_id)
{
    setWindowTitle("Update Task");
    setFixedSize(250,250);

    //Methods
    setupCoreWidgets();
    setupSignalsAndSlots();

    //Central Widget Layout
    centralWidgetLayout->addLayout(formLayout);
    centralWidgetLayout->addLayout(descriptionBoxLayout); // Important
    centralWidgetLayout->addLayout(buttonLayout);

    mainWidget->setLayout(centralWidgetLayout);
    setCentralWidget(mainWidget);

}

void UpdateTaskWindow::setupCoreWidgets(){

    //Widgets
    mainWidget = new QWidget();
    centralWidgetLayout = new QVBoxLayout();

    //Layout
    formLayout = new QFormLayout();
    descriptionBoxLayout = new QHBoxLayout();
    buttonLayout = new QFormLayout();

    //Label
    TaskNameLabel = new QLabel("Task Name");
    DueDateLabel = new QLabel("Task Due Date");
    PriorityLabel = new QLabel("Task Priority");
    completionStatusLabel = new QLabel("Task Status");
    DescriptionLabel = new QLabel("Task Description");

    //Push Button
    addTaskPushButton = new QPushButton("Update task");
    cancelPushButton = new QPushButton("Cancel");

    //Line Edit
    TaskNameLineEdit = new QLineEdit();

    //Date picker
    dueDateDateEdit = new QDateEdit();
    dueDateDateEdit->setMinimumDate(QDate::currentDate());

    //SpinBox
    prioritySpinBox = new QSpinBox();
    prioritySpinBox->setRange(1,5);

    //ComboBox
    completionStatusComboBox = new QComboBox();
    QStringList completionStatusList ={"Incomplete","Complete"};
    completionStatusComboBox->addItems(completionStatusList);

    //Big text box
    descriptionTextEdit = new QTextEdit();
    descriptionTextEdit->setPlaceholderText("Optional");

    //Model
    //model = new QStandardItemModel(1,5,this);

    //Form layout
    formLayout->addRow(TaskNameLabel,TaskNameLineEdit);
    formLayout->addRow(DueDateLabel,dueDateDateEdit);
    formLayout->addRow(PriorityLabel,prioritySpinBox);
    formLayout->addRow(completionStatusLabel,completionStatusComboBox);
    formLayout->addRow(DescriptionLabel);
    descriptionBoxLayout->addWidget(descriptionTextEdit);
    buttonLayout->addRow(addTaskPushButton,cancelPushButton);

    selectInfo();
}

void UpdateTaskWindow::setupSignalsAndSlots(){
    //Setup Signals And Slots
    connect(addTaskPushButton,&QPushButton::clicked,this,[=](){
        addButtonClicked(TaskNameLineEdit->text(),dueDateDateEdit->date(),prioritySpinBox->value(),completionStatusComboBox->currentText(),descriptionTextEdit->toPlainText());
    });

    connect(cancelPushButton,&QPushButton::clicked,this,[=](){
        UpdateTaskWindow::close();
    });

    // connect(TaskNameLineEdit,&QLineEdit::textChanged,this,&UpdateTaskWindow::handleTaskTitleChanged);
    // connect(dueDateDateEdit,&QDateEdit::dateChanged,this,&UpdateTaskWindow::handleDateChanged);
    // connect(prioritySpinBox,&QSpinBox::valueChanged,this,&UpdateTaskWindow::handlePriorityChanged);
    // connect(completionStatusComboBox,&QComboBox::currentIndexChanged,this,&UpdateTaskWindow::handleStatusChanged);
    // connect(descriptionTextEdit,&QTextEdit::textChanged,this,&UpdateTaskWindow::handleDescriptionChanged);

}

// void UpdateTaskWindow::handleTaskTitleChanged(){
//     changed[0]=1;
// }

// void UpdateTaskWindow::handleDateChanged(){
//     changed[1]=1;
// }

// void UpdateTaskWindow::handlePriorityChanged(){
//     changed[2]=1;
// }

// void UpdateTaskWindow::handleStatusChanged(){
//     changed[3]=1;
// }

// void UpdateTaskWindow::handleDescriptionChanged(){
//     changed[4]=1;
// }

// void UpdateTaskWindow::onlyChanged(){
//     QString word ="";
//     QDate date =; ;
//     for(int i =0;i<5;i++){
//         if(changed[0]==1){
//             word =TaskNameLineEdit->text();
//         }

//         if(changed[1]==1){
//             date = dueDateDateEdit->date();
//         }

//         if(changed[2]==1){
//             word =TaskNameLineEdit->text();
//         }

//         if(changed[3]==1){
//             word =TaskNameLineEdit->text();
//         }

//         if(changed[4]==1){
//             word =TaskNameLineEdit->text();
//         }

//     }
// }

void UpdateTaskWindow::selectInfo(){
    try{
        QSqlQuery selectStatement(m_db);
        selectStatement.prepare("Select * FROM task WHERE task_id=:task_id");
        selectStatement.bindValue(":task_id",m_id);
        if(!selectStatement.exec()){
            qDebug()<<"Error executing SQL statement"<< selectStatement.lastError().text();
        }else{
            while(selectStatement.next()){
                QString tasktitle = selectStatement.value(2).toString();
                QDate date = selectStatement.value(3).toDate();
                int priority = selectStatement.value(4).toInt();
                QString status = selectStatement.value(5).toString();
                QString description =selectStatement.value(6).toString();
                TaskNameLineEdit->setText(tasktitle);
                dueDateDateEdit->setDate(date);
                prioritySpinBox->setValue(priority);
                completionStatusComboBox->setCurrentText(status);
                descriptionTextEdit->setText(description);
            }
        }
    }catch(const QSqlError &error){
        qDebug()<<"Database error:"<<error.text();
    }
}

void UpdateTaskWindow::addButtonClicked(const QString& taskTitle,const QDate& dueDate,const int priority,const QString& completionStatus,const QString& description ){
    // FAIRE correctement le update query et faire que le code update seulement les champs qui ont ete modifier (puet-etre utiliser un switch case)

    try{
        QSqlQuery updateTask(m_db);
        updateTask.prepare("UPDATE task SET task_title=:task_title,due_date=:due_date,priority=:priority,status=:status,description=:description WHERE task_id=:task_id");
        updateTask.bindValue(":task_title",taskTitle);
        updateTask.bindValue(":due_date",dueDate);
        updateTask.bindValue(":priority",priority);
        updateTask.bindValue(":status",completionStatus);
        updateTask.bindValue(":description",description);
        updateTask.bindValue(":task_id",m_id);
        if(!updateTask.exec()){
            qDebug() << "Error executing SQL statement:"<< updateTask.lastError().text();
        }else{
            qDebug() << "task updated succesfully.";
            m_model->submitAll();
            UpdateTaskWindow::close();
        }
    }catch(const QSqlError &error){
        qDebug() << "Database error:"<<error.text();
    }
}
