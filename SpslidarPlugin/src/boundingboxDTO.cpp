/*****************************************************************//**
 * @file   boundingboxDTO.cpp
 * @brief  Implementation of the boundingBoxDto's functions
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

#include "boundingboxDTO.h"

/**
 * @brief Default Constructor
 * 
 */
boundingBoxDTO::boundingBoxDTO()
{
    southWestBottom=coord();
    northEastTop=coord();
}

/**
 * @brief Parameterized constructor
 *
 * @param [in] southWestBottom SouthWestBottom coord
 * @param [in] northEastTop NorthEastTop coord
 */
boundingBoxDTO::boundingBoxDTO(const coord& southWestBottom, const coord& northEastTop) : southWestBottom(southWestBottom),
northEastTop(northEastTop)
{

}

const coord &boundingBoxDTO::getNorthEastTop() const
{
    return northEastTop;
}

void boundingBoxDTO::setNorthEastTop(const coord &newNorthEastTop)
{
    northEastTop = newNorthEastTop;
}

const coord &boundingBoxDTO::getSouthWestBottom() const
{
    return southWestBottom;
}

void boundingBoxDTO::setSouthWestBottom(const coord &newSouthWestBottom)
{
    southWestBottom = newSouthWestBottom;
}


