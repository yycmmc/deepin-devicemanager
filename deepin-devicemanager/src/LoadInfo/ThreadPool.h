/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     Jun.Liu <liujuna@uniontech.com>
*
* Maintainer: XiaoMei.Ji <jixiaomei@uniontech.com>
* Maintainer: Jun.Liu <liujuna@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QObject>
#include <QThreadPool>
#include <QList>
#include <QVector>

struct Cmd{
    QString cmd;
    QString file;
    bool canNotReplace;
};

class ThreadPool : public QThreadPool
{
    Q_OBJECT
public:
    ThreadPool(QObject *parent = nullptr);

    /**
     * @brief generateDeviceFile : load device info
     */
    void generateDeviceFile();

    /**
     * @brief setRunning : Set the working status of the thread pool
     * @param status : status
     */
    void setRunning(bool status);

    /**
     * @brief running : Get the working status of the thread pool
     * @return : status
     */
    bool running();

private:
    void initCmd();

private:
    bool              m_Running;             // Mark the working status of the thread pool
    QList<Cmd>        m_ListCmd;             // all cmd
};

#endif // THREADPOOL_H
