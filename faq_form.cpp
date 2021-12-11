#include "faq_form.h"
#include "ui_faq_form.h"

Faq_form::Faq_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Faq_form)
{
    ui->setupUi(this);
    connect(ui->close_button, SIGNAL(clicked()), this, SLOT(close_clicked()));
    connect(ui->author_button, SIGNAL(clicked()), this, SLOT(author_clicked()));
    connect(ui->operation_button, SIGNAL(clicked()), this, SLOT(operation_clicked()));
    connect(ui->day_button, SIGNAL(clicked()), this, SLOT(day_clicked()));
    connect(ui->search_button, SIGNAL(clicked()), this, SLOT(search_clicked()));
    ui->textEdit->setText("Добро пожаловать в справку! выберите нужный вам пункт");
    ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

Faq_form::~Faq_form()
{
    delete ui;
}

void Faq_form::close_clicked(){
    close();
}

void Faq_form::author_clicked(){
    ui->textEdit->setText("Ковальчу М.С ИП-912");
    ui->label->clear();
    ui->label_2->clear();
}

void Faq_form::operation_clicked(){
    QFile file(path + "operation.txt");
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning( 0 , "Ошибка!", "файл не найден");
    }
    else{
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream.flush();
        ui->textEdit->setText(stream.readAll());
        file.close();
    }
    QImage img1(path + "operation1.png");
    QPixmap pix = QPixmap::fromImage(img1);
    ui->label->setPixmap(pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));

    QImage img2(path + "operation2.png");
    pix = QPixmap::fromImage(img2);
    ui->label_2->setPixmap(pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));
}

void Faq_form::day_clicked(){
    QFile file(path + "day.txt");
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning( 0 , "Ошибка!", "файл не найден");
    }
    else{
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream.flush();
        ui->textEdit->setText(stream.readAll());
        file.close();
    }
    QImage img1(path + "day1.png");
    QPixmap pix = QPixmap::fromImage(img1);
    ui->label->setPixmap(pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));

    QImage img2(path + "day2.png");
    pix = QPixmap::fromImage(img2);
    ui->label_2->setPixmap(pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));
}

void Faq_form::search_clicked(){
    QFile file(path + "search.txt");
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning( 0 , "Ошибка!", "файл не найден");
    }
    else{
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream.flush();
        ui->textEdit->setText(stream.readAll());
        file.close();
    }
    QImage img1(path + "search1.png");
    QPixmap pix = QPixmap::fromImage(img1);
    ui->label->setPixmap(pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));

    QImage img2(path + "search2.png");
    pix = QPixmap::fromImage(img2);
    ui->label_2->setPixmap(pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));
}
