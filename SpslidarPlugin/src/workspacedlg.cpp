#include "workspacedlg.h"
#include "ui_workspacedlg.h"

workspaceDlg::workspaceDlg(QWidget *parent) :
    QDialog(parent),
    Ui::workspaceDlg()
{
    setupUi(this);
}

workspaceDlg::~workspaceDlg()
{

}

const workspaceDTO &workspaceDlg::getWorkspace() const
{
    return workspace;
}

void workspaceDlg::finish(){
    QString name=nameText->text();
    QString description=descriptionText->toPlainText();
    int size=sizeText->text().toInt();
    if(!name.isEmpty() && !description.isEmpty() && size>=100 && size <= 1000000){
        workspace=workspaceDTO(name,description,size);
        this->accept();
    }else{
        QMessageBox::warning(this,"Error","One of the fields is empty or the datablock size is out of range");
    }
}
