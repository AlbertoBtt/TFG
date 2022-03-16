#include "serverinfo.h"

serverInfo::serverInfo()
{
    this->ip=nullptr;
    this->name=nullptr;
    this->port=nullptr;
}

serverInfo::serverInfo(QString name, QString ip, QString port){
    this->name=name;
    this->ip=ip;
    this->port=port;
}

const QString &serverInfo::getName() const
{
    return name;
}

const QString &serverInfo::getPort() const
{
    return port;
}

const QString &serverInfo::getIp() const
{
    return ip;
}
