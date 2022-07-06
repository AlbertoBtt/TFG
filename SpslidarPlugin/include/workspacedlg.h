/*****************************************************************//**
 * @file   workspacedlg.h
 * @brief  Header of the workspaceDlg class
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

#ifndef WORKSPACEDLG_H
#define WORKSPACEDLG_H

#include <QDialog>
#include "workspacedto.h"
#include <QMessageBox>
#include "ui_workspacedlg.h"

/**
 * @brief Class workspaceDlg which represents the dialog to create a new workspace
 */
class workspaceDlg : public QDialog, public Ui::workspaceDlg
{
    Q_OBJECT

public:
    workspaceDlg(QWidget *parent = nullptr);
    ~workspaceDlg();

    const workspaceDTO &getWorkspace() const;

private:
    workspaceDTO workspace; ///<The new workspace
private slots:
    void finish();
};

#endif // WORKSPACEDLG_H
