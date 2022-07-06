/*****************************************************************//**
 * @file   datasetdto.h
 * @brief  Header of the class datasetDTO
 * 
 * @author Alberto Beteta Fernández
 * @date   April 2022
 *********************************************************************/

 //##########################################################################
 //#                                                                        #
 //#                CLOUDCOMPARE PLUGIN: SpslidarPlugin                     #
 //#                                                                        #
 //#  This program is free software; you can redistribute it and/or modify  #
 //#  it under the terms of the GNU General Public License as published by  #
 //#  the Free Software Foundation; version 2 of the License.               #
 //#                                                                        #
 //#  This program is distributed in the hope that it will be useful,       #
 //#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
 //#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
 //#  GNU General Public License for more details.                          #
 //#                                                                        #
 //#						     COPYRIGHT:									#
 //#					 Alberto Beteta Fernandez							#                     
 //#				   Rafael Jesús Segura Sánchez							#
 //#				    Antonio Jesús Rueda Ruíz							#
 //#                  Carlos Javier Ogayar Anguita                          #
 //#                                                                        #
 //##########################################################################

#ifndef DATASETDTO_H
#define DATASETDTO_H
#include <QtCore>
#include <boundingboxDTO.h>

/**
 * @brief Class datasetDTO which represents a Dataset
 */
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
    QString name; ///< Name of the dataset
    QString description; ///<Description of the dataset
    QDateTime dateOfAcquisition; ///<Date of acquisition of the dataset
    int dataBlockSize; ///< Size of the Dataset's block
    QString dataBlockFormat; ///< Format of the Dataset's block
    boundingBoxDTO boundingBoxCoords; ///< Bounding Box of the Dataset
};

#endif // DATASETDTO_H
