/*****************************************************************//**
 * @file   uploaddlg.cpp
 * @brief  Implementation of the UploadDlg class
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

#include "uploaddlg.h"
#include "ui_uploaddlg.h"

/**
 * @brief Constructor
 * 
 * @param [in] parent Parent interface
 * @param [in] _rute Rute of the server to upload the cloud
 * @param [in] _cloudRute Path where the .laz file is located
 */
UploadDlg::UploadDlg(QWidget *parent, QString _rute, QString _cloudRute)
    : QDialog(parent)
    , Ui::UploadDlg()
    , rute(_rute)
    , cloudRute(_cloudRute)
{
    setupUi(this);
    netManager=new QNetworkAccessManager(this);
    netReply=nullptr;
    sendCloud();
}

/**
 * @brief Destroyer
 * 
 */
UploadDlg::~UploadDlg()
{

}

/**
 * @brief Function to generate the Network Request with the cloud in his body
 * 
 */
void UploadDlg::sendCloud(){
        QNetworkRequest req{QUrl(QString(rute+"/data"))};
        QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        multiPart->setBoundary("---------------------jasglfuyqwreltjaslgjlkdaghflsdgh");
        req.setHeader(QNetworkRequest::ContentTypeHeader, QString("multipart/form-data; boundary=" + multiPart->boundary()));
        QHttpPart cloudPart;
        QList<QString> cloudRuteSplit=cloudRute.split("/");
        cloudPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; filename=file ; name=\"files\""));
        QFile* file = new QFile(cloudRute);
        file->open(QIODevice::ReadOnly);
        QByteArray bytes=file->readAll();
        cloudPart.setBody(bytes);
        multiPart->append(cloudPart);
        netReply = netManager->put(req,multiPart);
        connect(netReply,&QNetworkReply::finished,this,&UploadDlg::finishPostCloud);
        connect(netReply,&QNetworkReply::uploadProgress,this,&UploadDlg::updateProgress);
}

/**
 * @brief Function to execute the last part of the Network Request to upload the cloud. We check the response code.
 * 
 */
void UploadDlg::finishPostCloud(){
    if(netReply->error() != QNetworkReply::NoError){
            qDebug() << "Error : " << netReply->errorString();
            QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
            reject();
     }else{
            accept();
     }
}

/**
 * @brief Slot function to representate the percentage of cloud that has been uploaded
 * 
 * @param [in] a Actual amount of bytes uploaded
 * @param [in] b Total amount of bytes that have to been uploaded
 */
void UploadDlg::updateProgress(qint64 a, qint64 b){
    if(b>0){
        progressBar->setValue(100*a/b);
    }
}
