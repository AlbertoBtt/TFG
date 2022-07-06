/*****************************************************************//**
 * @file   coord.cpp
 * @brief  Implementation of the coord's functions
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

#include "coord.h"

/**
 * @brief Default constructor
 * 
 */
coord::coord()
{
    easting="0";
    northing="0";
    zone="16N";
    height="0";
}

/**
 * @brief Parameterized constructor
 * 
 * @param [in] easting Easting point
 * @param [in] northing Northing point
 * @param [in] zone UTM Zone
 * @param [in] height Height
 */
coord::coord(const QString &easting, const QString &northing, const QString &zone, const QString &height) : easting(easting),
    northing(northing),
    zone(zone),
    height(height)
{}

const QString &coord::getHeight() const
{
    return height;
}

void coord::setHeight(const QString &newHeight)
{
    height = newHeight;
}

const QString &coord::getZone() const
{
    return zone;
}

void coord::setZone(const QString &newZone)
{
    zone = newZone;
}

const QString &coord::getNorthing() const
{
    return northing;
}

void coord::setNorthing(const QString &newNorthing)
{
    northing = newNorthing;
}

const QString &coord::getEasting() const
{
    return easting;
}

void coord::setEasting(const QString &newEasting)
{
    easting = newEasting;
}


