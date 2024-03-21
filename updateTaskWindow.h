#ifndef UPDATETASKWINDOW_H
#define UPDATETASKWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QtCore>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QAction>
#include <QtGui>
#include <Qt>
#include <QToolBar>
#include <QTableView>
#include <QHeaderView>
#include <QInputDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QTextEdit>
#include <QStringList>

class UpdateTaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    UpdateTaskWindow(QSqlTableModel *model,const QSqlDatabase& db,const int t_id);
private slots:
    void addButtonClicked(const QString& taskTitle,const QDate& dueDate,const int priority,const QString& completionStatus,const QString& description );
    // void handleTaskTitleChanged();
    // void handleDateChanged();
    // void handlePriorityChanged();
    // void handleStatusChanged();
    // void handleDescriptionChanged();
private:
    //Properties
    QSqlDatabase m_db;
    QSqlTableModel *m_model;
    int m_id;
    int changed[5];

    //Widgets
    QWidget *mainWidget;
    QVBoxLayout *centralWidgetLayout;
    QFormLayout *formLayout;
    QFormLayout *buttonLayout;
    QHBoxLayout *descriptionBoxLayout;

    //Labels
    QLabel *TaskNameLabel;
    QLabel *DueDateLabel; // date Picker set limit of date picker from the current day and year to end of year and add calendar
    QLabel *PriorityLabel;
    QLabel *completionStatusLabel;
    QLabel *DescriptionLabel;

    //Push Button
    QPushButton *addTaskPushButton;
    QPushButton *cancelPushButton;

    //Line Edit
    QLineEdit *TaskNameLineEdit;

    //Date Edit == date picker
    QDateEdit *dueDateDateEdit;

    //Spin box
    QSpinBox *prioritySpinBox;

    //Combo box
    QComboBox *completionStatusComboBox;

    //Text Edit == big text box
    QTextEdit *descriptionTextEdit;


    //Standard Item Model
    QStandardItemModel *model;

    void setupSignalsAndSlots();
    void setupCoreWidgets();
    //void onlyChanged();
    void selectInfo();

};
#endif // UPDATETASKWINDOW_H
