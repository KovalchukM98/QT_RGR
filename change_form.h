#ifndef CHANGE_FORM_H
#define CHANGE_FORM_H

#include <QWidget>

namespace Ui {
class Change_form;
}

class Change_form : public QWidget
{
    Q_OBJECT

public:
    explicit Change_form(QWidget *parent = 0);
    ~Change_form();

private:
    Ui::Change_form *ui;
};

#endif // CHANGE_FORM_H
