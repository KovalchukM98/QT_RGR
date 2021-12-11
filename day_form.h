#ifndef DAY_FORM_H
#define DAY_FORM_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QSqlTableModel>

namespace Ui {
class Day_form;
}

class Day_form : public QWidget
{
    Q_OBJECT

public:
    explicit Day_form(QWidget *parent = 0);
    ~Day_form();

    Day_form(QSqlDatabase db);
    QSqlQuery *query = nullptr;
    QSqlTableModel *tableModel = nullptr;
private:
    Ui::Day_form *ui;

private slots:
    void close_clicked();
    void search_clicked();
};

#endif // DAY_FORM_H
