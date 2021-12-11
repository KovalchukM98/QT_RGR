#ifndef ADD_FORM_H
#define ADD_FORM_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class Add_form;
}

class Add_form : public QWidget
{
    Q_OBJECT

public:
    explicit Add_form(QWidget *parent = 0);
    ~Add_form();

    Add_form(QSqlDatabase db);

    void connect_database(QSqlQuery *db);

    void prepare(QString name, QString size, QString man, QString transf,
                 int cost, int num, QString date, QString photo, QString sex);

    QSqlQuery *query = nullptr;
    bool change = false;
    int code = 0;

private:
    Ui::Add_form *ui;

private slots:
    void cancel_clicked();
    void ok_clicked();

signals:
    void need_refresh();
};

#endif // ADD_FORM_H
