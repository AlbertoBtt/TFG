#ifndef WORKSPACEDTO_H
#define WORKSPACEDTO_H

#include <QtCore>

class workspaceDTO
{
public:
    workspaceDTO();
    workspaceDTO(QString _name, QString _description, int _size);
    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getDescription() const;
    void setDescription(const QString &newDescription);

    int getSize() const;
    void setSize(int newSize);

private:
    QString name;
    QString description;
    int size;
};

#endif // WORKSPACEDTO_H
