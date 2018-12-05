#ifndef MAINWIDGETLOGIC_H
#define MAINWIDGETLOGIC_H

#include <QWidget>
#include <QList>
#include "MainWidget.h"
#include "Msg.h"
#include <QTime>
#include <QStringList>


class MainWidgetLogic : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidgetLogic(QWidget *parent = nullptr);
    // 显示主界面
    void showMainWidget(QString &uid);
    // 新用户登陆
    void newUserLogin(QString userName);
    // 新消息
    void newMessage(QString msg, QString sendName);

signals:
    // 显示主界面
    void signalShowMainWidget();
    // 在消息列表新增消息
    void signalShowNewMsgOnMainWidget(const QString msg, const QString sendUser, const QString currentTime);
    // 暂时没用-考虑删除
    void signalShowAllMsgOnMainWidget(const QString msg, const QString sendUser);
    // 在好友列表增加新用户
    void signalAddNewUserOnMainWidget(const QString newUser);
    // 发送消息给其他用户
    void signalSendMsgToOthers(Msg *msg);

public slots:
    // 打开主界面
    void slotOpenFromLogin(const QString userName);
    // 单人消息
//    void slotRecvMsgFromNetwork(const QString recvMsg, const QString sendUser);
    // 暂时没用
//    void slotRecvMsgToAllFromNetwork(const QString recvMsg, const QString sendUser);
    // 新用户登陆
//    void slotRecvNewUserLoginFromNetWork(const QString userName);
    // 当前聊天对象改变
    void slotFriendListChanged();
    // 发送消息给其他人
    void slotSendMsgToOther();

private:
    MainWidget *m_mainWidget; // 主界面

    QList<QList<Msg *> *> *m_msgList; // 保存此次聊天消息

    QStringList *m_userList; // 好友列表

    QString m_loginUser; // 当前登录用户

    QString m_currentChatUser; // 当前聊天对象

};

#endif // MAINWIDGETLOGIC_H
