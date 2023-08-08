#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new QTcpServer;  //创建服务器对象

    server->listen(QHostAddress::AnyIPv4, PORT);  //自己电脑测试局域网

    //客户端发起连接，server发出信号
    connect(server, &QTcpServer::newConnection, this, &Widget::newClientHandler);

}

Widget::~Widget()
{
    delete ui;
}
///处理连接功能  创建TCP连接
void Widget::newClientHandler(){
    //建立TCP连接
    QTcpSocket *socket = server->nextPendingConnection();
    //用nextPendingConnection 连接客户端和服务器

    //输出地址，端口
    socket->peerAddress();  //获取客户端地址
    socket->peerPort();  //获取端口号,不是服务器端口8000

    ui->ipLineEdit->setText(socket->peerAddress().toString());
    ui->portLineEdit->setText(QString::number(socket->peerPort()));

//     //单线程
//    //服务器收到客户端发送的信息,socket 发出readyread 信号
//    connect(socket, &QTcpSocket::readyRead, this, &Widget::clientInfoSlot);

    //启动多线程
    myThread *t = new myThread(socket);   //创建线程对象,同时把局部变量传过去
    t->start();  //开始线程

    connect(t, &myThread::sendToWidget, this, &Widget::threadSlot);
}

////单线程
////接收信息处理函数
//void Widget::clientInfoSlot(){  //收到信号才会触发槽函数
//    //获取信号的发出者
//    QTcpSocket *s = (QTcpSocket *)sender();  //调用sender() 可以获取谁发出的信号
//    //上一行代码说明都指向TCP连接对象

//    ui->mainLineEdit->setText(QString(s->readAll()));  //显示在对话框内
////    QString (s->readAll());  //把所有信息读出来
//}

void Widget::threadSlot(QByteArray b){
     ui->mainLineEdit->setText(QString(b));
}
