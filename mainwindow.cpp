#include "mainwindow.h"
#include "TaskManagerMainWindow.h"

MainWindow::MainWindow(const QSqlDatabase& db)
    : m_db(db)
{
    // Window
    setWindowTitle("Login");
    setFixedSize(250,145);

    // Methods
    setupCoreWidgets();
    setupSignalAndSlots();

    // Layout
    centralWidgetLayout->addLayout(formLayout);

    // Main Widget
    mainWidget->setLayout(centralWidgetLayout);
    setCentralWidget(mainWidget);
}

void MainWindow::setupCoreWidgets(){
    // Widgets
    mainWidget = new QWidget();
    centralWidgetLayout = new QVBoxLayout();

    // Layout
    formLayout = new QFormLayout();

    // Label
    usernameLabel = new QLabel("Username");
    passwordLabel = new QLabel("Password");

    // Push Button
    loginPushButton = new QPushButton("&Login");

    // Line Edit
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setPlaceholderText("Enter Username");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setPlaceholderText("Enter Password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Form Layout
    formLayout->addRow(usernameLabel);
    formLayout->addRow(usernameLineEdit);
    formLayout->addRow(passwordLabel);
    formLayout->addRow(passwordLineEdit);
    formLayout->addRow(loginPushButton);
}

void MainWindow::setupSignalAndSlots(){
    // Setup Signal and Slots
    connect(loginPushButton,&QPushButton::clicked,this,[=](){
        loginUserClicked(usernameLineEdit->text(),passwordLineEdit->text());
    });
}

void MainWindow::loginUserClicked(const QString& username,const QString& password){
    try{
        QSqlQuery select_user_statement(m_db);
        if(!select_user_statement.prepare("SELECT id,username,password,role FROM login WHERE username=:username AND password=:password")){
            qDebug() << "Error preparing SQL statement:" << select_user_statement.lastError().text();
        }else{
            select_user_statement.bindValue(":username",username);
            select_user_statement.bindValue(":password",password);
            if(!select_user_statement.exec()){
                qDebug() << "Error executing SQL statement:"<<select_user_statement.lastError().text();
            }else{
                if(select_user_statement.next()){
                    QSqlRecord record = select_user_statement.record();
                    QString role = select_user_statement.value(record.indexOf("role")).toString();
                    int id = select_user_statement.value(record.indexOf("id")).toInt();
                    if(role == "admin"){
                        TaskManagerMainWindow *tm = new TaskManagerMainWindow(m_db,id);
                        tm->setAttribute(Qt::WA_DeleteOnClose);
                        MainWindow::close();
                        tm->show();
                    }else{

                    }
                }else{
                    // Invalid password or username
                    QMessageBox::warning(this,tr("Invalid login"),tr("Invalid username or password."),QMessageBox::Ok|QMessageBox::Default,QMessageBox::NoButton);
                    passwordLineEdit->clear();
                }
            }
        }
    }catch(const QSqlError &error){
        qDebug() << "Database error:" << error.text();
    }
}
