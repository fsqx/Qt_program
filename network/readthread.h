#ifndef READTHREAD_H
#define READTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QTcpSocket>
#include <QStringList>
#include <QMap>
#include "networkprotocol.h"





class ReadThread : public QThread
{
    Q_OBJECT
public:
    ReadThread(QTcpSocket &socket);
    ~ReadThread();
    void initQMap();

signals:
    void signalRecvLogin(QString loginData);
    void signalRecvRegis(const QString regisData);
    void signalRecvPersonToPerson(const QString msgData, const QString sendUser);
    void signalRecvPersonToALL(const QString msgData, const QString sendUser);
    void signalRecvNewUserLogin(const QString userName);
public slots:
    void slotReadyRead();

protected:
    void run();

private:
    QTcpSocket *m_socket;
    QMap<QString, int> m_mapStringVal;
};

#endif // READTHREAD_H
