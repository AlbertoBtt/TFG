#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QString>

class serverInfo
{
public:
    serverInfo();
    serverInfo(QString name, QString ip, QString port);

    const QString &getName() const;

    const QString &getIp() const;

    const QString &getPort() const;

private:
    QString name;
    QString ip;
    QString port;
};

#endif // SERVERINFO_H
