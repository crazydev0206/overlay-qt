#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString path = a.applicationDirPath();
    path.truncate(path.indexOf("Contents") );
    QString m_path = path + "Contents/MacOS/sysmacoverlay";
//    QMessageBox::information(NULL, "", m_path);
    MainWindow w;
    w.setProPath(m_path);
    w.show();
    return a.exec();
}
