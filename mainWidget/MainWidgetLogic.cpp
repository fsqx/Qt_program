#include "MainWidgetLogic.h"
#include <QDebug>

MainWidgetLogic::MainWidgetLogic(QWidget *parent) : QWidget(parent)
{
    m_mainWidget = new MainWidget();
    m_msgList = new QList<QList<Msg *> *>;
    m_userList = new QStringList;

    /// 显示主聊天界面
//    connect(this, SIGNAL(signalShowMainWidget()),
//            m_mainWidget, SLOT(slotShowMainWidget()));
    /// 当前聊天对象改变
    connect(m_mainWidget, SIGNAL(signalFriendListChanged()),
            this, SLOT(slotFriendListChanged()));
//    /// 在界面显示新消息
//    connect(this, SIGNAL(signalShowNewMsgOnMainWidget(QString,QString,QString)),
//            m_mainWidget, SLOT(slotAddNewMsgOnMainWidget(QString,QString,QString)));
    /// 向其他用户发消息
    connect(m_mainWidget, SIGNAL(signalSendMsgToOther()),
            this, SLOT(slotSendMsgToOther()));
}

// 显示主界面
void MainWidgetLogic::showMainWidget(QString &uid)
{
    m_mainWidget->setWindowTitle(m_loginUser);
    m_loginUser = uid;
    m_mainWidget->showMainWidget();
}

// 新用户登陆
void MainWidgetLogic::newUserLogin(QString userName)
{

    qDebug() << userName << endl;
    if(m_currentChatUser == "")
    {
        m_currentChatUser = userName;
    }
    m_userList->append(userName);
    QList<Msg *> *tmp = new QList<Msg *>;
    m_msgList->append(tmp);
    m_mainWidget->addNewUserOnFriendList(userName);
}

// 显示新消息
void MainWidgetLogic::newMessage(QString msg, QString sendName)
{
    QTime currentTime = QTime::currentTime();
    Msg *tmpMsg = new Msg(sendName, this->m_loginUser, msg, currentTime.toString());
    int index = m_userList->indexOf(QString(sendName));
    qDebug() << index;
    if(index >= 0)
    {
        m_msgList->at(index)->append(tmpMsg);
        if(m_currentChatUser == sendName)
        {
            m_mainWidget->addNewMessageOnWidget(tmpMsg);
        }
    }

}
/** ******** 信号和槽 ******** */

/** 打开主界面 */
void MainWidgetLogic::slotOpenFromLogin(const QString userName)
{
    this->m_loginUser = userName;
    emit signalShowMainWidget();
}

///** 获取新消息-从网络模块 */
//void MainWidgetLogic::slotRecvMsgFromNetwork(const QString recvMsg, const QString sendUser)
//{

//}

///** 暂时没用 */
//void MainWidgetLogic::slotRecvMsgToAllFromNetwork(const QString recvMsg, const QString sendUser)
//{
//    emit signalShowAllMsgOnMainWidget(recvMsg, sendUser);
//}

///** 新用户登陆-从网络模块*/
//void MainWidgetLogic::slotRecvNewUserLoginFromNetWork(const QString userName)
//{

//}

/** 改变当前聊天对象 */
void MainWidgetLogic::slotFriendListChanged()
{
    if(m_mainWidget->getCurrentFriendListItem()->text() != m_currentChatUser)
    {
        m_currentChatUser = m_mainWidget->getCurrentFriendListItem()->text();
    }
    else
    {
        return;
    }
    // 更新消息列表
    int index = m_userList->indexOf(m_currentChatUser);
    if(index >= 0)
    {
        QList<Msg *> *tmp = m_msgList->at(index);
        m_mainWidget->flushMessageWidget(tmp);
    }
}

/** 发送消息给其他用户 */
void MainWidgetLogic::slotSendMsgToOther()
{
    QString msg = m_mainWidget->getInputMsg();
    qDebug() << "slotSendMsgToOther()" << msg;
    int index = m_userList->indexOf(m_currentChatUser);
    Msg *tmpMsg = new Msg(m_loginUser, m_currentChatUser, msg, QTime::currentTime().toString());
    m_msgList->at(index)->append(tmpMsg);
    emit signalSendMsgToOthers(tmpMsg);
}



