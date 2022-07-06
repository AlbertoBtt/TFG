/*****************************************************************//**
 * @file   spslidardownloaddlg.cpp
 * @brief  Functions implementation from spslidardownloaddlg.h
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

#include "spslidardownloaddlg.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QtCore>

spslidarDownloadDlg::spslidarDownloadDlg(QWidget *parent)
    : QDialog(parent)
    , Ui::spslidarDownloadDlg()
{
    setupUi(this);
    clearValues();
    netManager = new QNetworkAccessManager(this);
    getServers();
}

spslidarDownloadDlg::~spslidarDownloadDlg()
{
}

/**
 * @brief Return the name of the dataset
 * 
 * @return The name of the dataset 
 */
QString spslidarDownloadDlg::getDataset()
{
    return dataset;
}
/**
 * @brief Return the rute where the cloud is downloaded
 * 
 * @return The rute
 */
QString spslidarDownloadDlg::getRuta()
{
    return ruta;
}

/**
 * @brief Get the saved servers in servers.txt
 * 
 */
void spslidarDownloadDlg::getServers(){
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
 * @brief Slot function which is executed when server is clicked in the server selection page
 */
void spslidarDownloadDlg::serverClicked(){
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
 * @brief Slot function which is executed when we click save in the server selection page
 * 
 * @return 
 */
void spslidarDownloadDlg::saveServer(){
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
        serverList->takeItem(serverList->count()-1);
        serverList->addItem(server.getName());
        serverList->addItem("New Server...");

        serverName->setEnabled(false);
        serverIP->setEnabled(false);
        serverPort->setEnabled(false);
        saveButton->setEnabled(false);
        updateServerDocument();
    }
}

/**
 * @brief Slot function which is executed when the delete button is clicked
 * 
 */
void spslidarDownloadDlg::deleteServer(){
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
 * @brief Auxiliar fuction which saves changes in the servers' list
 */
void spslidarDownloadDlg::updateServerDocument(){
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
 * @brief Slot function which is activated when we click the continue button in the servers page
 * 
 */
void spslidarDownloadDlg::serverContinue(){

    if(server.isEmpty()){
        QMessageBox::warning(this,"URL error","You have to select a server before continue");
    } else{
        setListWorkspaces();
        clearList();
        //serverContinue->setEnabled(false);
        //serverContinue->setText("Connecting");
    }
}

/**
 * @brief Slot function which is activated when we click the continue button in the workspace and dataset selection page
 *
 */
void spslidarDownloadDlg::workspaceContinue(){
    if(workspace!=nullptr&&dataset!=nullptr){
        setDataset();
        stackedWidget->setCurrentIndex(stackedWidget->currentIndex()+1);
    }else{
        QMessageBox::warning(this,"Dataset error","You have to select a Dataset before continue");
    }

}

/**
 * @brief Slot function which is activated when we click the confirm button in the dataset's details page
 * 
 */
void spslidarDownloadDlg::confirm(){
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex()+1);
    descargarDataset();
}

/**
 * @brief Slot function which is activated when we click a workspace from the list in the workspace and dataset selection page
 * 
 */
void spslidarDownloadDlg::clickWorkspace(){
    QString item = workspaceList->currentItem()->text();
    if(item!=nullptr) workspace=item;
    qInfo(workspace.toStdString().c_str());
    datasetList->clear();
    setListDatasets();
}

/**
 * @brief Slot function which is activated when we click a dataset from the list in the workspace and dataset selection page
 * 
 */
void spslidarDownloadDlg::clickDataset(){
    QString item = datasetList->currentItem()->text();
    if(item!=nullptr) dataset=item;
    qInfo() << dataset.toStdString().c_str();
}

/**
 * @brief Set the list of workspaces from the server
 * 
 */
void spslidarDownloadDlg::setListWorkspaces(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces"))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarDownloadDlg::leerMensaje);
    connect(netReply,&QNetworkReply::finished,this,&spslidarDownloadDlg::terminarLeerListaWorkspace);
}

/**
 * @brief Set the list of datasets from the server
 * 
 */
void spslidarDownloadDlg::setListDatasets(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets"))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarDownloadDlg::leerMensaje);
    connect(netReply,&QNetworkReply::finished,this,&spslidarDownloadDlg::terminarLeerListaDataset);
}

/**
 * @brief Set the dataset details from the server
 * 
 */
void spslidarDownloadDlg::setDataset(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets/"+dataset))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarDownloadDlg::leerMensaje);
    connect(netReply,&QNetworkReply::finished,this,&spslidarDownloadDlg::terminarLeerDataset);
}

/**
 * @brief Downloads the .laz or .las from the server
 * 
 */
void spslidarDownloadDlg::descargarDataset(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets/"+dataset+"/data"))};
    qDebug() << QString(server+"/spslidar/workspaces/"+workspace+"/datasets/"+dataset+"/data");
    netReply = netManager->get(req);
    connect(netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(actualizarProgreso(qint64, qint64)));
    connect(netReply,&QNetworkReply::finished,this,&spslidarDownloadDlg::terminarLeerDatasetData);

}

/**
 * @brief Saves the body of the reply in the ByteArray
 * 
 */
void spslidarDownloadDlg::leerMensaje()
{
    dataBuffer.append(netReply->readAll());
}

/**
 * @brief Updates the download progress bar
 * 
 * @param ist The actual value
 * @param max The maximum value
 */
void spslidarDownloadDlg::actualizarProgreso(qint64 ist, qint64 max){
    progreso->setMaximum(max);
    progreso->setValue(ist);
}

/**
 * @brief Proccess the ByteArray to obtain the list of Workspaces
 */
void spslidarDownloadDlg::terminarLeerListaWorkspace()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
        cancel();
    }else{
        QString dataBufferRaw=QString::fromStdString(dataBuffer.toStdString());
        if(!dataBufferRaw.isEmpty()){
            QStringList workspacesRaw=dataBufferRaw.split("\n");
            workspacesRaw.removeLast();
            foreach(QString workspaceRaw, workspacesRaw){
                QJsonObject workspaceJson=QJsonDocument::fromJson(workspaceRaw.toUtf8()).object();
                QString workspace=workspaceJson.value("name").toString();
                qInfo(workspace.toStdString().c_str());
                workspaceList->addItem(workspace);
            }
        }
        dataBuffer.clear();
        stackedWidget->setCurrentIndex(stackedWidget->currentIndex()+1);
    }
}

/**
 * @brief Proccess the ByteArray to obtain the list of Datasets
 */
void spslidarDownloadDlg::terminarLeerListaDataset()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
        cancel();
    }else{
        QString dataBufferRaw=QString::fromStdString(dataBuffer.toStdString());
        if(!dataBufferRaw.isEmpty()){
            QStringList datasetsRaw=dataBufferRaw.split("\n");
            datasetsRaw.removeLast();
            foreach(QString datasetRaw, datasetsRaw){
                QJsonObject datasetJson=QJsonDocument::fromJson(datasetRaw.toUtf8()).object();
                QString dataset=datasetJson.value("name").toString();
                qInfo(dataset.toStdString().c_str());
                datasetList->addItem(dataset);
            }
        }
        dataBuffer.clear();
    }
}

/**
 * @brief Proccess the ByteArray to obtain the details of the dataset
 * 
 */
void spslidarDownloadDlg::terminarLeerDataset()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
        cancel();
    }else{
        QJsonDocument datasetDocument=QJsonDocument::fromJson(dataBuffer);
        QJsonObject datasetObject=datasetDocument.object();

        //Obtenemos datos básicos del dataset
        output_nombre->setText(datasetObject.value("name").toString());
        output_descripcion->setText(datasetObject.value("description").toString());
        output_fecha->setText(datasetObject.value("dateOfAcquisition").toString().replace("T"," "));
        int dataBlockSize=datasetObject.value("dataBlockSize").toInt();
        output_tamDatablock->setText(QString::number(dataBlockSize));
        output_formatoDatablock->setText(datasetObject.value("dataBlockFormat").toString());

        //Preprocesamos boundingBox
        QJsonObject boundingBox = datasetObject.value("boundingBox").toObject();

        //Procesamos punto Suroeste
        int este, norte, altura;
        QJsonObject suroeste = boundingBox.value("southWestBottom").toObject();
        altura=suroeste.value("height").toInt();
        norte=suroeste.value("northing").toInt();
        este=suroeste.value("easting").toInt();

        output_suroeste_altura->setText(QString::number(altura));
        output_suroeste_norte->setText(QString::number(norte));
        output_suroeste_este->setText(QString::number(este));
        output_suroeste_zona->setText(suroeste.value("zone").toString());

        //Procesamos punto Noreste
        QJsonObject noreste = boundingBox.value("northEastTop").toObject();
        altura=noreste.value("height").toInt();
        norte=noreste.value("northing").toInt();
        este=noreste.value("easting").toInt();

        output_noreste_altura->setText(QString::number(altura));
        output_noreste_norte->setText(QString::number(norte));
        output_noreste_este->setText(QString::number(este));
        output_noreste_zona->setText(noreste.value("zone").toString());


        dataBuffer.clear();
    }
}

/**
 * @brief Adaptate and save the data from a dataset in a .laz file
 * 
 */
void spslidarDownloadDlg::terminarLeerDatasetData()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
        cancel();
    }else{
        QDir dir(QString(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) + "/spslidar/LAZ");
        if (!dir.exists()) dir.mkpath(".");
        ruta = QString(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) + "/spslidar/LAZ/" + dataset + ".laz";
        qDebug() << ruta;
        if (QFile::exists(ruta)) {
            QFile::remove(ruta);
        }
        QFile file(ruta);
        file.open(QIODevice::ReadWrite);
        file.write(netReply->readAll());
        qDebug() << file.errorString();
        accept();
    }
}

/**
 * @brief Initialize the main variables of the program
 * 
 */
void spslidarDownloadDlg::clearValues(){
    netReply=nullptr;
    dataBuffer.clear();
    workspace=nullptr;
    dataset=nullptr;
}

/**
 * @brief Slot function which is activated when the cancel button is clicked
 * 
 */
void spslidarDownloadDlg::cancel(){
    this->reject();
}

/**
 * @brief Slot function which is activated when the comeback button from the workspaces and datasets page
 * 
 */
void spslidarDownloadDlg::comeBack(){
    //serverContinue->setEnabled(true);
    //serverContinue->setText("Continue");
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex()-1);
    clearList();
}

/**
 * @brief Slot function which is activated when the comeback button from the dataset's details page
 *
 */
void spslidarDownloadDlg::comeBackDataset(){
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex()-1);
}

/**
 * @brief Auxiliar function which clear the lists of workspaces and datasets
 * 
 */
void spslidarDownloadDlg::clearList(){
    workspaceList->clear();
    datasetList->clear();
}

