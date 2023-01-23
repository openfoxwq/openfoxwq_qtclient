#include "getinitdatamsg.h"

GetInitDataMsg::GetInitDataMsg()
{
}

void GetInitDataMsg::write(QJsonObject& json) const {
    QJsonObject msg;
    json["type"] = "GetInitDataMsg";
    json["msg"] = msg;
}
