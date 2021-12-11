#ifndef FAQ_FORM_H
#define FAQ_FORM_H

#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class Faq_form;
}

class Faq_form : public QWidget
{
    Q_OBJECT

public:
    explicit Faq_form(QWidget *parent = 0);
    ~Faq_form();

    QString path = "D:/Qt_lab/";

private:
    Ui::Faq_form *ui;

public slots:
    void author_clicked();
    void close_clicked();
    void operation_clicked();
    void day_clicked();
    void search_clicked();
};

#endif // FAQ_FORM_H
