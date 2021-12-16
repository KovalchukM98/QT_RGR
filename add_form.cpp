#include "add_form.h"
#include "ui_add_form.h"

Add_form::Add_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_form)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ok_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(cancel_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(open_photo()));

    query = new QSqlQuery;
    ui->dateEdit->setDate(QDate::currentDate());
    ui->photo_line->hide();
}

Add_form::Add_form(QSqlDatabase db) : ui(new Ui::Add_form){
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ok_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(cancel_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(open_photo()));

    query = new QSqlQuery(db);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->photo_line->hide();
}

Add_form::~Add_form()
{
    delete ui;
    if(query != nullptr){
        query->finish();
        delete query;
    }
}

void Add_form::connect_database(QSqlQuery *db){
    if(query != nullptr){
        delete query;
    }
    query = db;
}

void Add_form::open_photo(){
    QString filename = QFileDialog::getOpenFileName(0, "Выберите изображение", "D:/Qt_lab/", "*.png *.jpg *.gif *.jpeg");
    ui->photo_line->setText(filename);
    QImage image(filename);
    QPixmap pix = QPixmap::fromImage(image);
    ui->photo_label->setPixmap(pix.scaled(ui->photo_label->width(), ui->photo_label->height(), Qt::KeepAspectRatio));
}

void Add_form::cancel_clicked(){
    ui->Name_line->clear();
    ui->Size_line->clear();
    ui->Manufacturer_line->clear();
    ui->Provider_line->clear();
    ui->Cost_line->clear();
    ui->Num_line->clear();
    ui->photo_line->clear();
    ui->gender_line->clear();
    hide();
}

void Add_form::prepare(QString name, QString size, QString man, QString transf,
                       int cost, int num, QString date, QString photo, QString sex){
    if(code < 0){
        return;
    }
    ui->Name_line->setText(name);
    ui->Size_line->setText(size);
    ui->Manufacturer_line->setText(man);
    ui->Provider_line->setText(transf);
    ui->Cost_line->setText(QString::number(cost));
    ui->Num_line->setText(QString::number(num));
    int day = (date[0].unicode() - '0')*10 + (date[1].unicode() - '0');
    int mon = (date[3].unicode() - '0')*10 + (date[4].unicode() - '0');
    int year = (date[6].unicode() - '0')*1000 + (date[7].unicode() - '0')*100 + (date[8].unicode() - '0')*10 + (date[9].unicode() - '0');
    QDate d;
    d.setDate(year, mon, day);
    ui->dateEdit->setDate(d);
    ui->photo_line->setText(photo);
    QImage image(photo);
    QPixmap pix = QPixmap::fromImage(image);
    ui->photo_label->setPixmap(pix.scaled(ui->photo_label->width(), ui->photo_label->height(), Qt::KeepAspectRatio));

    ui->gender_line->setText(sex);
}

void Add_form::ok_clicked(){
    if(query == nullptr){
        return;
    }
    if(ui->Name_line->text().isEmpty() || ui->Provider_line->text().isEmpty() || ui->Num_line->text().isEmpty()){
        QMessageBox::warning(this, "Ошибка!", "не заполнены ключевые поля");
        return;
    }
    if(change){
        query->prepare("UPDATE tab SET Наименование = :name, Размер = :size, Производитель = :made, Поставщик = :transfer, Цена = :cost , Наличие = :num , Дата = :date, Фото = :photo, Пол = :sex WHERE Код = :id;");
        query->bindValue(":id", code);
    }
    else{
        query->prepare("INSERT INTO tab(Наименование, Размер, Производитель, Поставщик, Цена , Наличие , Дата, Фото, Пол) VALUES (:name , :size, :made, :transfer, :cost, :num, :date, :photo, :sex);");
    }
    query->bindValue(":name", ui->Name_line->text());
    query->bindValue(":size", ui->Size_line->text());
    query->bindValue(":made", ui->Manufacturer_line->text());
    query->bindValue(":transfer", ui->Provider_line->text());
    query->bindValue(":cost", ui->Cost_line->text());
    query->bindValue(":num", ui->Num_line->text());
    query->bindValue(":date", ui->dateEdit->text());
    query->bindValue(":photo", ui->photo_line->text());
    query->bindValue(":sex", ui->gender_line->text());

    if(!query->exec()){
        //qDebug() << "Unable to add in table: " << query->lastError();
    }

    ui->Name_line->clear();
    ui->Size_line->clear();
    ui->Manufacturer_line->clear();
    ui->Provider_line->clear();
    ui->Cost_line->clear();
    ui->Num_line->clear();
    ui->photo_line->clear();
    ui->gender_line->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    emit need_refresh();
    hide();
}
