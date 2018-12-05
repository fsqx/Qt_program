#ifndef MAINLOGIC_H
#define MAINLOGIC_H

#include <QWidget>
#include <QTcpSocket>
#include "login/LoginLogic.h"
#include "login/LoginWidget.h"
#include "mainWidget/MainWidget.h"
#include "mainWidget/MainWidgetLogic.h"
#include "mainWidget/Msg.h"
#include "network/networklogic.h"
#include "network/networkprotocol.h"

class MainLogic : public QWidget
{
    Q_OBJECT

public:
    MainLogic(QWidget *parent = 0);
    ~MainLogic();

    void initLogic(); // 初始化程序逻辑

    void answerLogin(NetworkProtocol *recvMsg);

    void answerResig(NetworkProtocol *recvMsg);

    void newUserLogin(NetworkProtocol *recvMsg);

    void newMessage(NetworkProtocol *recvMsg);
public slots:
    void slotTestUidAndPasswd(int);

    void slotOpenMainWidget();

    void slotSendMsgToOthers(Msg *msg);

    void slotFlushProgram();



//    void slotSendMessage(Msg *msg);

    void slotRecvFromSocket();
private:
    LoginLogic *m_loginLogic; // 登录界面

    NetworkLogic *m_networkLogic; // 网络模块

    MainWidgetLogic *m_mainWidgetLogic; // 主界面

    QTcpSocket *m_socket;


};

#endif // MAINLOGIC_H
