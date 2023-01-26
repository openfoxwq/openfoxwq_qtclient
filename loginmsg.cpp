#include "loginmsg.h"

LoginMsg::LoginMsg()
{
}

const QString &LoginMsg::username() const
{
    return mUsername;
}

const QString &LoginMsg::password() const
{
    return mPassword;
}

void LoginMsg::setPassword(const QString &newPassword)
{
    mPassword = newPassword;
}

void LoginMsg::setUsername(const QString &newUsername)
{
    mUsername = newUsername;
}

LoginMsg::LoginMsg(const QString &username, const QString &password) : mUsername(username),
    mPassword(password)
{}

void LoginMsg::write(QJsonObject& json) const {
    QJsonObject msg;
    msg["username"] = mUsername;
    msg["password"] = mPassword;

    json["type"] = "LoginMsg";
    json["msg"] = msg;
}
