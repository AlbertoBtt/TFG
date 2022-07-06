/*****************************************************************//**
 * @file   datasetdlg.h
 * @brief  Header of the datasetDlg class
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

#ifndef DATASETDLG_H
#define DATASETDLG_H

#include <QDialog>
#include <datasetdto.h>
#include <boundingbox.h>
#include <coord.h>
#include <QMessageBox>
#include "ui_datasetdlg.h"

/**
 * @brief Class which represents the dialog to create a new dataset
 */
class datasetDlg : public QDialog, public Ui::datasetDlg
{
    Q_OBJECT

public:
    explicit datasetDlg(QWidget *parent = nullptr);
    datasetDlg(datasetDTO datasetIn, QWidget* parent = nullptr);
    ~datasetDlg();

    const datasetDTO &getDataset() const;
    void setDataset(const datasetDTO &newDataset);

private:
    datasetDTO dataset; ///<The new dataset

    bool checkDatasetData();
    bool checkDatasetNorth();
    bool checkDatasetSouth();
private slots:
    void finish();
};

#endif // DATASETDLG_H
