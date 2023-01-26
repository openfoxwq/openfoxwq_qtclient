#include "leaveroommsg.h"

LeaveRoomMsg::LeaveRoomMsg()
{

}

int LeaveRoomMsg::roomId() const
{
    return m_roomId;
}

void LeaveRoomMsg::setRoomId(int newRoomId)
{
    m_roomId = newRoomId;
}

LeaveRoomMsg::LeaveRoomMsg(int roomId) : m_roomId(roomId)
{}


void LeaveRoomMsg::write(QJsonObject& json) const {
    QJsonObject msg;
    msg["room_id"] = m_roomId;

    json["type"] = "LeaveRoomMsg";
    json["msg"] = msg;
}
