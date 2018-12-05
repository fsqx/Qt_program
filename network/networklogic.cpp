#include "networkLogic.h"
#include <QDebug>

NetworkLogic::NetworkLogic(QWidget *parent)
    : QWidget(parent)
{
    m_netAddress = "127.0.0.1";
    m_port = QString::number(8000);
    m_socket = new QTcpSocket();
}

NetworkLogic::~NetworkLogic()
{
    delete m_socket;
}

void NetworkLogic::testUidAndPassword(QString uid, QString passwd)
{
    NetworkProtocol *login = new NetworkProtocol(enum_login, passwd, QString(SERVER), uid);
    sendData(login);
//    delete login;
}

void NetworkLogic::registUidAndPassword(QString uid, QString passwd)
{
    initNetwork();
    NetworkProtocol *login = new NetworkProtocol(enum_regis, passwd, QString(SERVER), uid);
    sendData(login);
}

NetworkProtocol *NetworkLogic::getRecvPack()
{
    QString recvPack = QString(m_socket->readAll());
    NetworkProtocol *pack = new NetworkProtocol(recvPack);
    qDebug() << "getRecvPack()" << recvPack;
    return pack;
}

/// 初始化TCP连接
void NetworkLogic::initNetwork()
{
    m_socket->connectToHost(QHostAddress(QString(m_netAddress)), m_port.toInt());
    if(m_socket->waitForConnected())
    {
        /// 连接成功
        qDebug() << "connecting has been established.";
    }
    else
    {
        qDebug() << m_socket->error();
    }
    /// 监听socket有消息发来
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
}

void NetworkLogic::closeSocket()
{
    m_socket->close();
}

/// 发送
void NetworkLogic::sendData(NetworkProtocol *data)
{
    const char *send_buf = data->classToPtChar();
    qDebug() << data->getPackHead() << data->getPackData() << endl;
    qDebug() << "temp" << QString(send_buf);
    m_socket->write(send_buf);
    delete data;
}

QTcpSocket *NetworkLogic::getSocket()
{
    return m_socket;
}

/** ********** 信号和槽 ********** */

///** 从主界面获取发送的消息 */
//void NetworkLogic::slotRecvSendMsgFromMainWidget(Msg *msg)
//{
//    QString flag;
//    /// 处理发送个人和发送所有
//    if(recvUser == QString("all"))
//    {
//        flag = QString(PERSON2ALL);
//    }
//    else
//    {
//        flag = QString(PERSON2PERSON);
//    }

//    NetworkProtocol *msg = new NetworkProtocol(flag, msgData, recvUser, sendUser);
//    sendData(msg);
//    delete msg;
//}

/** 准备读取socket */
void NetworkLogic::slotReadyRead()
{

}
