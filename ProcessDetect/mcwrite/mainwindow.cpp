#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    setStyleSheet("background:transparent;");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_TranslucentBackground,true);

    m_timer = new QBasicTimer;
    m_timer->start(50,this);
    m_path = NULL;
    m_ct = 0;

  //  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* event){

    if( event->timerId() != m_timer->timerId() || m_ct >= 20*60*10) return ;

    m_ct ++;
    find_pids("sysmacoverlay");
}

void MainWindow::find_pids(const char *name)
{
    pid_t pids[2048];
    bool m_checkFlg = true;
    int bytes = proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    int n_proc = bytes / sizeof(pids[0]);
    for (int i = 0; i < n_proc; i++) {
        struct proc_bsdinfo proc;
        int st = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0,
                             &proc, PROC_PIDTBSDINFO_SIZE);
        if (st == PROC_PIDTBSDINFO_SIZE) {
            if (strcmp(name, proc.pbi_name) == 0) {
                /* Process PID */
                m_checkFlg = false;
            }
        }
    }
    if(m_checkFlg){
       startPro();

    }

}

void MainWindow::startPro(){

    QProcess *pro = new QProcess();

//    QString path = "/Volumes/sysmacoverlay/sysmacoverlay.app/Contents/MacOS/sysmacoverlay";
//    QString path = m_path.replace(QString("sysoverlaydetect"), QString("sysmacoverlay")) + "/sysmacoverlay";
//    QMessageBox::information(NULL, "", path);
//    QString path = m_path + "/sysmacoverlay";
    QStringList arguments;
    arguments << "-style" << "fusion";

//    QMessageBox::information(NULL, "", path);
    pro->start(m_path, arguments);

}

void MainWindow::closeEvent(QCloseEvent *event){

    event->ignore();
}
