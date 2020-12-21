#ifndef DEVICETABLEWIDGET_H
#define DEVICETABLEWIDGET_H

#include <DTableWidget>

DWIDGET_USE_NAMESPACE

class DeviceTableWidgetDelegate;

class DeviceTableWidget : public DTableWidget
{
    Q_OBJECT

public:
    explicit DeviceTableWidget(DWidget *parent = nullptr);

protected:
    void initUI();


private:

    DeviceTableWidgetDelegate *mp_delegate;

};

#endif // DEVICETABLEWIDGET_H
