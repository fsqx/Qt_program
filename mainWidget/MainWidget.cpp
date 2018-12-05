#include "MainWidget.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->pb_send->setShortcut(Qt::Key_Return);
    initFont();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initMainWidget()
{

}

void MainWidget::initFont()
{
    bigFont = new QFont;
    bigFont->setPointSize(11);
    bigFont->setFamily("微软雅黑");

    littleFont = new QFont;
    littleFont->setPointSize(9);
    littleFont->setFamily("微软雅黑");

}

/** 显示主界面 */
void MainWidget::showMainWidget()
{
    this->show();
}

void MainWidget::addNewUserOnFriendList(QString userName)
{
    this->ui->lw_friendList->addItem(userName);
}

void MainWidget::addNewMessageOnWidget(Msg *msg)
{
    QString tmp = tr("<i><font size='4' face='微软雅黑'>%1<font></i>  <i><font size='4' face='微软雅黑'>%2</font></i>").arg(msg->getSendUser()).arg(msg->getRecvTime());
    this->ui->tb_showMsg->append(tmp);
    tmp.clear();
    tmp = tr("<p><font size='6' face='微软雅黑'>%1<font></p>").arg(msg->getMsg());
    this->ui->tb_showMsg->append(tmp);
}

void MainWidget::flushMessageWidget(QList<Msg *> *msgList)
{
    for(int i = 0; i < msgList->length(); i++)
    {
        this->addNewMessageOnWidget(msgList->at(i));
    }
}

/** 获取当前聊天用户 */
QString MainWidget::getCurrentChatUser()
{
    return ui->lw_friendList->currentItem()->text();
}

/** 获取当前输入框内容 */
QString MainWidget::getInputMsg()
{
    return ui->te_sendMsg->toPlainText();
}

/** 清楚输入框 */
void MainWidget::setCleanInputMsg()
{
    ui->te_sendMsg->clear();
}

QListWidgetItem *MainWidget::getCurrentFriendListItem()
{
    return ui->lw_friendList->currentItem();
}


/** ******** 信号和槽 ******** */



/** 退出 */
void MainWidget::on_pb_quit_clicked()
{
    this->close();
}

///** 在好友列表增加用户 */
//void MainWidget::slotAddNewUserOnMainWidget(const QString newUser)
//{
//    ui->lw_friendList->addItem(newUser);
//}

///** 在消息列表增加消息 */
//void MainWidget::slotAddNewMsgOnMainWidget(const QString msg, const QString sendUser, const QString currentTime)
//{
//    ui->tb_showMsg->setFontWeight(9);
//    ui->tb_showMsg->append(sendUser + " " + currentTime);
//    ui->tb_showMsg->setFontWeight(11);
//    ui->tb_showMsg->append(msg);
//    ui->tb_showMsg->append("");
//}

/** 发送按钮 */
void MainWidget::on_pb_send_clicked()
{
    ui->tb_showMsg->setFont(*littleFont);
    ui->tb_showMsg->append(QString("me  ") + QTime::currentTime().toString());
    ui->tb_showMsg->setFont(*bigFont);
    ui->tb_showMsg->append(ui->te_sendMsg->toPlainText());
    emit signalSendMsgToOther();
}

/** 改变当前聊天对象 */
void MainWidget::on_lw_friendList_itemClicked()
{
    ui->tb_showMsg->clear();
    ui->te_sendMsg->clear();
    emit signalFriendListChanged();
}

/** 消息列表滚动到最下面 */
void MainWidget::on_tb_showMsg_textChanged()
{
    ui->tb_showMsg->moveCursor(QTextCursor::End);
}
