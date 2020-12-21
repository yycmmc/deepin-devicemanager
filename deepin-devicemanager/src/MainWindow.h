#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DWidget>

DWIDGET_USE_NAMESPACE

class DeviceTableWidget;

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

signals:

public slots:


private:
    DeviceTableWidget *mp_Table;
    DWidget *mp_CenterWidget;
};

#endif // MAINWINDOW_H
