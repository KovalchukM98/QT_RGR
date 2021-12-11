#include "search_form.h"
#include "ui_search_form.h"

search_form::search_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search_form)
{
    ui->setupUi(this);
    connect(ui->Cancel_Button, SIGNAL(clicked()), this, SLOT(cancel_clicked()));
    connect(ui->Reset_button, SIGNAL(clicked()), this, SLOT(reset_clicked()));
    connect(ui->Search_Button, SIGNAL(clicked()), this, SLOT(search_clicked()));
    ui->dateEdit->setDate(QDate::currentDate());
}

search_form::search_form(QSqlTableModel *model) : ui(new Ui::search_form){
    tableModel = model;
    ui->setupUi(this);
    connect(ui->Cancel_Button, SIGNAL(clicked()), this, SLOT(cancel_clicked()));
    connect(ui->Reset_button, SIGNAL(clicked()), this, SLOT(reset_clicked()));
    connect(ui->Search_Button, SIGNAL(clicked()), this, SLOT(search_clicked()));
    ui->dateEdit->setDate(QDate::currentDate());
}

void search_form::connect_window(QSqlTableModel *model, QTableView *view){
    tableModel = model;
    table = view;
}

search_form::~search_form()
{
    delete ui;
}

void search_form::cancel_clicked(){
    ui->Name_line->clear();
    ui->Size_line->clear();
    ui->Manufacturer_line->clear();
    ui->Provider_line->clear();
    ui->Cost_line->clear();
    ui->Num_line->clear();
    ui->gender_line->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    hide();
}

void search_form::reset_clicked(){
    emit need_reset();
}

void search_form::search_clicked(){
    if(table == nullptr || tableModel == nullptr){
        QMessageBox::warning( 0 , "Ошибка!", "нет привязки к таблице");
    }
    for(int i = 0; i < tableModel->rowCount(); ++i){
        if(!ui->Name_line->text().isEmpty() && ui->Name_line->text() != tableModel->index(i, 1).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
        if(!ui->Size_line->text().isEmpty() && ui->Size_line->text() != tableModel->index(i, 2).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
        if(!ui->Manufacturer_line->text().isEmpty() && ui->Manufacturer_line->text() != tableModel->index(i, 3).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
        if(!ui->Provider_line->text().isEmpty() && ui->Provider_line->text() != tableModel->index(i, 4).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
        if(!ui->Cost_line->text().isEmpty() && ui->Cost_line->text() != tableModel->index(i, 5).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
        if(!ui->Num_line->text().isEmpty() && ui->Num_line->text() != tableModel->index(i, 6).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
        if(ui->checkBox->isChecked() && ui->dateEdit->text() != tableModel->index(i, 7).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
        if(!ui->gender_line->text().isEmpty() && ui->gender_line->text() != tableModel->index(i, 9).data().toString()){
            table->setRowHidden(i, true);
            continue;
        }
    }
    emit need_refresh();
}
