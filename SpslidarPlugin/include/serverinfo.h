/*****************************************************************//**
 * @file   serverinfo.h
 * @brief  Header of the class serverInfo
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

#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QString>

/**
 * @brief Class serverInfo which represents the information of a server
 */
class serverInfo
{
public:
    serverInfo();
    serverInfo(QString name, QString ip, QString port);

    const QString &getName() const;

    const QString &getIp() const;

    const QString &getPort() const;

private:
    QString name; ///<Name of the server
    QString ip; ///<Ip of the server
    QString port; ///<Port of the server
};

#endif // SERVERINFO_H
