#include "datasetdto.h"

datasetDTO::datasetDTO()
{
    name="";
    description="";
    dateOfAcquisition=QDateTime();
    dataBlockSize=100;
    dataBlockFormat="LAZ";
    boundingBoxCoords=boundingBoxDTO();

}

datasetDTO::datasetDTO(const QString &name, const QString &description, const QDateTime &dateOfAcquisition, int dataBlockSize, const QString &dataBlockFormat, const boundingBoxDTO &boundingBox) : name(name),
    description(description),
    dateOfAcquisition(dateOfAcquisition),
    dataBlockSize(dataBlockSize),
    dataBlockFormat(dataBlockFormat),
    boundingBoxCoords(boundingBox)
{}

const QString &datasetDTO::getName() const
{
    return name;
}

void datasetDTO::setName(const QString &newName)
{
    name = newName;
}

const QString &datasetDTO::getDescription() const
{
    return description;
}

void datasetDTO::setDescription(const QString &newDescription)
{
    description = newDescription;
}

const QDateTime &datasetDTO::getDateOfAcquisition() const
{
    return dateOfAcquisition;
}

void datasetDTO::setDateOfAcquisition(const QDateTime &newDateOfAcquisition)
{
    dateOfAcquisition = newDateOfAcquisition;
}

int datasetDTO::getDataBlockSize() const
{
    return dataBlockSize;
}

void datasetDTO::setDataBlockSize(int newDataBlockSize)
{
    dataBlockSize = newDataBlockSize;
}

const QString &datasetDTO::getDataBlockFormat() const
{
    return dataBlockFormat;
}

void datasetDTO::setDataBlockFormat(const QString &newDataBlockFormat)
{
    dataBlockFormat = newDataBlockFormat;
}

const boundingBoxDTO &datasetDTO::getBoundingBox() const
{
    return boundingBoxCoords;
}

void datasetDTO::setBoundingBox(const boundingBoxDTO &newBoundingBox)
{
    boundingBoxCoords = newBoundingBox;
}
