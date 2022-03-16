#include "spslidardlg.h"
#include "./ui_spslidardlg.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QtCore>

spslidarDlg::spslidarDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::spslidarDlg)
{
    ui->setupUi(this);
    clearValues();
    netManager = new QNetworkAccessManager(this);
    getServers();
}

spslidarDlg::~spslidarDlg()
{
    delete ui;
}

QString spslidarDlg::getDataset()
{
    return dataset;
}

QString spslidarDlg::getRuta()
{
    return ruta;
}

void spslidarDlg::getServers(){
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
              ui->serverList->addItem(attributes[0]);
              serversInfoList.append(server);
           }
           inputFile.close();
           ui->serverList->addItem("New Server...");
        }
    }else{
        QFile file(rutaServers);
        file.close();
        ui->serverList->addItem("New Server...");
    }
}

void spslidarDlg::serverClicked(){
    QString choose=ui->serverList->currentItem()->text();
    ui->serverName->setEnabled(false);
    ui->serverIP->setEnabled(false);
    ui->serverPort->setEnabled(false);
    ui->saveButton->setEnabled(false);
    if(choose=="New Server..."){
        ui->serverName->setText("Server Example");
        ui->serverIP->setText("example.com");
        ui->serverPort->setText("8080");
        ui->deleteButton->setEnabled(false);
        ui->serverName->setEnabled(true);
        ui->serverIP->setEnabled(true);
        ui->serverPort->setEnabled(true);
        ui->saveButton->setEnabled(true);
    }else{
        foreach(serverInfo info, serversInfoList){
            if(info.getName()==choose){
                ui->serverName->setText(info.getName());
                ui->serverIP->setText(info.getIp());
                ui->serverPort->setText(info.getPort());
                server = "http://" + info.getIp() + ":" + info.getPort();
                ui->deleteButton->setEnabled(true);
                break;
            }
        }
    }
}

void spslidarDlg::saveServer(){
    bool sameName=false;
    foreach(serverInfo server,serversInfoList){
        QString choose=ui->serverName->text();
        if(server.getName()==choose){
            sameName=true;
        }
    }
    if(sameName){
        QMessageBox::warning(this,"Name Error","There is a server with the same name");
    }else{
        serverInfo server(ui->serverName->text(),ui->serverIP->text(),ui->serverPort->text());
        serversInfoList.append(server);
        ui->serverList->takeItem(ui->serverList->count()-1);
        ui->serverList->addItem(server.getName());
        ui->serverList->addItem("New Server...");

        ui->serverName->setEnabled(false);
        ui->serverIP->setEnabled(false);
        ui->serverPort->setEnabled(false);
        ui->saveButton->setEnabled(false);
        updateServerDocument();
    }
}

void spslidarDlg::deleteServer(){
    QString choose=ui->serverList->currentItem()->text();
    for(int i=0;i<serversInfoList.count();i++){
        if(serversInfoList[i].getName()==choose) serversInfoList.removeAt(i);
    }
    QListWidgetItem *it = ui->serverList->takeItem(ui->serverList->currentRow());
    delete it;
    ui->deleteButton->setEnabled(false);
    updateServerDocument();
}

void spslidarDlg::updateServerDocument(){
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

void spslidarDlg::serverContinue(){

    if(server.isEmpty()){
        QMessageBox::warning(this,"URL error","You have to select a server before continue");
    } else{
        setListWorkspaces();
        clearList();
        ui->serverContinue->setEnabled(false);
        ui->serverContinue->setText("Connecting");
    }
}

void spslidarDlg::workspaceContinue(){
    if(workspace!=nullptr&&dataset!=nullptr){
        setDataset();
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }else{
        QMessageBox::warning(this,"Dataset error","You have to select a Dataset before continue");
    }

}

void spslidarDlg::confirm(){
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    descargarDataset();
}

void spslidarDlg::clickWorkspace(){
    QString item = ui->workspaceList->currentItem()->text();
    if(item!=nullptr) workspace=item;
    qInfo(workspace.toStdString().c_str());
    ui->datasetList->clear();
    setListDatasets();
}

void spslidarDlg::clickDataset(){
    QString item = ui->datasetList->currentItem()->text();
    if(item!=nullptr) dataset=item;
    qInfo() << dataset.toStdString().c_str();
}


void spslidarDlg::setListWorkspaces(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces"))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarDlg::leerMensaje);
    connect(netReply,&QNetworkReply::finished,this,&spslidarDlg::terminarLeerListaWorkspace);
}

void spslidarDlg::setListDatasets(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets"))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarDlg::leerMensaje);
    connect(netReply,&QNetworkReply::finished,this,&spslidarDlg::terminarLeerListaDataset);
}

void spslidarDlg::setDataset(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets/"+dataset))};
    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&spslidarDlg::leerMensaje);
    connect(netReply,&QNetworkReply::finished,this,&spslidarDlg::terminarLeerDataset);
}

void spslidarDlg::descargarDataset(){
    QNetworkRequest req{QUrl(QString(server+"/spslidar/workspaces/"+workspace+"/datasets/"+dataset+"/data"))};
    qDebug() << QString(server+"/spslidar/workspaces/"+workspace+"/datasets/"+dataset+"/data");
    netReply = netManager->get(req);
    connect(netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(actualizarProgreso(qint64, qint64)));
    connect(netReply,&QNetworkReply::finished,this,&spslidarDlg::terminarLeerDatasetData);

}

void spslidarDlg::leerMensaje()
{
    dataBuffer.append(netReply->readAll());
}

void spslidarDlg::actualizarProgreso(qint64 ist, qint64 max){
    ui->progreso->setMaximum(max);
    ui->progreso->setValue(ist);
}
void spslidarDlg::terminarLeerListaWorkspace()
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
                qInfo(workspace.toStdString().c_str());
                ui->workspaceList->addItem(workspace);
            }
        }
        dataBuffer.clear();
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }
}

void spslidarDlg::terminarLeerListaDataset()
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
                QString dataset=datasetJson.value("name").toString();
                qInfo(dataset.toStdString().c_str());
                ui->datasetList->addItem(dataset);
            }
        }
        dataBuffer.clear();
    }
}

void spslidarDlg::terminarLeerDataset()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
        cancel();
    }else{
        QJsonDocument datasetDocument=QJsonDocument::fromJson(dataBuffer);
        QJsonObject datasetObject=datasetDocument.object();

        //Obtenemos datos básicos del dataset
        ui->output_nombre->setText(datasetObject.value("name").toString());
        ui->output_descripcion->setText(datasetObject.value("description").toString());
        ui->output_fecha->setText(datasetObject.value("dateOfAcquisition").toString().replace("T"," "));
        int dataBlockSize=datasetObject.value("dataBlockSize").toInt();
        ui->output_tamDatablock->setText(QString::number(dataBlockSize));
        ui->output_formatoDatablock->setText(datasetObject.value("dataBlockFormat").toString());

        //Preprocesamos boundingBox
        QJsonObject boundingBox = datasetObject.value("boundingBox").toObject();

        //Procesamos punto Suroeste
        int este, norte, altura;
        QJsonObject suroeste = boundingBox.value("southWestBottom").toObject();
        altura=suroeste.value("height").toInt();
        norte=suroeste.value("northing").toInt();
        este=suroeste.value("easting").toInt();

        ui->output_suroeste_altura->setText(QString::number(altura));
        ui->output_suroeste_norte->setText(QString::number(norte));
        ui->output_suroeste_este->setText(QString::number(este));
        ui->output_suroeste_zona->setText(suroeste.value("zone").toString());

        //Procesamos punto Noreste
        QJsonObject noreste = boundingBox.value("northEastTop").toObject();
        altura=noreste.value("height").toInt();
        norte=noreste.value("northing").toInt();
        este=noreste.value("easting").toInt();

        ui->output_noreste_altura->setText(QString::number(altura));
        ui->output_noreste_norte->setText(QString::number(norte));
        ui->output_noreste_este->setText(QString::number(este));
        ui->output_noreste_zona->setText(noreste.value("zone").toString());


        dataBuffer.clear();
    }
}

void spslidarDlg::terminarLeerDatasetData()
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
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(netReply->readAll());
        qDebug() << file.errorString();
        accept();
    }
}

void spslidarDlg::clearValues(){
    netReply=nullptr;
    dataBuffer.clear();
    workspace=nullptr;
    dataset=nullptr;
}

void spslidarDlg::cancel(){
    this->reject();
}

void spslidarDlg::comeBack(){
    ui->serverContinue->setEnabled(true);
    ui->serverContinue->setText("Continue");
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    clearList();
}

void spslidarDlg::comeBackDataset(){
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
}

void spslidarDlg::clearList(){
    ui->workspaceList->clear();
    ui->datasetList->clear();
}

