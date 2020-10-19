#ifndef THREADPOOLTASK_H
#define THREADPOOLTASK_H

#include <QObject>
#include <QRunnable>

class ThreadPoolTask : public QObject , public QRunnable
{
    Q_OBJECT
public:
    explicit ThreadPoolTask(QString cmd,QString file,bool replace,QObject *parent = nullptr);
    ~ThreadPoolTask() override;

protected:
    void run() override;

private:
    QString   m_Cmd;                  // cmd
    QString   m_File;                 // file name
    bool      m_CanNotReplace;        // Whether to replace if file existed
};

#endif // THREADPOOLTASK_H
