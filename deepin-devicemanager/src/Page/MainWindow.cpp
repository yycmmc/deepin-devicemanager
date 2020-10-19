// 项目自身文件
#include "MainWindow.h"

#include <QDateTime>
#include <QDebug>

#include "./LoadInfo/ThreadPool.h"

DWIDGET_USE_NAMESPACE



MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    qint64 dtBegin = QDateTime::currentMSecsSinceEpoch();
    ThreadPool *pool = new ThreadPool;
    pool->generateDeviceFile();
    pool->waitForDone(-1);
    qint64 dtEnd = QDateTime::currentMSecsSinceEpoch();
    qDebug() << "***************** " << dtEnd - dtBegin;
}

MainWindow::~MainWindow()
{
}

