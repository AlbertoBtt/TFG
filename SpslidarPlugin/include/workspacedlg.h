#ifndef WORKSPACEDLG_H
#define WORKSPACEDLG_H

#include <QDialog>
#include "workspacedto.h"
#include <QMessageBox>
#include "ui_workspacedlg.h"


class workspaceDlg : public QDialog, public Ui::workspaceDlg
{
    Q_OBJECT

public:
    workspaceDlg(QWidget *parent = nullptr);
    ~workspaceDlg();

    const workspaceDTO &getWorkspace() const;

private:
    workspaceDTO workspace;
private slots:
    void finish();
};

#endif // WORKSPACEDLG_H
