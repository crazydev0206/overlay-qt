#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QCloseEvent>
#include <libproc.h>
#include <stdio.h>
#include <string.h>
#include <QProcess>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setProPath(QString path){
        m_path = path;
    };
protected:
    void timerEvent(QTimerEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
private:

    void find_pids(const char *name);
    void startPro();

    Ui::MainWindow *ui;
    int m_ct;
    QBasicTimer *m_timer;
    QString m_path;


};
#endif // MAINWINDOW_H
