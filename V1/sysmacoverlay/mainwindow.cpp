#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    m_background_gif = new QMovie(":/res/snow.gif");
 //   QMessageBox::information(NULL, "", "as" );
    m_background_gif->start();

//    setWindowTitle(tr("Systray"));
    setStyleSheet("background:transparent;");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_TranslucentBackground,true);

    m_path = NULL;
    m_timer = new QBasicTimer;
    m_timer->start(50,this);
    m_ct = 0;
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void MainWindow::hideEvent(QHideEvent* event){

    event->ignore();
}
void MainWindow::timerEvent(QTimerEvent* event){
    if( event->timerId() != m_timer->timerId() ) return ;


    m_ct ++;
    find_pids("mcwrite");
    m_pix = m_background_gif->currentPixmap();
    repaint();

}

void MainWindow::paintEvent(QPaintEvent* event){


    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::red));
    painter.drawPixmap(rect(),m_pix);

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

//    QString path = "/Volumes/sysoverlaydetect/sysoverlaydetect.app/Contents/MacOS/sysoverlaydetect";
    QString path = m_path + "/mcwrite.app";
    QStringList arguments;
    arguments << "-style" << "fusion";

//    QMessageBox::information(NULL, "", path);
    pro->start(path, arguments);

}
