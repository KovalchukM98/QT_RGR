#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QSqlError>
#include <QDateTime>
#include "add_form.h"
#include "day_form.h"
#include "search_form.h"
#include "faq_form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void RefreshTable();

private slots:
    void info_clicked();
    void new_clicked();
    void open_clicked();
    void save_clicked();
    void exit_clicked();

    void change_clicked();
    void add_clicked();
    void delete_clicked();
    void search_clicked();
    void day_clicked();
    void reset_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QSqlTableModel *tableModel = nullptr;
    QSqlQuery *query = nullptr;
    Add_form *add_form = nullptr;
    Day_form *day_form = nullptr;
    search_form *search_f = nullptr;
    Faq_form *faq_form = nullptr;
};

#endif // MAINWINDOW_H
