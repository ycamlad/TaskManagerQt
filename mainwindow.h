#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QSqlDatabase& db);
private slots:
    void loginUserClicked(const QString& username,const QString& password);
private:
    // Properties
    QSqlDatabase m_db;

    // Widgets
    QWidget *mainWidget;
    QVBoxLayout *centralWidgetLayout;
    QFormLayout *formLayout;

    // Labels
    QLabel *usernameLabel;
    QLabel *passwordLabel;

    // Line Edit
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;

    // Push Buttons
    QPushButton *loginPushButton;

    // Methods
    void setupSignalAndSlots();
    void setupCoreWidgets();
};
#endif // MAINWINDOW_H
