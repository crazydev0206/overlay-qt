#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QProcess>
//[0-2] : Get full path which has to autorun
QString macOSXAppBundlePath()
{
    QDir dir = QDir ( QApplication::applicationDirPath() );
    dir.cdUp();
    dir.cdUp();
    QString absolutePath = dir.absolutePath();
    // absolutePath will contain a "/" at the end,
    // but we want the clean path to the .app bundle
    if ( absolutePath.length() > 0 && absolutePath.right(1) == "/" ) {
        absolutePath.chop(1);
    }
    return absolutePath;

}
//[0-2]
//[0-1] : Get process name which added in 
QString macOSXAppBundleName()
{
    QString bundlePath = macOSXAppBundlePath();
    QFileInfo fileInfo(bundlePath);
    QString pro_name = fileInfo.baseName();
    return pro_name;

}
//[0-1]
//[0] : Manage autorun program
void setAppToStartAutomatically ( bool startAutomatically )
{

    // Remove any existing login entry for this app first, in case there was one
    // from a previous installation, that may be under a different launch path.
   {
       QStringList args;
       args << "-e tell application \"System Events\" to delete login item \""
           + macOSXAppBundleName() + "\"";
       QProcess::execute("osascript", args);
   }

    // Now install the login item, if needed.
    if (startAutomatically){
        
        QStringList args;
        QString pro_path = macOSXAppBundlePath();
        args << "-e tell application \"System Events\" to make login item at end with properties {path:\"" + pro_path + "\", hidden:false}";

        QProcess::execute("osascript", args);
    }
}
//[0]
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(overlay);

    QApplication a(argc, argv);
    //Get path where program is running
    QString load_path = a.applicationDirPath();
    //Manage autorun program
    setAppToStartAutomatically(true);

    MainWindow w;
    w.setProPath(load_path);
    w.showMaximized();

    return a.exec();
}
