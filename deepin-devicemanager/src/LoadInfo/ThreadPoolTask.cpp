#include "ThreadPoolTask.h"

#include <QTime>
#include <QProcess>
#include <QFile>
#include <QDebug>

ThreadPoolTask::ThreadPoolTask(QString cmd, QString file, bool replace, QObject *parent)
    : QObject(parent),
      m_Cmd(cmd),
      m_File(file),
      m_CanNotReplace(replace)
{

}

ThreadPoolTask::~ThreadPoolTask()
{

}

void ThreadPoolTask::run()
{
    // 不用重新采集的信息，如果文件存在就不需要重新采集
    QFile file("/opt/test/" + m_File);
    if (m_CanNotReplace && file.exists()) {
        return;
    }

    QProcess process;
    process.start(m_Cmd);

    process.waitForFinished(-1);
    QString info = process.readAllStandardOutput();

    int exitCode = process.exitCode();
    if (exitCode == 127 || exitCode == 126) {
        info = "";
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(info.toStdString().data());
    }

}
