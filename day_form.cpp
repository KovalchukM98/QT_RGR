#include "day_form.h"
#include "ui_day_form.h"

Day_form::Day_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Day_form)
{
    ui->setupUi(this);
}

Day_form::Day_form(QSqlDatabase db) :
    ui(new Ui::Day_form)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    tableModel = new QSqlTableModel(this, db);
    tableModel->setTable("tab");
    //tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableModel->select();
    ui->tableView->setModel(tableModel);

    connect(ui->Search_Button, SIGNAL(clicked()), this, SLOT(search_clicked()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close_clicked()));

    ui->cost_line->setEnabled(false);
    ui->total_line->setEnabled(false);
    ui->found_line->setEnabled(false);
}

Day_form::~Day_form()
{
    delete ui;
    if(query != nullptr){
        query->finish();
        delete query;
    }
    if(tableModel != nullptr){
        delete tableModel;
    }
}

void Day_form::close_clicked(){
    this->close();
}

void Day_form::search_clicked(){
    QString date = ui->dateEdit->text();
//    QString tmp = date;
//    date[0] = tmp[6];
//    date[1] = tmp[7];
//    date[2] = tmp[8];
//    date[3] = tmp[9];
//    date[4] = date[7] = '-';
//    date[5] = tmp[3];
//    date[6] = tmp[4];
//    date[8] = tmp[0];
//    date[9] = tmp[1];
    //query->prepare("SELECT * FROM tab WHERE Дата=" + date);
    int cnt = 0;
    int total_cost = 0;
    int total_num = 0;
    for(int i = 0; i < tableModel->rowCount(); ++i){
        if(date != tableModel->index(i, 7).data().toString()){
            ui->tableView->setRowHidden(i, true);
        }
        else{
            cnt++;
            total_num += tableModel->index(i, 6).data().toInt();
            total_cost += tableModel->index(i, 6).data().toInt() * tableModel->index(i, 5).data().toInt();
        }
    }
    ui->cost_line->setText(QString::number(total_cost));
    ui->found_line->setText(QString::number(cnt));
    ui->total_line->setText(QString::number(total_num));
}
