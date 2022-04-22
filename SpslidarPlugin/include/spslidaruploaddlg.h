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
    QList<serverInfo> serversInfoList;
    QList<workspaceDTO> workspaceDTOList;
    QList<datasetDTO> datasetDTOList;
    QString server;
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QByteArray dataBuffer;
    QString workspace;
    QString dataset;
    workspaceDlg newWorkspace;
    datasetDlg newDataset;
    QString rute;
    QString zone;
    datasetDTO newDatasetDTO;
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
