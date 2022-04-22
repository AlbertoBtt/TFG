#ifndef DATASETDLG_H
#define DATASETDLG_H

#include <QDialog>
#include <datasetdto.h>
#include <boundingbox.h>
#include <coord.h>
#include <QMessageBox>
#include "ui_datasetdlg.h"

class datasetDlg : public QDialog, public Ui::datasetDlg
{
    Q_OBJECT

public:
    explicit datasetDlg(QWidget *parent = nullptr);
    datasetDlg(datasetDTO datasetIn, QWidget* parent = nullptr);
    ~datasetDlg();

    const datasetDTO &getDataset() const;
    void setDataset(const datasetDTO &newDataset);

private:
    datasetDTO dataset;

    bool checkDatasetData();
    bool checkDatasetNorth();
    bool checkDatasetSouth();
private slots:
    void finish();
};

#endif // DATASETDLG_H
