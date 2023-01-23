#ifndef LOGINMSG_H
#define LOGINMSG_H

#include <QString>
#include <QJsonObject>

class LoginMsg
{
public:
    LoginMsg();
    LoginMsg(const QString &username, const QString &password);

    const QString &username() const;
    const QString &password() const;
    void setPassword(const QString &newPassword);
    void setUsername(const QString &newUsername);

    void write(QJsonObject&) const;

private:
    QString mUsername;
    QString mPassword;
};

#endif // LOGINMSG_H
