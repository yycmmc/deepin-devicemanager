#include "MainWindow.h"

#include "DeviceTableWidget.h"
#include <QVBoxLayout>


// 主界面需要的一些宏定义
#define INIT_WIDTH  1000    // 窗口的初始化宽度
#define INIT_HEIGHT 720     // 窗口的初始化高度
#define MIN_WIDTH  840      // 窗口的最小宽度
#define MIN_HEIGHT 420      // 窗口的最小高度

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
    , mp_Table(new DeviceTableWidget(nullptr))
    , mp_CenterWidget(new DWidget(this))
{
    // 设置窗口的最小尺寸
    QSize minSize(MIN_WIDTH, MIN_HEIGHT);
    setMinimumSize(minSize);

    // 设置窗口的大小
    QSize initSize(INIT_WIDTH, INIT_HEIGHT);
    resize(initSize);

    // 设置窗口的主控件
    setCentralWidget(mp_CenterWidget);
    setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vLayout = new QVBoxLayout();
    mp_CenterWidget->setLayout(vLayout);
    vLayout->addWidget(mp_Table);
}

MainWindow::~MainWindow()
{

}
