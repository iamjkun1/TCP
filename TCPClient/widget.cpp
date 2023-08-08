#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket = new QTcpSocket;  //在构造函数里，创建scoket对象
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_cancelButton_clicked()
{
    this->close();
}

void Widget::on_connectButton_clicked()
{
    //获取ip地址和端口号
    QString IP = ui->ipLineEdit->text(); //获取文本框内容,最终string 类型转换为：QHostAddress类型
    QString port = ui->portLineEdit->text(); //获取端口号

    //debug
    qDebug()<<IP;
    qDebug()<<port;

    //连接服务器
    socket->connectToHost(QHostAddress(IP), port.toShort());

    //当连接服务器成功，socket对象会发出信号
    connect(socket, &QTcpSocket::connected, [this](){
        QMessageBox::information(this, "连接提示", "连接服务器成功");
        //弹出对话框

        this->hide();  //把当前界面隐藏掉

        Chat *c = new Chat(socket);  //在堆上创建对象，这样就不会像在栈上创建局部变量一样消失
        c->show();  //显示新的对话框
    });

    //连接异常，socket会发出信号
    connect(socket, &QTcpSocket::disconnected, [this](){
        QMessageBox::warning(this, "连接提示","连接异常，网络断开");
    });
}
