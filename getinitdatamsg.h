#ifndef GETINITDATAMSG_H
#define GETINITDATAMSG_H

#include <QString>
#include <QJsonObject>

class GetInitDataMsg
{
public:
    GetInitDataMsg();

    void write(QJsonObject&) const;
};

#endif // GETINITDATAMSG_H
