/*****************************************************************//**
 * @file   workspacedto.h
 * @brief  Header of the workspaceDTO class
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

#ifndef WORKSPACEDTO_H
#define WORKSPACEDTO_H

#include <QtCore>

/**
 * @brief Class workspaceDTO which represents a workspace from the server
 */
class workspaceDTO
{
public:
    workspaceDTO();
    workspaceDTO(QString _name, QString _description, int _size);
    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getDescription() const;
    void setDescription(const QString &newDescription);

    int getSize() const;
    void setSize(int newSize);

private:
    QString name; ///<Name of the workspace
    QString description; ///<Description of the workspae
    int size; ///<Size
};

#endif // WORKSPACEDTO_H
