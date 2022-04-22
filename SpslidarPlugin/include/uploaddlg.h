#ifndef UPLOADDLG_H
#define UPLOADDLG_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QFile>
#include <QMessageBox>
#include "ui_uploaddlg.h"

class UploadDlg : public QDialog, Ui::UploadDlg
{
    Q_OBJECT
public:
    UploadDlg(QWidget *parent = nullptr, QString _rute="", QString _cloudRute="");
    ~UploadDlg();

private:
    QString rute;
    QString cloudRute;
    QNetworkAccessManager* netManager;
    QNetworkReply* netReply;
    void sendCloud();
private slots:
    void finishPostCloud();
    void updateProgress(qint64 a, qint64 b);
};
#endif // UPLOADDLG_H
