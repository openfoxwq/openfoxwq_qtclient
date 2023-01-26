#ifndef LEAVEROOMMSG_H
#define LEAVEROOMMSG_H

#include <QJsonObject>

class LeaveRoomMsg
{
public:
    LeaveRoomMsg();
    LeaveRoomMsg(int roomId);

    int roomId() const;
    void setRoomId(int newRoomId);

    void write(QJsonObject&) const;

private:
    int m_roomId;

};

#endif // LEAVEROOMMSG_H
