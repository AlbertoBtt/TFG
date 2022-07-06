/*****************************************************************//**
 * @file   datasetdto.cpp
 * @brief  Implementation of the datasetDto's functions
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

#include "datasetdto.h"

/**
 * @brief Default Constructor
 * 
 */
datasetDTO::datasetDTO()
{
    name="";
    description="";
    dateOfAcquisition=QDateTime();
    dataBlockSize=100;
    dataBlockFormat="LAZ";
    boundingBoxCoords=boundingBoxDTO();

}

/**
 * @brief Parameterized constructor
 * 
 * @param [in] name Name of the dataset
 * @param [in] description Description of the Dataset
 * @param [in] dateOfAcquisition Date of Acquisition of the Dataset
 * @param [in] dataBlockSize Size of the dataBlock
 * @param [in] dataBlockFormat Format of the Datablock
 * @param [in] boundingBox boundingBoxDTO of the Dataset
 */
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
