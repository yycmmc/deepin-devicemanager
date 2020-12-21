#include "DeviceTableWidget.h"

#include "DeviceTableWidgetDelegate.h"

#include <QTableWidgetItem>
#include <QHeaderView>

DeviceTableWidget::DeviceTableWidget(DWidget *parent)
    : DTableWidget(parent)
    , mp_delegate(nullptr)
{
    initUI();
}

void DeviceTableWidget::initUI()
{
    mp_delegate = new DeviceTableWidgetDelegate(this);
    setItemDelegate(mp_delegate);

    // 隐藏网格线
    this->setShowGrid(false);
    this->viewport()->setAutoFillBackground(true);

    this->setRowCount(10);
    this->setColumnCount(3);

    // 设置最后一个section拉伸填充
    this->horizontalHeader()->setStretchLastSection(true);

    // 设置行高
    this->verticalHeader()->setDefaultSectionSize(40);


    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem("this");
            setItem(i, j, item);
        }
    }
}
