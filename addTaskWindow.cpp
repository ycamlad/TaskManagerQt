#include "addTaskWindow.h"

AddTaskWindow::AddTaskWindow(QSqlTableModel *model,const QSqlDatabase& db,const int u_id):m_db(db),m_model(model),m_id(u_id)
{
    setWindowTitle("Add Task");
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

void AddTaskWindow::setupCoreWidgets(){

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
    addTaskPushButton = new QPushButton("Add task");
    cancelPushButton = new QPushButton("cancel");

    //Line Edit
    TaskNameLineEdit = new QLineEdit();
    TaskNameLineEdit->setPlaceholderText("Task title");

    //Date picker
    dueDateDateEdit = new QDateEdit;
    dueDateDateEdit->setDate(dueDateDateEdit->date());
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
}

void AddTaskWindow::setupSignalsAndSlots(){
    //Setup Signals And Slots
    connect(addTaskPushButton,&QPushButton::clicked,this,[=](){
        addButtonClicked(TaskNameLineEdit->text(),dueDateDateEdit->date(),prioritySpinBox->value(),completionStatusComboBox->currentText(),descriptionTextEdit->toPlainText());
    });

    connect(cancelPushButton,&QPushButton::clicked,this,[=](){
        AddTaskWindow::close();
    });
}

void AddTaskWindow::addButtonClicked(const QString& taskTitle,const QDate& dueDate,const int priority,const QString& completionStatus,const QString& description ){
    try{
        QSqlQuery saveTask(m_db);
        saveTask.prepare("INSERT INTO task(user_id,task_title,due_date,priority,status,description)""VALUES(:user_id,:task_title,:due_date,:priority,:status,:description)");
        saveTask.bindValue(":user_id",m_id); //Temporaire
        saveTask.bindValue(":task_title",taskTitle);
        saveTask.bindValue(":due_date",dueDate);
        saveTask.bindValue(":priority",priority);
        saveTask.bindValue(":status",completionStatus);
        saveTask.bindValue(":description",description);
        if(!saveTask.exec()){
            qDebug() << "Error executing SQL statement:"<< saveTask.lastError().text();
        }else{
            qDebug() << "New task inserted succesfully.";
            m_model->submitAll();
            clearFields();
        }
    }catch(const QSqlError &error){
        qDebug() << "Database error:"<<error.text();
    }
}

void AddTaskWindow::clearFields(){
    TaskNameLineEdit->clear();
    dueDateDateEdit->clear();
    prioritySpinBox->clear();
    completionStatusComboBox->clear();
    descriptionTextEdit->clear();
}
