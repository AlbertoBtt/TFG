/*****************************************************************//**
 * @file   spslidaruploaddlg.h
 * @brief  Header of the class spslidarUploadDlg
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


#ifndef SPSLIDARUPLOADDLG_H
#define SPSLIDARUPLOADDLG_H

#include <QDialog>
#include "serverinfo.h"
#include <QtNetwork>
#include "workspacedlg.h"
#include "workspacedto.h"
#include "datasetdlg.h"
#include "datasetdto.h"
#include "ui_spslidaruploaddlg.h"

/**
 * @brief Class spslidarUploadDlg which represents the interface to select the dataset where the cloud will be uploaded
 */
class spslidarUploadDlg : public QDialog, Ui::spslidarUploadDlg
{
    Q_OBJECT

public:
    spslidarUploadDlg(QWidget *parent = nullptr);
    spslidarUploadDlg(datasetDTO dataset, QWidget* parent = nullptr);
    ~spslidarUploadDlg();

    const QString &getRute() const;
    void setRute(const QString &newRute);

    const QString &getZone() const;
    void setZone(const QString &newZone);

    datasetDTO getDataset();
    void setDataset(datasetDTO dataset);

private:
    QList<serverInfo> serversInfoList; ///<List of serverInfo saved in the computer
    QList<workspaceDTO> workspaceDTOList; ///<List of workspaces from a server
    QList<datasetDTO> datasetDTOList; ///<List of dataset from a workspace
    QString server; ///<Server we are working with
    QNetworkAccessManager *netManager; ///<Connection manager
    QNetworkReply *netReply; ///<The reply of a petition
    QByteArray dataBuffer; ///<ByteArray where the body of a petition is saved
    QString workspace; ///<Workspace we are working with
    QString dataset; ///<Dataset we are working with
    workspaceDlg newWorkspace; ///<Dialog to create a new workspace
    datasetDlg newDataset; ///<Dialog to create a new dataset
    QString rute; ///<The final path to save the cloud
    QString zone; ///<The UTM zone of the Dataset
    datasetDTO newDatasetDTO; ///<The dataset from we will recover the Bounding Box information
    void getServers();
    void updateServerDocument();
    void clearList();
    void setListWorkspaces();
    void setListDatasets();
    QString dateToString(QDateTime date);
private slots:
    void serverClicked();
    void saveServer();
    void deleteServer();
    void serverContinue();
    void cancel();
    void readMessage();
    void finishReadingWorkspaces();
    void clickWorkspace();
    void finishPostWorkspace();
    void comeBack();
    void finishReadingDatasets();
    void clickDataset();
    void finishPostDataset();
    void finish();
};
#endif // SPSLIDARUPLOADDLG_H
