#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <QProcess>

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


QString macOSXAppBundleName()
{
    QString bundlePath = macOSXAppBundlePath();
    QFileInfo fileInfo(bundlePath);
    QString pro_name = fileInfo.baseName();
    return pro_name;

}
void setAppToStartAutomatically ( bool startAutomatically )
{

    // Remove any existing login entry for this app first, in case there was one
    // from a previous installation, that may be under a different launch path.
//    {
//        QStringList args;
//        args << "-e tell application \"System Events\" to delete login item \""
//            + macOSXAppBundleName() + "\"";
//        QProcess::execute("osascript", args);
//    }

    // Now install the login item, if needed.
    if ( startAutomatically )
    {
        QStringList args;
        QString pro_path = macOSXAppBundlePath();
        args << "-e tell application \"System Events\" to make login item at end with properties {path:\"" + pro_path + "\", hidden:false}";

        QProcess::execute("osascript", args);
    }
}
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(overlay);

    QApplication a(argc, argv);
    setAppToStartAutomatically(true);

    QString path = a.applicationDirPath();
//    QMessageBox::information(NULL, "", path);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "sysmacoverlay_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.setProPath(path);
    w.showMaximized();
//    w.show();

    return a.exec();
}
