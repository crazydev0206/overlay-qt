#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setUiProperty();
    setMovie();
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUiProperty(){

    setStyleSheet("background:transparent;");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

void MainWindow::setMovie(){

    m_background_gif = new QMovie(":/res/snow.gif");
    m_background_gif->start();

    m_timer = new QBasicTimer;
    m_timer->start(50,this);
}

void MainWindow::init(){

    m_path = NULL;
    ui->setupUi(this);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void MainWindow::timerEvent(QTimerEvent* event){
    if( event->timerId() != m_timer->timerId() ) return ;

    find_pids("mcwrite");
    m_pix = m_background_gif->currentPixmap();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent* event){

    QPainter painter(this);
    painter.drawPixmap(rect(),m_pix);
}

//[1] : Find process named "name"
//      If Process is not running : m_checkFlg = true and then run startPro();
//                                  m_checkFlg = false : "mcwrite" is running
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
//[1]
//[2] : Create new Process with Special path ("mcwrite path")
void MainWindow::startPro(){

    QProcess *process_detect = new QProcess();

    QString path = m_path + "/mcwrite.app";
    QStringList arguments;
    arguments << "-style" << "fusion";
    process_detect->start(path, arguments);

}
//[2]