#ifndef ENTERROOMMSG_H
#define ENTERROOMMSG_H

#include <QJsonObject>

class EnterRoomMsg
{
public:
    EnterRoomMsg();
    EnterRoomMsg(int roomId);

    int roomId() const;
    void setRoomId(int newRoomId);

    void write(QJsonObject&) const;

private:
    int m_roomId;

};

#endif // ENTERROOMMSG_H
