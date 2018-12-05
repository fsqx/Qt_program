#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>
#include <QWidget>
#include <QString>

/** pack_head--消息类型 */
#define LOGIN "Login" // 登陆
#define REGISTER "Regis" // 注册
#define PERSON2PERSON "P2P" // 个人发送至个人
#define PERSON2ALL "P2A" // 个人发送至所有人
#define NEW_USER_LOGIN "Nulogin" // 新用户登陆

/** pack_recv--消息接受者*/
#define SERVER "Server" // 服务器
#define ALL "All" // 所有人

class NetworkProtocol: public QWidget
{
    Q_OBJECT

public:

    NetworkProtocol(int pack_head, QString pack_data,
                    QString pack_recv = "", QString pack_send = "");

    /// 接受字符串，切割处理
    NetworkProtocol(QString recvBuf);

    /// 返回数据
    int getPackHead();

    QString getPackRecv();

    QString getPackData();

    QString getPackSend();

    const char *classToPtChar();

    QString *printClass();

private:
    int pack_head; // 消息类型

    QString pack_recv; // 接受者

    QString pack_data; // 消息内容

    QString pack_send; // 发送者

    QString send_buf;

    std::string str;
};

#endif // NETWORKPROTOCOL_H
