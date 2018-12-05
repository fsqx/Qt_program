#ifndef NETWORKLOGIC_H
#define NETWORKLOGIC_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include "networkprotocol.h"
#include "readThread.h"
#include "mainWidget/Msg.h"

#define NETWORK_ADDRESS "127.0.0.1"
#define PORT 8000

enum MessageFlag{enum_login = 0x10,
                 enum_regis,
                 enum_ptp,
                 enum_new_user_login };

class NetworkLogic : public QWidget
{
    Q_OBJECT

public:

    NetworkLogic(QWidget *parent = 0);
    ~NetworkLogic();
    // 初始化网络模块
    void initNetwork();
    // 关闭socket连接
    void closeSocket();
    // 向服务器发送消息
    void sendData(NetworkProtocol *data);
    // 验证密码
    void testUidAndPassword(QString uid, QString passwd);
    // 注册账号
    void registUidAndPassword(QString uid, QString passwd);
    // 获得读取的消息
    NetworkProtocol *getRecvPack();
    // 获取socket
    QTcpSocket *getSocket();

public slots:

    // 从主界面获得发送的消息
//    void slotRecvSendMsgFromMainWidget(const QString msgData,
//                                       const QString recvUser, const QString sendUser);
    // 准备读取消息
    void slotReadyRead();

signals:
//    // 发送登陆消息给登陆模块
//    void signalSendLoginMsgToLogin(const QString loginData);
//    // 发送注册消息给登陆模块
//    void signalSendRegisMsgToLogin(const QString regisData);

    // 新用户登陆
    void signalNewUserLogin(NetworkProtocol *recvMsg);
    // 应答登陆消息
    void signalAnswerLogin(NetworkProtocol *recvMsg);
    // 应答注册消息
    void signalAnswerRegis(NetworkProtocol *recvMsg);
    // 发送消息
    void signalNewMessage(NetworkProtocol *recvMsg);

private:
    QTcpSocket *m_socket; // socket连接

    QString m_netAddress;

    QString m_port;
};

#endif // NETWORKLOGIC_H
