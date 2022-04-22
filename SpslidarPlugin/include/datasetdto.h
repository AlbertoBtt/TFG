#ifndef DATASETDTO_H
#define DATASETDTO_H
#include <QtCore>
#include <boundingboxDTO.h>

class datasetDTO
{
public:
    datasetDTO();
    datasetDTO(const QString &name, const QString &description, const QDateTime &dateOfAcquisition, int dataBlockSize, const QString &dataBlockFormat, const boundingBoxDTO &boundingBox);
    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getDescription() const;
    void setDescription(const QString &newDescription);
    const QDateTime &getDateOfAcquisition() const;
    void setDateOfAcquisition(const QDateTime &newDateOfAcquisition);
    int getDataBlockSize() const;
    void setDataBlockSize(int newDataBlockSize);
    const QString &getDataBlockFormat() const;
    void setDataBlockFormat(const QString &newDataBlockFormat);

    const boundingBoxDTO &getBoundingBox() const;
    void setBoundingBox(const boundingBoxDTO &newBoundingBox);

private:
    QString name;
    QString description;
    QDateTime dateOfAcquisition;
    int dataBlockSize;
    QString dataBlockFormat;
    boundingBoxDTO boundingBoxCoords;
};

#endif // DATASETDTO_H
