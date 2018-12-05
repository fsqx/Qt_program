#include "readThread.h"

ReadThread::ReadThread(QTcpSocket &socket)
{
    m_socket = new QTcpSocket;
    this->m_socket = &socket;
    initQMap();
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
}

ReadThread::~ReadThread()
{

}

void ReadThread::run()
{

}

void ReadThread::initQMap()
{
    m_mapStringVal[QString(LOGIN)] = enum_login;
    m_mapStringVal[QString(REGISTER)] = enum_regis;
    m_mapStringVal[QString(PERSON2PERSON)] = enum_ptp;
    m_mapStringVal[QString(PERSON2ALL)] = enum_pta;
    m_mapStringVal[QString(NEW_USER_LOGIN)] = enum_new_user_login;
}

void ReadThread::slotReadyRead()
{
    QString recvBuf;
    recvBuf = QString(m_socket->readAll());
    NetworkProtocol *readBuf = new NetworkProtocol(recvBuf);

    switch(m_mapStringVal[readBuf->getPackHead()])
    {
    case enum_login:
        emit signalRecvLogin(readBuf->getPackData());
        break;
    case enum_regis:
        emit signalRecvRegis(readBuf->getPackData());
        break;
    case enum_ptp:
        emit signalRecvPersonToPerson(readBuf->getPackData(), readBuf->getPackSend());
        break;
    case enum_pta:
        emit signalRecvPersonToALL(readBuf->getPackData(), readBuf->getPackSend());
        break;
    case enum_new_user_login:
        emit signalRecvNewUserLogin(readBuf->getPackData());
        break;
    default:
        break;
    }
}
