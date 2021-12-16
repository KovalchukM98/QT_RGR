#ifndef SEARCH_FORM_H
#define SEARCH_FORM_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class search_form;
}

class search_form : public QWidget
{
    Q_OBJECT

public:
    explicit search_form(QWidget *parent = 0);
    ~search_form();

    search_form(QSqlTableModel *model);

    void connect_window(QSqlTableModel *model, QTableView *view);

    QTableView *table;
    QSqlTableModel *tableModel = nullptr;

private:
    Ui::search_form *ui;

private slots:
    void reset_clicked();
    void search_clicked();
    void cancel_clicked();

    void change_state_name();
    void change_state_size();
    void change_state_man();
    void change_state_prov();
    void change_state_cost();
    void change_state_num();
    void change_state_date();
    void change_state_sex();

signals:
    void need_refresh();
    void need_reset();

};

#endif // SEARCH_FORM_H
