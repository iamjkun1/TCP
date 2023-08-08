#include "mythread.h"

myThread::myThread(QTcpSocket *s)
{
    socket = s;
}

void myThread::run(){  //重写run()函数

     connect(socket, &QTcpSocket::readyRead, this, &myThread::clientInfoSlot);

}



void myThread::clientInfoSlot(){
////    //接收信息
////    socket->readAll();  //把消息读出来
////    //打印消息//不能在其他类里面操作界面,就是不能显示信息在其他窗口

//       qDebug()<<socket->readAll();
    QByteArray ba = socket->readAll();  //先在线程读数据
    emit sendToWidget(ba);  //发送信号



}
