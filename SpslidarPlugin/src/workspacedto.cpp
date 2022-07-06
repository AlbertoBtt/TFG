/*****************************************************************//**
 * @file   workspacedto.cpp
 * @brief  Implmentation of the workspaceDTO class
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
 //#				    		 COPYRIGHT:								    #
 //#				      Alberto Beteta Fernandez					 	    #
 //#				     Rafael Jesús Segura Sánchez						#
 //#				      Antonio Jesús Rueda Ruíz						    #
 //#                    Carlos Javier Ogayar Anguita                        #
 //#                                                                        #
 //##########################################################################

#include "workspacedto.h"

/**
 * @brief Default Constructor
 * 
 */
workspaceDTO::workspaceDTO(){
    this->name="";
    this->description="";
    this->size=100;
}

/**
 * @brief Paremeterized constructor
 * 
 * @param [in] _name Name of the Workspace
 * @param [in] _description Description of the Workspace
 * @param [in] _size Size
 */
workspaceDTO::workspaceDTO(QString _name, QString _description, int _size)
{
    this->name=_name;
    this->description=_description;
    this->size=_size;
}

const QString &workspaceDTO::getName() const
{
    return name;
}

void workspaceDTO::setName(const QString &newName)
{
    name = newName;
}

const QString &workspaceDTO::getDescription() const
{
    return description;
}

void workspaceDTO::setDescription(const QString &newDescription)
{
    description = newDescription;
}

int workspaceDTO::getSize() const
{
    return size;
}

void workspaceDTO::setSize(int newSize)
{
    size = newSize;
}
