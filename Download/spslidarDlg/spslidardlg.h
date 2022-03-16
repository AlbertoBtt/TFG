#ifndef SPSLIDARDLG_H
#define SPSLIDARDLG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include "serverinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class spslidarDlg; }
QT_END_NAMESPACE

class spslidarDlg : public QDialog
{
    Q_OBJECT

public:
    spslidarDlg(QWidget *parent = nullptr);
    ~spslidarDlg();
    QString getDataset();
    QString getRuta();
private:
    Ui::spslidarDlg *ui;
    QString server;
    QString workspace;
    QString dataset;
    void setListWorkspaces();
    void setListDatasets();
    void setDataset();
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QByteArray dataBuffer;
    QString ruta;
    void getServers();
    QList<serverInfo> serversInfoList;
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
