#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QTcpSocket *s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    socket = s;
}

Chat::~Chat()
{
    delete ui;
}


//清空
void Chat::on_clearButton_clicked()
{
    ui->lineEdit->clear();
}
//发送
void Chat::on_sendButton_clicked()
{
    QByteArray ba;
    ba.append(ui->lineEdit->text());
//    ui->lineEdit->text(); //获取文本框内容
    socket->write(ba);  //发送
}
