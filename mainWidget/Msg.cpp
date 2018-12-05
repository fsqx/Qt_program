#include "Msg.h"

Msg::Msg(const QString &sendUser , const QString &recvUser,
         const QString &msg , const QString recvTime )
{
    m_sendUser = sendUser;
    m_recvUser = recvUser;
    m_msg = msg;
    m_recvTime = recvTime;
}

const QString Msg::getSendUser()
{
    return m_sendUser;
}

const QString Msg::getRecvTime()
{
    return m_recvTime;
}

const QString Msg::getRecvUser()
{
    return m_recvUser;
}

const QString Msg::getMsg()
{
    return m_msg;
}

void Msg::setSendUser(const QString &sendUser)
{
    m_sendUser = sendUser;
}

void Msg::setRecvUser(const QString &recvUser)
{
    m_recvUser = recvUser;
}

void Msg::setMsg(const QString &msg)
{
    m_msg = msg;
}

void Msg::setRecvTime(const QString &recvTime)
{
    m_recvTime = recvTime;
}

