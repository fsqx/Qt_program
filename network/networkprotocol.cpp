#include "networkProtocol.h"
#include <QDebug>

NetworkProtocol::NetworkProtocol(int pack_head, QString pack_data,
                                 QString pack_recv, QString pack_send)
{
    this->pack_head = pack_head;
    this->pack_recv = pack_recv;
    this->pack_data = pack_data;
    this->pack_send = pack_send;
}

NetworkProtocol::NetworkProtocol(QString recvBuf)
{
    QStringList readDataList;
    readDataList = recvBuf.split('#');
    this->pack_head = QString(readDataList.at(1)).toInt();
    this->pack_recv = readDataList.at(2);
    this->pack_data = readDataList.at(3);
    this->pack_send = readDataList.at(4);
}

int NetworkProtocol::getPackHead()
{
    return this->pack_head;
}

QString NetworkProtocol::getPackRecv()
{
    return this->pack_recv;
}

QString NetworkProtocol::getPackData()
{
    return this->pack_data;
}

QString NetworkProtocol::getPackSend()
{
    return this->pack_send;
}

QString *NetworkProtocol::printClass()
{
    QString *msg = new QString("[ \"" + QString::number(this->pack_head) + "\" \"" + this->pack_send + "\" \"" +
                               this->pack_recv + "\" \"" + this->pack_data + "\" ]");
    return msg;
}

const char *NetworkProtocol::classToPtChar()
{
    send_buf += "#" + QString::number(this->getPackHead()) + "#" + this->getPackRecv()
            + "#" + this->getPackData() + "#" + this->getPackSend() + "#";

    str = send_buf.toStdString();
    const char* aim_str = str.c_str();
    return aim_str;
}
