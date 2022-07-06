/*****************************************************************//**
 * @file   boundingboxDTO.h
 * @brief  Header of the class boundingBoxDTO
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

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "coord.h"

/**
 * @brief Class which represents the Bounding Box of a dataset
 */
class boundingBoxDTO
{
public:
    boundingBoxDTO();
    boundingBoxDTO(const coord &southWestBottom, const coord &northEastTop);
    const coord &getSouthWestBottom() const;
    void setSouthWestBottom(const coord &newSouthWestBottom);
    const coord &getNorthEastTop() const;
    void setNorthEastTop(const coord &newNorthEastTop);
private:
    coord southWestBottom; ///< Coord of the southWestBottom
    coord northEastTop; ///< Coord of the northEastTop
};

#endif // BOUNDINGBOX_H
