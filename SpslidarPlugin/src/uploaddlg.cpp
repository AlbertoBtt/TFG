#include "uploaddlg.h"
#include "ui_uploaddlg.h"

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

UploadDlg::~UploadDlg()
{

}

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

void UploadDlg::finishPostCloud(){
    if(netReply->error() != QNetworkReply::NoError){
            qDebug() << "Error : " << netReply->errorString();
            QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
            reject();
     }else{
            accept();
     }
}

void UploadDlg::updateProgress(qint64 a, qint64 b){
    if(b>0){
        progressBar->setValue(100*a/b);
    }
}
