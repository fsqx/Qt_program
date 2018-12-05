#include "LoginLogic.h"

LoginLogic::LoginLogic()
{
    m_loginWidget = new LoginWidget();
    /// 接受界面获取的用户名和密码
    connect(m_loginWidget, SIGNAL(signalSendUidAndPassword(int)), this, SLOT(slotGetUidAndPasswd(int)));

    /// 清空界面
    connect(this, SIGNAL(signalClearLoginWidget()), m_loginWidget, SLOT(slotClearLoginWidget()));
}

LoginLogic::~LoginLogic()
{
    delete m_loginWidget;
}

/** 显示主界面 */
void LoginLogic::showMainWidget()
{
    emit signalOpenMainWidget();
}

/** 显示登录界面 */
void LoginLogic::showLoginWidget()
{
    m_loginWidget->show();
}

QString LoginLogic::getLoginName()
{
    return m_uid;
}

QString LoginLogic::getLoginPasswd()
{
    return m_passwd;
}

/** 验证登陆 */
void LoginLogic::testLogin(QString loginData)
{
    if(loginData == QString(SUCCESS))
    {
        // QMessageBox 弹出消息框确认消息

        QMessageBox *msgBox;
        msgBox = new QMessageBox("登陆",		///--这里是设置消息框标题
                                 "登陆成功！",						///--这里是设置消息框显示的内容
                                 QMessageBox::Information,							///--这里是在消息框显示的图标
                                 QMessageBox::Ok | QMessageBox::Default,		///---这里是显示消息框上的按钮情况
                                 0, 0);
        msgBox->show();
        m_loginWidget->close();
        this->showMainWidget();
        return;
    }

    else if(loginData == QString(PASSWD_ERROR))
    {
        // QMessageBox 弹出消息框确认消息
        QMessageBox *msgBox;
        msgBox = new QMessageBox("登陆",		///--这里是设置消息框标题
                                 "登陆失败！密码错误。",						///--这里是设置消息框显示的内容
                                 QMessageBox::Information,							///--这里是在消息框显示的图标
                                 QMessageBox::Ok | QMessageBox::Default,		///---这里是显示消息框上的按钮情况
                                 0, 0);
        msgBox->show();
        emit signalLoginFail();
    }

    else
    {

    }
}
/** ******** 信号和槽 ******** */

/** 获取用户名和密码*/
void LoginLogic::slotGetUidAndPasswd(int flag)
{
    m_uid = m_loginWidget->getInputUid();
    m_passwd = m_loginWidget->getInputPasswd();
    qDebug() << "slotGetUidAndPasswd()" << "uid:" << m_uid << "passwd:" << m_passwd << endl;
    emit signalTestUidAndPassword(flag);
}



/** 注册 */
void LoginLogic::slotRecvRegisMsgFromNetwork(const QString regisData)
{
    if(regisData == QString("success"))
    {

    }

}
