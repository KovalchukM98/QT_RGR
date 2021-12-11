#include "change_form.h"
#include "ui_change_form.h"

Change_form::Change_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change_form)
{
    ui->setupUi(this);
}

Change_form::~Change_form()
{
    delete ui;
}
