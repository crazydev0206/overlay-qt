#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>
#include <QMovie>
#include <QPainter>
#include <QCloseEvent>
#include <QEvent>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QMessageBox>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QHideEvent>
#include <QProcess>
#include <QStandardPaths>
#include <libproc.h>
#include <stdio.h>
#include <string.h>

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
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
    void hideEvent(QHideEvent* event) override;

private:
    Ui::MainWindow *ui;

    QMovie *m_background_gif;
    int m_ct;
    QPixmap m_pix;
    QBasicTimer *m_timer;

    void find_pids(const char *name);
    void startPro();
    QString m_path;
};
#endif // MAINWINDOW_H
