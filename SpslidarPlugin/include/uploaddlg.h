/*****************************************************************//**
 * @file   uploaddlg.h
 * @brief  Header of the class UploadDlg
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

#ifndef UPLOADDLG_H
#define UPLOADDLG_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QFile>
#include <QMessageBox>
#include "ui_uploaddlg.h"

/**
 * @brief Class UploadDlg which represents the interface which we can see while the cloud is uploading
 */
class UploadDlg : public QDialog, Ui::UploadDlg
{
    Q_OBJECT
public:
    UploadDlg(QWidget *parent = nullptr, QString _rute="", QString _cloudRute="");
    ~UploadDlg();

private:
    QString rute; ///<Sever path where the cloud will be uploaded
    QString cloudRute; ///<Local path where the file .laz is located
    QNetworkAccessManager* netManager; ///<Connection Manager
    QNetworkReply* netReply; ///<Reply of a petition
    void sendCloud();
private slots:
    void finishPostCloud();
    void updateProgress(qint64 a, qint64 b);
};
#endif // UPLOADDLG_H
