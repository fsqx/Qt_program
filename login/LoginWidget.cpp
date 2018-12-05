#include "LoginWidget.h"


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    initLoginWidget();
    ui->pb_login->setShortcut(Qt::Key_Return);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

QString LoginWidget::getInputPasswd()
{
    return ui->le_getPasswd->text();
}

QString LoginWidget::getInputUid()
{
    return ui->le_getUID->text();
}

/** 初始化登陆界面 */
void LoginWidget::initLoginWidget()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowTitle(tr("聊天室登陆"));
    // 设置tab关联
    QLineEdit::setTabOrder(ui->le_getUID, ui->le_getPasswd);
    QPushButton::setTabOrder(ui->pb_login, ui->pb_register);
}

/** 鼠标点击事件 */
void LoginWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        m_widgetMove = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
}

/** 鼠标移动事件 */
void LoginWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        this->move(event->globalPos() - m_widgetMove);
        event->accept();
    }
}

/** ******** 信号和槽 ********* */

/** 最小化按钮 */
void LoginWidget::on_pb_min_clicked()
{
    this->showMinimized();
}

/** 关闭按钮 */
void LoginWidget::on_pb_close_clicked()
{
    this->close();
}

/** 登陆按钮 */
void LoginWidget::on_pb_login_clicked()
{
    const QString getUid = ui->le_getUID->text();
    const QString getPasswd = ui->le_getPasswd->text();
    if(getUid == "" || getPasswd == "")
    {
        return;
    }
    emit signalSendUidAndPassword(enum_LOGIN);

}

void LoginWidget::slotClearLoginWidget()
{
    ui->le_getPasswd->text().clear();
    ui->le_getUID->text().clear();
}

void LoginWidget::on_pb_register_clicked()
{
    const QString getUid = ui->le_getUID->text();
    const QString getPasswd = ui->le_getPasswd->text();
    if(getUid == "" || getPasswd == "")
    {
        return;
    }
    emit signalSendUidAndPassword(enum_REGST);
}
