#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <mythread.h>
#define PORT 8000
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
        void newClientHandler();  //处理连接功能的槽函数
//        void clientInfoSlot();   //客户端消息的槽函数
        void threadSlot(QByteArray b);  //线程槽函数

private:
    Ui::Widget *ui;
    QTcpServer *server;
};
#endif // WIDGET_H
