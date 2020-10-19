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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

#include <DMainWindow>
#include <DStackedWidget>

class WaitingWidget;
class DeviceWidget;
class ThreadPool;

using namespace Dtk::Widget;

/**
 * @brief The MainWindow class
 * 界面，主窗口
 */
class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
};

#endif // MAINWINDOW_H
