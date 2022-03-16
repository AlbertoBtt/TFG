#include "spslidardlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    spslidarDlg w;
    w.show();
    return a.exec();
}
