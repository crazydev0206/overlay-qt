#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //[0] : Get path where "sysmacoverlay" is running
    QString path = a.applicationDirPath();
    path.truncate(path.indexOf("Contents") );
    QString m_path = path + "Contents/MacOS/sysmacoverlay";
    //[0]
    
    MainWindow w;
    w.setProPath(m_path);
    w.show();
    
    return a.exec();
}
