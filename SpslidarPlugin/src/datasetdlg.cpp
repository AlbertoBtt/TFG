/*****************************************************************//**
 * @file   datasetdlg.cpp
 * @brief  Implementation of the datasetDlg's functions
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

#include "datasetdlg.h"
#include "ui_datasetdlg.h"

/**
 * @brief Constructor
 * 
 * @param [in] parent The parent interface of the dialog
 */
datasetDlg::datasetDlg(QWidget *parent) :
    QDialog(parent),
    Ui::datasetDlg()
{
    setupUi(this);
}

/**
 * @brief Parameterized constructor
 * 
 * @param [in] datasetIn The dataset we obtain the bounding box with
 * @param [in] parent The parent interface of the Dialog
 */
datasetDlg::datasetDlg(datasetDTO datasetIn, QWidget* parent) :
    QDialog(parent),
    Ui::datasetDlg()
{
    setupUi(this);
    southEastingEdit->setText(datasetIn.getBoundingBox().getSouthWestBottom().getEasting());
    southNorthingEdit->setText(datasetIn.getBoundingBox().getSouthWestBottom().getNorthing());
    southHeightEdit->setText(datasetIn.getBoundingBox().getSouthWestBottom().getHeight());
    southZoneEdit->setText((datasetIn.getBoundingBox().getSouthWestBottom().getZone()));
    northEastingEdit->setText(datasetIn.getBoundingBox().getNorthEastTop().getEasting());
    northNorthingEdit->setText(datasetIn.getBoundingBox().getNorthEastTop().getNorthing());
    northHeightEdit->setText(datasetIn.getBoundingBox().getNorthEastTop().getHeight());
    northZoneEdit->setText(datasetIn.getBoundingBox().getNorthEastTop().getZone());
    dataset = datasetIn;
}

datasetDlg::~datasetDlg()
{

}

const datasetDTO &datasetDlg::getDataset() const
{
    return dataset;
}

void datasetDlg::setDataset(const datasetDTO &newDataset)
{
    dataset = newDataset;
}

/**
 * @brief Function to create the new Dataset with correct information
 * 
 */
void datasetDlg::finish()
{
    QString name=nameEdit->text();
    QString description=descriptionEdit->toPlainText();
    QString date=dateEdit->text();
    int datablockSize=datablockSizeEdit->text().toInt();
    QString datablockFormat=datablockFormatEdit->text();

    QString northEasting=northEastingEdit->text();
    QString northNorthing=northNorthingEdit->text();
    QString northZone=northZoneEdit->text();
    QString northHeight=northHeightEdit->text();

    QString southEasting=southEastingEdit->text();
    QString southNorthing=southNorthingEdit->text();
    QString southZone=southZoneEdit->text();
    QString southHeight=southHeightEdit->text();

    coord north(northEasting,northNorthing,northZone,northHeight);
    coord south(southEasting,southNorthing,southZone,southHeight);
    boundingBoxDTO box(south,north);
    if(checkDatasetData()&&checkDatasetNorth()&&checkDatasetSouth()){
        if(date.count("/")==2){
            QList<QString> split=date.split("/");
            QDate dateFormat(split[2].toInt(),split[1].toInt(),split[0].toInt());
            QLocale locale  = QLocale(QLocale::English, QLocale::UnitedKingdom);
            QDateTime dateAndTime(dateFormat);
            dataset.setName(name);
            dataset.setDescription(description);
            dataset.setDateOfAcquisition(dateAndTime);
            dataset.setDataBlockSize(datablockSize);
            dataset.setDataBlockFormat(datablockFormat);
            dataset.setBoundingBox(box);
            accept();
        }else{
            QMessageBox::warning(this,"Error",QString("Invalid date format"));
        }
    }else{
        QMessageBox::warning(this,"Error",QString("Some cell is empty"));
    }
}

/**
 * @brief Check if the basic information of the dataset is valid
 * 
 * @return True if the information is valid, else returns false
 */
bool datasetDlg::checkDatasetData(){
    QString name=nameEdit->text();
    QString description=descriptionEdit->toPlainText();
    QString date=dateEdit->text();
    int datablockSize=datablockSizeEdit->text().toInt();
    QString datablockFormat=datablockFormatEdit->text();
    if(name.isEmpty()||description.isEmpty()||date.isEmpty()||date.isEmpty()||datablockSize<100||datablockFormat.isEmpty()){
        return false;
    }
    return true;
}

/**
 * @brief Check if the information of the northEastTop coord is valid
 * 
 * @return True if the information is valid, else returns false
 */
bool datasetDlg::checkDatasetNorth()
{
    QString northEasting=northEastingEdit->text();
    QString northNorthing=northNorthingEdit->text();
    QString northZone=northZoneEdit->text();
    QString northHeight=northHeightEdit->text();
    if(northEasting.isEmpty()||northNorthing.isEmpty()||northZone.isEmpty()||northHeight.isEmpty()){
        return false;
    }
    return true;
}

/**
 * @brief Check if the information of the southWestBottom coord is valid
 * 
 * @return True if the information is valid, else returns false
 */
bool datasetDlg::checkDatasetSouth()
{
    QString southEasting=southEastingEdit->text();
    QString southNorthing=southNorthingEdit->text();
    QString southZone=southZoneEdit->text();
    QString southHeight=southHeightEdit->text();
    if(southEasting.isEmpty()||southNorthing.isEmpty()||southZone.isEmpty()||southHeight.isEmpty()){
        return false;
    }
    return true;
}
