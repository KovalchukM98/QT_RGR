#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->info_action, SIGNAL(triggered()), this, SLOT(info_clicked()));
    connect(ui->new_action, SIGNAL(triggered()), this, SLOT(new_clicked()));
    connect(ui->save_action, SIGNAL(triggered()), this, SLOT(save_clicked()));
    connect(ui->open_action, SIGNAL(triggered()), this, SLOT(open_clicked()));
    connect(ui->exit_action, SIGNAL(triggered()), this, SLOT(exit_clicked()));

    connect(ui->day_action, SIGNAL(triggered()), this, SLOT(day_clicked()));
    connect(ui->delete_action, SIGNAL(triggered()), this, SLOT(delete_clicked()));
    connect(ui->add_action, SIGNAL(triggered()), this, SLOT(add_clicked()));
    connect(ui->search_action, SIGNAL(triggered()), this, SLOT(search_clicked()));
    connect(ui->change_action, SIGNAL(triggered()), this, SLOT(change_clicked()));
    connect(ui->reset_action, SIGNAL(triggered()), this, SLOT(reset_clicked()));

    ui->tableView->setModel(tableModel);

    query = new QSqlQuery;
    add_form = new Add_form();
    add_form->hide();
    connect(add_form, SIGNAL(need_refresh()), this, SLOT(RefreshTable()));

    search_f = new search_form();
    search_f->hide();
    connect(search_f, SIGNAL(need_refresh()), this, SLOT(RefreshTable()));
    connect(search_f, SIGNAL(need_reset()), this, SLOT(reset_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if(database.isOpen()){
        database.close();
    }
    delete query;
    delete add_form;
}

void MainWindow::RefreshTable(){
    if(tableModel != nullptr){
        delete tableModel;
    }
    tableModel = new QSqlTableModel(this, database);
    tableModel->setTable("tab");
    //tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableModel->select();
    ui->tableView->setModel(tableModel);
    if(search_f != nullptr){
        search_f->connect_window(tableModel, ui->tableView);
    }
}

void MainWindow::open_clicked(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QFileDialog::getOpenFileName(0, tr("Открыть файл"), QDir::currentPath()));
    if (!database.open())
    {
        QMessageBox::warning( 0 , "Ошибка!", database.lastError().databaseText());
    }
    if(query != nullptr){
        delete query;
    }
    query = new QSqlQuery(database);
    if(tableModel != nullptr){
        delete tableModel;
    }
    add_form->connect_database(query);
    RefreshTable();
}

void MainWindow::new_clicked(){
    if(database.isOpen()){
        database.close();
    }
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("/database.db");
    if (!database.open())
         {
             QMessageBox::warning( 0 , "Ошибка!", database.lastError().databaseText());
         }
    if(query != nullptr){
        delete query;
    }
    query = new QSqlQuery(database);
    query->exec("CREATE TABLE tab(Код INTEGER PRIMARY KEY AUTOINCREMENT,"
                "Наименование TEXT,"
                "Размер INTEGER,"
                "Производитель TEXT,"
                "Поставщик TEXT NOT NULL,"
                "Цена INTEGER,"
                "Наличие INTEGER,"
                "Дата TEXT,"
                "Фото TEXT,"
                "Пол TEXT)");

    //QMessageBox::warning( 0 , "создание новой таблицы!"," ");
//    if(!query->exec("INSERT INTO tab(Наименование, Размер, Производитель, Поставщик, Цена , Наличие, Дата, Фото, Пол) VALUES ('1', '2', '3', '4', '5', '6', '7', '8', '9');")){
//        QMessageBox::warning( 0 , "Ошибка!", query->lastError().databaseText());
//    }
    add_form->connect_database(query);
    RefreshTable();
}

//????????????????
void MainWindow::save_clicked(){
    QString path = QFileDialog::getSaveFileName(0, tr("Сохранить файл"), QDir::currentPath());
    QSqlDatabase clone;
    database.cloneDatabase(clone, path);
    clone.close();
    database.close();
    database.setDatabaseName(path);
    database.open();
    query = new QSqlQuery(database);
    RefreshTable();
}

void MainWindow::info_clicked(){
    if(faq_form == nullptr){
        faq_form = new Faq_form();
    }
    faq_form->show();
}

void MainWindow::exit_clicked(){
    this->close();
}

void MainWindow::day_clicked(){
    if(day_form != nullptr){
        delete day_form;
    }
    day_form = new Day_form(database);
    day_form->show();
}

void MainWindow::delete_clicked(){
    tableModel->removeRow(ui->tableView->currentIndex().row());
    RefreshTable();
}

void MainWindow::add_clicked(){
    if(add_form->query != query){
        add_form->query = query;

    }
    add_form->code = -1;
    add_form->change = false;
    add_form->show();
}

void MainWindow::change_clicked(){
    int row = ui->tableView->currentIndex().row();
    add_form->code = tableModel->index(row, 0).data().toInt();
    add_form->prepare(tableModel->index(row, 1).data().toString(), tableModel->index(row, 2).data().toString(),
                      tableModel->index(row, 3).data().toString(), tableModel->index(row, 4).data().toString(),
                      tableModel->index(row, 5).data().toInt(), tableModel->index(row, 6).data().toInt(),
                      tableModel->index(row, 7).data().toString(), tableModel->index(row, 8).data().toString(),
                      tableModel->index(row, 9).data().toString());
    add_form->change = true;
    add_form->show();
}

void MainWindow::reset_clicked(){
    for(int i = 0; i < tableModel->rowCount(); ++i){
        ui->tableView->setRowHidden(i, false);
    }
    RefreshTable();
}

void MainWindow::search_clicked(){
    search_f->connect_window(tableModel, ui->tableView);
    search_f->show();
}
