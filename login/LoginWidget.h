#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QMouseEvent>
#include "ui_LoginWidget.h"

namespace Ui {
class LoginWidget;
}

enum LOGIN_FLAG{enum_LOGIN = 0x10, enum_REGST};

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    // 初始化登录界面
    void initLoginWidget();

    QString getInputUid();

    QString getInputPasswd();

protected:
    // 鼠标移动事件
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

signals:
    // 发送界面的UID和密码给逻辑层
    signalSendUidAndPassword(int flag);

private slots:

    // 最小化
    void on_pb_min_clicked();
    // 关闭
    void on_pb_close_clicked();
    // 登陆按钮
    void on_pb_login_clicked();
    // 清除登录界面
    void slotClearLoginWidget();
    // 注册按钮
    void on_pb_register_clicked();

private:
    Ui::LoginWidget *ui;

    QPoint m_widgetMove;
};

#endif // LOGINWIDGET_H
