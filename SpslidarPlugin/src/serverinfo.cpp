/*****************************************************************//**
 * @file   serverinfo.cpp
 * @brief  Implementation of the serverInfo's functions
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

#include "serverinfo.h"

/**
 * @brief Default constructor
 * 
 */
serverInfo::serverInfo()
{
    this->ip=nullptr;
    this->name=nullptr;
    this->port=nullptr;
}
/**
 * @brief Parameterized constructor
 * 
 * @param [in] name Name of the server
 * @param [in] ip IP of the server
 * @param [in] port Port of the server
 */
serverInfo::serverInfo(QString name, QString ip, QString port){
    this->name=name;
    this->ip=ip;
    this->port=port;
}

const QString &serverInfo::getName() const
{
    return name;
}

const QString &serverInfo::getPort() const
{
    return port;
}

const QString &serverInfo::getIp() const
{
    return ip;
}
