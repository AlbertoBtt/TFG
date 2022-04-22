#include "workspacedto.h"

workspaceDTO::workspaceDTO(){
    this->name="";
    this->description="";
    this->size=100;
}

workspaceDTO::workspaceDTO(QString _name, QString _description, int _size)
{
    this->name=_name;
    this->description=_description;
    this->size=_size;
}

const QString &workspaceDTO::getName() const
{
    return name;
}

void workspaceDTO::setName(const QString &newName)
{
    name = newName;
}

const QString &workspaceDTO::getDescription() const
{
    return description;
}

void workspaceDTO::setDescription(const QString &newDescription)
{
    description = newDescription;
}

int workspaceDTO::getSize() const
{
    return size;
}

void workspaceDTO::setSize(int newSize)
{
    size = newSize;
}
