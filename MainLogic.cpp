#include "mainlogic.h"

MainLogic::MainLogic(QWidget *parent)
    : QWidget(parent)
{
    m_loginLogic = new LoginLogic;
    m_mainWidgetLogic = new MainWidgetLogic();
    m_networkLogic = new NetworkLogic();
    m_socket = new QTcpSocket();
    m_socket = m_networkLogic->getSocket();
    initLogic();
}

MainLogic::~MainLogic()
{

}

/**
 * @brief MainLogic::initLogci 初始化程序逻辑
 */
void MainLogic::initLogic()
{
    m_loginLogic->showLoginWidget();

    /// 监听socket
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(slotRecvFromSocket()));

    /// 网络发送用户名和密码验证消息
    connect(m_loginLogic, SIGNAL(signalTestUidAndPassword(int)),
            this, SLOT(slotTestUidAndPasswd(int)));

    /** 登陆-主界面*/
    connect(m_loginLogic, SIGNAL(signalOpenMainWidget()),
            this, SLOT(slotOpenMainWidget()));

    connect(m_mainWidgetLogic, SIGNAL(signalSendMsgToOthers(Msg*)),
            this, SLOT(slotSendMsgToOthers(Msg*)));
}
/**
 * @brief MainLogic::slotTestUidAndPasswd
 * 验证用户名和密码-通过网络发送给服务器验证
 */
void MainLogic::slotTestUidAndPasswd(int flag)
{
    QString loginName = m_loginLogic->getLoginName();
    QString loginPasswd = m_loginLogic->getLoginPasswd();
    qDebug() << "slotTestUidAndPasswd()" << "uid:" << loginName << "passwd:" << loginPasswd << endl;
    if(flag == enum_LOGIN)
    {
        m_networkLogic->testUidAndPassword(loginName, loginPasswd);
    }
    else if(flag == enum_REGST)
    {
        m_networkLogic->registUidAndPassword(loginName, loginPasswd);
    }

}

/**
 * @brief MainLogic::answerLogin
 * @param recvMsg 从网络收到的原始数据
 * 服务器应答登陆情况 返回给登陆模块
 */
void MainLogic::answerLogin(NetworkProtocol *recvMsg)
{
    m_loginLogic->testLogin(recvMsg->getPackData());
}

/**
 * @brief MainLogic::NewUserLogin
 * @param recvMsg 从网络接受的原始数据
 * 交由主界面处理新用户登陆的情况
 */
void MainLogic::newUserLogin(NetworkProtocol *recvMsg)
{
    m_mainWidgetLogic->newUserLogin(recvMsg->getPackData());
}

/**
 * @brief MainLogic::newMessage
 * @param recvMsg 从网络接受的原始数据
 * 交由主界面处理新消息的情况
 */
void MainLogic::newMessage(NetworkProtocol *recvMsg)
{
    m_mainWidgetLogic->newMessage(recvMsg->getPackData(), recvMsg->getPackSend());
}

/**
 * @brief MainLogic::slotOpenMainWidget
 * 打开主界面
 */
void MainLogic::slotOpenMainWidget()
{
    QString uid = m_loginLogic->getLoginName();
    m_mainWidgetLogic->showMainWidget(uid);
}

void MainLogic::slotSendMsgToOthers(Msg *msg)
{
    NetworkProtocol *pack = new NetworkProtocol(enum_ptp, msg->getMsg(),
                                                msg->getRecvUser(), msg->getSendUser());
    m_networkLogic->sendData(pack);
}

void MainLogic::slotFlushProgram()
{
    m_networkLogic->closeSocket();
}

void MainLogic::slotRecvFromSocket()
{
    NetworkProtocol *pack = m_networkLogic->getRecvPack();
    qDebug() << * pack->printClass();
    switch(pack->getPackHead())
    {
    case enum_login:
        answerLogin(pack); // 返回登录信息
        break;
    case enum_regis:
//        answerResig(pack); // 返回注册信息
        break;
    case enum_ptp:
        newMessage(pack); // 个人发送给个人
        break;
    case enum_new_user_login:
        newUserLogin(pack); // 新用户登陆
        break;
    default:
        break;
    }
}
