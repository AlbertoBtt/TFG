/*****************************************************************//**
 * @file   coord.h
 * @brief  Header of the class coord
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

#ifndef COORD_H
#define COORD_H
#include <QtCore>

/**
 * @brief Class which represents a coord in UTM
 */
class coord
{
public:
    coord();
    coord(const QString &easting, const QString &northing, const QString &zone, const QString &height);
    const QString &getHeight() const;
    void setHeight(const QString &newHeight);

    const QString &getZone() const;
    void setZone(const QString &newZone);

    const QString &getNorthing() const;
    void setNorthing(const QString &newNorthing);

    const QString &getEasting() const;
    void setEasting(const QString &newEasting);

private:
    QString easting; ///< Easting of the coord
    QString northing; ///< Northing of the coord
    QString zone; ///< UTM zone of the coord
    QString height; ///< Height of the coord
};

#endif // COORD_H
