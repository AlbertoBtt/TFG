/*****************************************************************//**
 * @file   spslidardownloaddlg.h
 * @brief  Definition of the class spslidarDownloadDlg
 * 
 * @author Alberto Beteta Fernández
 * @date   March 2022
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

#ifndef SPSLIDARDLG_H
#define SPSLIDARDLG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include "serverinfo.h"
#include "ui_spslidardownloaddlg.h"

/**
 * @brief spslidarDonwloadDlg class which represents the dialog to download a laz from the server
 */
class spslidarDownloadDlg : public QDialog, public Ui::spslidarDownloadDlg
{
    Q_OBJECT

public:
    spslidarDownloadDlg(QWidget *parent = nullptr);
    ~spslidarDownloadDlg();
    QString getDataset();
    QString getRuta();
private:
    QNetworkAccessManager* netManager; ///< The client which is used for doing the petitions to the server
    QNetworkReply* netReply; ///< The reply from the server when we do a petition
    QByteArray dataBuffer; ///< A QByteArray where we save the content of the reply
    QString ruta; ///< The route where the data.laz is saved
    QString server; ///< The server which we are using
    QString workspace; ///< The workspace which we are using
    QString dataset; ///< The dataset which we are using
    QList<serverInfo> serversInfoList; ///< The list of servers which are saved
    void setListWorkspaces();
    void setListDatasets();
    void setDataset();
    void getServers();
    void updateServerDocument();
    void clearList();
private slots:
    void serverContinue();
    void workspaceContinue();
    void clickWorkspace();
    void clickDataset();
    void leerMensaje();
    void terminarLeerListaWorkspace();
    void clearValues();
    void terminarLeerListaDataset();
    void terminarLeerDataset();
    void cancel();
    void comeBack();
    void comeBackDataset();
    void confirm();
    void descargarDataset();
    void actualizarProgreso(qint64 ist, qint64 max);
    void terminarLeerDatasetData();
    void serverClicked();
    void saveServer();
    void deleteServer();
};
#endif // SPSLIDARDLG_H
