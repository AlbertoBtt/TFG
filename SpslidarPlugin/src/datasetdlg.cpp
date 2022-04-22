#include "datasetdlg.h"
#include "ui_datasetdlg.h"

datasetDlg::datasetDlg(QWidget *parent) :
    QDialog(parent),
    Ui::datasetDlg()
{
    setupUi(this);
}

datasetDlg::datasetDlg(datasetDTO datasetIn, QWidget* parent) :
    QDialog(parent),
    Ui::datasetDlg()
{
    setupUi(this);
    southEastingEdit->setText(datasetIn.getBoundingBox().getSouthWestBottom().getEasting());
    southNorthingEdit->setText(datasetIn.getBoundingBox().getSouthWestBottom().getNorthing());
    southHeightEdit->setText(datasetIn.getBoundingBox().getSouthWestBottom().getHeight());
    southZoneEdit->setText("16N");
    northEastingEdit->setText(datasetIn.getBoundingBox().getNorthEastTop().getEasting());
    northNorthingEdit->setText(datasetIn.getBoundingBox().getNorthEastTop().getNorthing());
    northHeightEdit->setText(datasetIn.getBoundingBox().getNorthEastTop().getHeight());
    northZoneEdit->setText("16N");
}

datasetDlg::~datasetDlg()
{

}

const datasetDTO &datasetDlg::getDataset() const
{
    return dataset;
}

void datasetDlg::setDataset(const datasetDTO &newDataset)
{
    dataset = newDataset;
}

void datasetDlg::finish()
{
    QString name=nameEdit->text();
    QString description=descriptionEdit->toPlainText();
    QString date=dateEdit->text();
    int datablockSize=datablockSizeEdit->text().toInt();
    QString datablockFormat=datablockFormatEdit->text();

    QString northEasting=northEastingEdit->text();
    QString northNorthing=northNorthingEdit->text();
    QString northZone=northZoneEdit->text();
    QString northHeight=northHeightEdit->text();

    QString southEasting=southEastingEdit->text();
    QString southNorthing=southNorthingEdit->text();
    QString southZone=southZoneEdit->text();
    QString southHeight=southHeightEdit->text();

    coord north(northEasting,northNorthing,northZone,northHeight);
    coord south(southEasting,southNorthing,southZone,southHeight);
    boundingBoxDTO box(south,north);
    if(checkDatasetData()&&checkDatasetNorth()&&checkDatasetSouth()){
        if(date.count("/")==2){
            QList<QString> split=date.split("/");
            QDate dateFormat(split[2].toInt(),split[1].toInt(),split[0].toInt());
            QLocale locale  = QLocale(QLocale::English, QLocale::UnitedKingdom);
            QDateTime dateAndTime(dateFormat);
            dataset=datasetDTO(name,description, dateAndTime,datablockSize,
                               datablockFormat,box);
            accept();
        }else{
            QMessageBox::warning(this,"Error",QString("Invalid date format"));
        }
    }else{
        QMessageBox::warning(this,"Error",QString("Some cell is empty"));
    }
}

bool datasetDlg::checkDatasetData(){
    QString name=nameEdit->text();
    QString description=descriptionEdit->toPlainText();
    QString date=dateEdit->text();
    int datablockSize=datablockSizeEdit->text().toInt();
    QString datablockFormat=datablockFormatEdit->text();
    if(name.isEmpty()||description.isEmpty()||date.isEmpty()||date.isEmpty()||datablockSize<100||datablockFormat.isEmpty()){
        return false;
    }
    return true;
}

bool datasetDlg::checkDatasetNorth()
{
    QString northEasting=northEastingEdit->text();
    QString northNorthing=northNorthingEdit->text();
    QString northZone=northZoneEdit->text();
    QString northHeight=northHeightEdit->text();
    if(northEasting.isEmpty()||northNorthing.isEmpty()||northZone.isEmpty()||northHeight.isEmpty()){
        return false;
    }
    return true;
}

bool datasetDlg::checkDatasetSouth()
{
    QString southEasting=southEastingEdit->text();
    QString southNorthing=southNorthingEdit->text();
    QString southZone=southZoneEdit->text();
    QString southHeight=southHeightEdit->text();
    if(southEasting.isEmpty()||southNorthing.isEmpty()||southZone.isEmpty()||southHeight.isEmpty()){
        return false;
    }
    return true;
}
