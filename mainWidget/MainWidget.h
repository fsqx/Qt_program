#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTextBrowser>
#include <QFont>
#include "Msg.h"
#include "ui_MainWidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    // 初始化主界面
    void initMainWidget();
    // 显示主界面
    void showMainWidget();
    // 增加新用户
    void addNewUserOnFriendList(QString userName);
    // 消息框增加新消息
    void addNewMessageOnWidget(Msg *msg);
    // 刷新消息区
    void flushMessageWidget(QList<Msg *> *msgList);


    // 获取当前用户
    QString getCurrentChatUser(void);
    // 获取输入内容
    QString getInputMsg(void);
    // 清除数据区
    void setCleanInputMsg(void);

    QListWidgetItem *getCurrentFriendListItem();


private:
    Ui::MainWidget *ui;

    QFont *bigFont;

    QFont *littleFont;

    void initFont();

signals:
    // 当前聊天对象改变
    void signalFriendListChanged();
    // 发送消息给其他用户
    void signalSendMsgToOther();





public slots:
    // 显示主界面
//    void slotShowMainWidget();

    // 在主界面新增消息
//    void slotAddNewMsgOnMainWidget(const QString msg, const QString sendUser, const QString currentTime);

private slots:
    // 退出
    void on_pb_quit_clicked();
    // 发送
    void on_pb_send_clicked();
    // 点击好友列表item
    void on_lw_friendList_itemClicked();
    // 消息列表滚动到最下方
    void on_tb_showMsg_textChanged();
};

#endif // MAINWIDGET_H
