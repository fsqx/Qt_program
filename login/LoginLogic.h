#ifndef LOGINLOGIC_H
#define LOGINLOGIC_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "LoginWidget.h"

#define SUCCESS "Login Success"
#define PASSWD_ERROR "password error"
#define UNREGISTUSER "unregist user"

class LoginLogic : public QWidget
{
    Q_OBJECT

public:
    LoginLogic();
    ~LoginLogic();

    // 显示登陆界面
    void showLoginWidget(void);
    // 显示主界面
    void showMainWidget(void);
    // 获取登陆UID
    QString getLoginName();
    // 获取登陆密码
    QString getLoginPasswd();
    // 验证登陆情况
    void testLogin(QString loginData);

signals:
    // 发送UID和密码给网络模块
    void signalTestUidAndPassword(int);
    // 清空界面输入
    void signalClearLoginWidget(void);
    // 发送打开信号给主界面
    void signalOpenMainWidget();
    // 登陆失败，重新初始化
    void signalLoginFail(void);

public slots:
    // 获得界面上的UID和密码
    void slotGetUidAndPasswd(int flag);
    // 获取登陆信息从网络模块

    // 获取注册信息从网络模块
    void slotRecvRegisMsgFromNetwork(const QString regisData);
private:
    QString m_uid; // 用户名

    QString m_passwd; // 密码

    LoginWidget *m_loginWidget; // 登陆界面
};

#endif // LOGINLOGIC_H
