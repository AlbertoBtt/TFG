/*****************************************************************//**
 * @file   workspacedlg.cpp
 * @brief  Implementation of the workspaceDlg class
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
//#				    		     COPYRIGHT:								   #
//#				    	 Alberto Beteta Fernandez						   #
//#				       Rafael Jesús Segura Sánchez						   #
//#				        Antonio Jesús Rueda Ruíz						   #
//#                    Carlos Javier Ogayar Anguita                        #
//#                                                                        #
//##########################################################################

#include "workspacedlg.h"
#include "ui_workspacedlg.h"

/**
 * @brief Constructor
 * 
 * @param [in] parent Parent interface
 */
workspaceDlg::workspaceDlg(QWidget *parent) :
    QDialog(parent),
    Ui::workspaceDlg()
{
    setupUi(this);
}

/**
 * @brief Destroyer
 * 
 */
workspaceDlg::~workspaceDlg()
{

}

const workspaceDTO &workspaceDlg::getWorkspace() const
{
    return workspace;
}

/**
 * @brief Slot function that is executed when the finish button is clicked
 * 
 */
void workspaceDlg::finish(){
    QString name=nameText->text();
    QString description=descriptionText->toPlainText();
    int size=sizeText->text().toInt();
    if(!name.isEmpty() && !description.isEmpty() && size>=100 && size <= 1000000){
        workspace=workspaceDTO(name,description,size);
        this->accept();
    }else{
        QMessageBox::warning(this,"Error","One of the fields is empty or the datablock size is out of range");
    }
}
