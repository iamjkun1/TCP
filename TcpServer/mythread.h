#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
class myThread :  public QThread
{
    Q_OBJECT
public:
    explicit myThread(QTcpSocket *s);
    void run();   //线程处理函数

signals:
    void sendToWidget(QByteArray b);  //自定义信号，用来输出信息

public slots:  //槽函数权限不限制,私有公有都行
    void clientInfoSlot();  //处理客户端的槽函数


private:
    QTcpSocket *socket;
};

#endif // MYTHREAD_H
