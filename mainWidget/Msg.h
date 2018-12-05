#ifndef MSG_H
#define MSG_H
#include <QString>


class Msg
{
public:
    Msg(const QString &sendUser = "", const QString &recvUser = "",
        const QString &msg = "", const QString recvTime = "");

    void setSendUser(const QString &sendUser);
    void setRecvUser(const QString &recvUser);
    void setMsg(const QString &msg);
    void setRecvTime(const QString &recvTime);

    const QString getSendUser();
    const QString getRecvUser();
    const QString getMsg();
    const QString getRecvTime();

private:
    QString m_sendUser; // 发送者
    QString m_recvUser; // 接受者
    QString m_msg; // 消息
    QString m_recvTime; // 收到消息的时间
};

#endif // MSG_H
