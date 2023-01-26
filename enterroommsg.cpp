#include "enterroommsg.h"

EnterRoomMsg::EnterRoomMsg()
{

}

int EnterRoomMsg::roomId() const
{
    return m_roomId;
}

void EnterRoomMsg::setRoomId(int newRoomId)
{
    m_roomId = newRoomId;
}

EnterRoomMsg::EnterRoomMsg(int roomId) : m_roomId(roomId)
{}


void EnterRoomMsg::write(QJsonObject& json) const {
    QJsonObject msg;
    msg["room_id"] = m_roomId;

    json["type"] = "EnterRoomMsg";
    json["msg"] = msg;
}
