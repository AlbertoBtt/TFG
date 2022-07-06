/*****************************************************************//**
 * @file   spslidaruploaddlg.cpp
 * @brief  Implementation of the spslidarUploadDlg class
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

#include "spslidaruploaddlg.h"
#include "QtCore"
#include "QMessageBox"

/**
 * @brief Default Constructor
 * 
 * @param [in] parent The parent interface
 */
spslidarUploadDlg::spslidarUploadDlg(QWidget *parent)
    : QDialog(parent)
    ,  Ui::spslidarUploadDlg()
{
    netManager = new QNetworkAccessManager(this);
    setupUi(this);
    getServers();
}

/**
 * @brief Parameterized constructor
 * 
 * @param [in] dataset We will obtain the bounding box from this dataset
 * @param [in] parent Parent interface
 */
spslidarUploadDlg::spslidarUploadDlg(datasetDTO dataset, QWidget* parent)
    : QDialog(parent)
    , Ui::spslidarUploadDlg()
    , newDataset(dataset, this)
{
    netManager = new QNetworkAccessManager(this);
    setupUi(this);
    getServers();
}

/**
 * @brief Destroyer
 * 
 */
spslidarUploadDlg::~spslidarUploadDlg()
{

}

const QString &spslidarUploadDlg::getRute() const
{
    return rute;
}

void spslidarUploadDlg::setRute(const QString &newRute)
{
    rute = newRute;
}

const QString &spslidarUploadDlg::getZone() const
{
    return zone;
}

void spslidarUploadDlg::setZone(const QString &newZone)
{
    zone = newZone;
}

datasetDTO spslidarUploadDlg::getDataset()
{
    return newDatasetDTO;
}

void spslidarUploadDlg::setDataset(datasetDTO dataset)
{
    newDatasetDTO = dataset;
}

/**
 * @brief Function to obtain the saved servers in the local computer. If it doesn't exist, it will create a new document.
 * 
 */
void spslidarUploadDlg::getServers(){
    QDir dir(QString(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)) + "\\spslidar");
    if (!dir.exists()) dir.mkpath(".");
    QString rutaServers = QString(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)) + "\\spslidar\\servers.txt";
    if(QFile::exists(rutaServers)){
        QFile inputFile(rutaServers);
        if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              QStringList attributes=line.split("::");
              serverInfo server(attributes[0],attributes[1],attributes[2]);
              serverList->addItem(attributes[0]);
              serversInfoList.append(server);
           }
           inputFile.close();
           serverList->addItem("New Server...");
        }
    }else{
        QFile file(rutaServers);
        file.close();
        serverList->addItem("New Server...");
    }
}

/**
 * @brief Slot function that is executed when a server is clicked
 * 
 */
void spslidarUploadDlg::serverClicked(){
    QString choose=serverList->currentItem()->text();
    serverName->setEnabled(false);
    serverIP->setEnabled(false);
    serverPort->setEnabled(false);
    saveButton->setEnabled(false);
    if(choose=="New Server..."){
        serverName->setText("Server Example");
        serverIP->setText("example.com");
        serverPort->setText("8080");
        deleteButton->setEnabled(false);
        serverName->setEnabled(true);
        serverIP->setEnabled(true);
        serverPort->setEnabled(true);
        saveButton->setEnabled(true);
    }else{
        int c = 0;
        bool find = false;
        while (!find && c < serversInfoList.size()) {
            auto info = serversInfoList[c];
            if (info.getName() == choose) {
                find = true;
                serverName->setText(info.getName());
                serverIP->setText(info.getIp());
                serverPort->setText(info.getPort());
                server = "http://" + info.getIp() + ":" + info.getPort();
                deleteButton->setEnabled(true);
            }
            ++c;
        }
    }
}

/**
 * @brief Slot function that is executed when the save button of a server is clicked
 * 
 */
void spslidarUploadDlg::saveServer(){
    bool sameName=false;
    foreach(serverInfo server,serversInfoList){
        QString choose=serverName->text();
        if(server.getName()==choose){
            sameName=true;
        }
    }
    if(sameName){
        QMessageBox::warning(this,"Name Error","There is a server with the same name");
    }else{
        serverInfo server(serverName->text(),serverIP->text(),serverPort->text());
        serversInfoList.append(server);
        this->serverList->takeItem(serverList->count()-1);
        this->serverList->addItem(server.getName());
        this->serverList->addItem("New Server...");

        this->serverName->setEnabled(false);
        this->serverIP->setEnabled(false);
        this->serverPort->setEnabled(false);
        this->saveButton->setEnabled(false);
        this->updateServerDocument();
    }
}

/**
 * @brief Slot function that is executed when the delete button of a server is clicked
 * 
 */
void spslidarUploadDlg::deleteServer(){
    QString choose=serverList->currentItem()->text();
    for(int i=0;i<serversInfoList.count();i++){
        if(serversInfoList[i].getName()==choose) serversInfoList.removeAt(i);
    }
    QListWidgetItem *it = serverList->takeItem(serverList->currentRow());
    delete it;
    deleteButton->setEnabled(false);
    updateServerDocument();
}

/**
 * @brief Auxiliar function that is executed each time a server is saved or is deleted. It save the changes in the document.
 * 
 */
void spslidarUploadDlg::updateServerDocument(){
    QString rutaServers = QString(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)) + "\\spslidar\\servers.txt";
    QFile file(rutaServers);
    file.reset();
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    foreach(serverInfo server, serversInfoList){
        in<<server.getName()+"::"+server.getIp()+"::"+server.getPort()<<Qt::endl;
    }
    file.close();
}

/**
 * @brief Slot function assigned to the button continue in servers page
 * 
 */
void spslidarUploadDlg::serverContinue(){

    if(server.isEmpty()){
        QMessageBox::warning(this,"URL error","You have to select a server before continue");
    } else{
        setListWorkspaces();
        clearList();
    }
}

/**
 * @brief Slot function assigned to the button cancel in servers page
 * 
 */
void spslidarUploadDlg::cancel(){
    this->reject();
}

/**
 * @brief Function to set the list of workspaces from a server
 * 
 */
void spslidarUploadDlg::setListWorkspaces(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces"))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarUploadDlg::readMessage);
    connect(netReply,&QNetworkReply::finished,this,&spslidarUploadDlg::finishReadingWorkspaces);
}

/**
 * @brief Function to set the list of dataset from a workspace in a server
 * 
 */
void spslidarUploadDlg::setListDatasets(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets"))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarUploadDlg::readMessage);
    connect(netReply,&QNetworkReply::finished,this,&spslidarUploadDlg::finishReadingDatasets);
}

/**
 * @brief Auxiliary function to save the body of a network reply in a ByteArray
 * 
 */
void spslidarUploadDlg::readMessage()
{
    dataBuffer.append(netReply->readAll());
}

/**
 * @brief Last part of Network Request of all the workspaces in a server, here we check the response code of the request and process the reply
 * 
 */
void spslidarUploadDlg::finishReadingWorkspaces()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
        cancel();
    }else{
        QString dataBufferRaw=QString::fromStdString(dataBuffer.toStdString());
        if(!dataBufferRaw.isEmpty()){
            QStringList workspacesRaw=dataBufferRaw.split("}");
            workspacesRaw.removeLast();
            foreach(QString workspaceRaw, workspacesRaw){
                workspaceRaw.append("}");
                QJsonObject workspaceJson=QJsonDocument::fromJson(workspaceRaw.toUtf8()).object();
                QString workspace=workspaceJson.value("name").toString();
                workspaceDTO workspaceToList(workspace,workspaceJson.value("description").toString(),workspaceJson.value("cellSize").toInt());
                workspaceDTOList.append(workspaceToList);
                workspacesList->addItem(workspace);
            }
        }
        dataBuffer.clear();
        workspacesList->addItem("New Workspace...");
        stackedWidget->setCurrentIndex(stackedWidget->currentIndex()+1);
    }
}

/**
 * @brief Last part of Network Request of all the datasets in a workspace from a server, here we check the response code of the request and process the reply
 * 
 */
void spslidarUploadDlg::finishReadingDatasets()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
        cancel();
    }else{
        QString up="{";
        QString down="}";
        QString dataBufferRaw=QString::fromStdString(dataBuffer.toStdString());
        if(!dataBufferRaw.isEmpty()){
            QStringList datasetsRaw=dataBufferRaw.split("}\n{");
            foreach(QString datasetRaw, datasetsRaw){
                datasetRaw.remove("\n");
                if(datasetRaw[0]!=up){
                    datasetRaw=up+datasetRaw;
                }
                if(datasetRaw[datasetRaw.size()-1]!=down){
                    datasetRaw.append(down);
                }
                QJsonObject datasetJson=QJsonDocument::fromJson(datasetRaw.toUtf8()).object();
                QJsonObject bounding=datasetJson.value("boundingBox").toObject();
                QJsonObject coordSouth=bounding.value("southWestBottom").toObject();
                QJsonObject coordNorth=bounding.value("northEastTop").toObject();

                QString dataset=datasetJson.value("name").toString();
                datasetsList->addItem(dataset);

                datasetDTO simple;
                coord south(coordSouth["easting"].toString(),coordSouth["northing"].toString(),coordSouth["zone"].toString(),coordSouth["height"].toString());
                coord north(coordNorth["easting"].toString(),coordNorth["northing"].toString(),coordNorth["zone"].toString(),coordNorth["height"].toString());
                boundingBoxDTO box(south,north);
                simple.setName(datasetJson.value("name").toString());
                simple.setDescription(datasetJson.value("description").toString());
                simple.setDataBlockSize(datasetJson.value("dataBlockSize").toInt());
                simple.setDataBlockFormat("LAZ");
                simple.setDateOfAcquisition(QDateTime());
                simple.setBoundingBox(box);
                datasetDTOList.append(simple);
            }
        }
        dataBuffer.clear();
        datasetsList->addItem("New Dataset...");
    }
}

/**
 * @brief Slot function that is executed each time a workspace is clicked
 * 
 */
void spslidarUploadDlg::clickWorkspace(){
    QString item = workspacesList->currentItem()->text();
    datasetNameLine->clear();
    datasetDescriptionText->clear();
    datasetSizeLine->clear();
    if(item!=nullptr){
        if(item=="New Workspace..."){
            int result = newWorkspace.exec();
            if(result == QDialog::Accepted){
                datasetsList->clear();
                workspaceDTO workspaceDTO=newWorkspace.getWorkspace();
                QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces"))};
                req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                QJsonObject json;
                json.insert("name",workspaceDTO.getName());
                json.insert("description",workspaceDTO.getDescription());
                json.insert("cellSize",workspaceDTO.getSize());
                QJsonDocument doc(json);
                QByteArray data = doc.toJson();
                qInfo()<< QString::fromStdString(data.toStdString());
                netReply = netManager->post(req, data);
                connect(netReply,&QNetworkReply::finished,this,&spslidarUploadDlg::finishPostWorkspace);
            }
            workspacesList->clearSelection();
        }else{
            workspace=item;
            int c = 0;
            bool find = false;
            while (!find && c < workspaceDTOList.size()) {
                auto info = workspaceDTOList[c];
                if (info.getName() == item) {
                    find = true;
                    workspaceNameLine->setText(info.getName());
                    workspaceDestriptionText->clear();
                    workspaceDestriptionText->appendPlainText(info.getDescription());
                    workspaceCellLine->setText(QString::number(info.getSize()));
                }
                ++c;
            }
            datasetsList->clear();
            setListDatasets();
        }
    }
}

/**
 * @brief Slot function that is executed each time a dataset is clicked
 * 
 */
void spslidarUploadDlg::clickDataset(){
    QString item = datasetsList->currentItem()->text();
    if(item!=nullptr){
        if(item=="New Dataset..."){
            int result = newDataset.exec();
            if(result == QDialog::Accepted){
                datasetDTO datasetDTO=newDataset.getDataset();
                datasetDTOList.append(datasetDTO);
                QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets"))};
                req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                QJsonObject coordSouth,coordNorth,box,datasetJson;

                coordSouth.insert("easting",datasetDTO.getBoundingBox().getSouthWestBottom().getEasting());
                coordSouth.insert("northing",datasetDTO.getBoundingBox().getSouthWestBottom().getNorthing());
                coordSouth.insert("zone",datasetDTO.getBoundingBox().getSouthWestBottom().getZone());
                coordSouth.insert("height",datasetDTO.getBoundingBox().getSouthWestBottom().getHeight());

                coordNorth.insert("easting",datasetDTO.getBoundingBox().getNorthEastTop().getEasting());
                coordNorth.insert("northing",datasetDTO.getBoundingBox().getNorthEastTop().getNorthing());
                coordNorth.insert("zone",datasetDTO.getBoundingBox().getNorthEastTop().getZone());
                coordNorth.insert("height",datasetDTO.getBoundingBox().getNorthEastTop().getHeight());

                box.insert("southWestBottom",coordSouth);
                box.insert("northEastTop",coordNorth);

                datasetJson.insert("name",datasetDTO.getName());
                datasetJson.insert("description",datasetDTO.getDescription());

                QString date;
                date=dateToString(datasetDTO.getDateOfAcquisition());

                datasetJson.insert("dateOfAcquisition",date);
                datasetJson.insert("boundingBox",box);
                datasetJson.insert("dataBlockSize",datasetDTO.getDataBlockSize());
                datasetJson.insert("dataBlockFormat",datasetDTO.getDataBlockFormat());

                QJsonDocument doc(datasetJson);
                QByteArray data = doc.toJson();
                qInfo() << QString::fromStdString(data.toStdString());
                netReply = netManager->post(req, data);
                connect(netReply,&QNetworkReply::finished,this,&spslidarUploadDlg::finishPostDataset);
            }
            datasetsList->clearSelection();
        }else{
            dataset=item;
            int c = 0;
            bool find = false;
            while (!find && c < datasetDTOList.size()) {
                auto info = datasetDTOList[c];
                if (info.getName() == item) {
                    find = true;
                    datasetNameLine->setText(info.getName());
                    datasetDescriptionText->clear();
                    datasetDescriptionText->appendPlainText(info.getDescription());
                    datasetSizeLine->setText(QString::number(info.getDataBlockSize()));
                    zone = info.getBoundingBox().getSouthWestBottom().getZone();
                    newDatasetDTO = info;
                }
                ++c;
            }
        }
    }
}

/**
 * @brief Last part of a Network Request to upload a Workspace to the server. We check the response code and if it is accepted, we add it to the Workspaces' list
 * 
 */
void spslidarUploadDlg::finishPostWorkspace(){
    if(netReply->error() != QNetworkReply::NoError){
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
    }else{
        workspaceDTOList.append(newWorkspace.getWorkspace());
        workspacesList->takeItem(workspacesList->count()-1);
        workspacesList->addItem(newWorkspace.getWorkspace().getName());
        workspacesList->addItem("New Workspace...");
    }
}

/**
 * @brief Last part of a Network Request to upload a Dataset to the server. We check the response code and if it is accepted, we add it to the datasets' list
 * 
 */
void spslidarUploadDlg::finishPostDataset(){
    if(netReply->error() != QNetworkReply::NoError){
        QMessageBox::warning(this,"Error",QString("Some data was invalid"));
    }else{
        datasetDTOList.append(newDataset.getDataset());
        datasetsList->takeItem(datasetsList->count()-1);
        datasetsList->addItem(newDataset.getDataset().getName());
        datasetsList->addItem("New Dataset...");
    }
}

/**
 * @brief Slot function that is executed when the back button is clicked
 * 
 */
void spslidarUploadDlg::comeBack(){
    workspaceNameLine->clear();
    workspaceDestriptionText->clear();
    workspaceCellLine->clear();

    datasetNameLine->clear();
    datasetDescriptionText->clear();
    datasetSizeLine->clear();

    stackedWidget->setCurrentIndex(stackedWidget->currentIndex()-1);
    clearList();
}

/**
 * @brief Auxiliary function to clear the lists of the plugin
 * 
 */
void spslidarUploadDlg::clearList(){
    workspacesList->clear();
    datasetsList->clear();
    workspaceDTOList.clear();
    datasetDTOList.clear();
}

/**
 * @brief Auxiliary function to convert a date inf the format DD/MM/YYYY to the format of LocalDateTime from Java
 * 
 * @param date
 * @return 
 */
QString spslidarUploadDlg::dateToString(QDateTime date)
{
    QString newDate;
    newDate.append(QString::number(date.date().year()));

    newDate.append("-");

    int month=date.date().month();
    if(month>=10) newDate.append(QString::number(month));
    else newDate.append("0"+QString::number(month));

    newDate.append("-");

    int day=date.date().day();
    if(day>=10) newDate.append(QString::number(day));
    else newDate.append("0"+QString::number(day));

    newDate.append("T");

    int hour=date.time().hour();
    if(hour>=10) newDate.append(QString::number(hour));
    else newDate.append("0"+QString::number(hour));

    newDate.append(":");

    int minute=date.time().minute();
    if(minute>=10) newDate.append(QString::number(minute));
    else newDate.append("0"+QString::number(minute));

    newDate.append(":");

    int second=date.time().second();
    if(second>=10) newDate.append(QString::number(second));
    else newDate.append("0"+QString::number(second));

    newDate.append(".");

    newDate.append(QString::number(date.time().msec()));

    return newDate;
}

/**
 * @brief Slot function that is executed when the finish button is clicked.
 * 
 */
void spslidarUploadDlg::finish(){
    rute=QString(server+"/spslidar/workspaces/"+workspace+"/datasets/"+dataset);
    accept();
}
