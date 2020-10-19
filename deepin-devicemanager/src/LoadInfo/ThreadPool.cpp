#include "ThreadPool.h"
#include "ThreadPoolTask.h"

#include <QObjectCleanupHandler>
#include <QProcess>
#include <QDir>

ThreadPool::ThreadPool(QObject *parent)
    : QThreadPool(parent)
{
    initCmd();
    QDir dir;
    dir.mkdir("/opt/test");
}

void ThreadPool::generateDeviceFile()
{
    QObjectCleanupHandler *cleaner = new QObjectCleanupHandler;
    cleaner->setParent(this);
    QList<Cmd>::iterator it = m_ListCmd.begin();
    for (; it != m_ListCmd.end(); ++it) {
        ThreadPoolTask *task = new ThreadPoolTask((*it).cmd, (*it).file, (*it).canNotReplace);
        cleaner->add(task);
        start(task);
        task->setAutoDelete(true);
    }
}

void ThreadPool::setRunning(bool status)
{
    m_Running = status;
}

bool ThreadPool::running()
{
    return m_Running;
}

void ThreadPool::initCmd()
{
    // According to Huawei's requirements , Modify the way of judging klu and panguv
    QProcess process;
    process.start("gdbus introspect -y -d com.deepin.system.SystemInfo -o /com/deepin/system/SystemInfo -p");
    process.waitForFinished(-1);
    QString info = process.readAllStandardOutput();


    Cmd cmdLshw;
    cmdLshw.cmd = "lshw";
    cmdLshw.file = "lshw.txt";
    cmdLshw.canNotReplace = false;
    m_ListCmd.append(cmdLshw);

    Cmd cmdDmi0;
    cmdDmi0.cmd = "dmidecode -t 0";
    cmdDmi0.file = "dmidecode_0.txt";
    cmdDmi0.canNotReplace = true;
    m_ListCmd.append(cmdDmi0);

    Cmd cmdDmi1;
    cmdDmi1.cmd = "dmidecode -t 1";
    cmdDmi1.file = "dmidecode_1.txt";
    cmdDmi1.canNotReplace = true;
    m_ListCmd.append(cmdDmi1);

    Cmd cmdDmi2;
    cmdDmi2.cmd = "dmidecode -t 2";
    cmdDmi2.file = "dmidecode_2.txt";
    cmdDmi2.canNotReplace = true;
    m_ListCmd.append(cmdDmi2);

    Cmd cmdDmi3;
    cmdDmi3.cmd = "dmidecode -t 3";
    cmdDmi3.file = "dmidecode_3.txt";
    cmdDmi3.canNotReplace = true;
    m_ListCmd.append(cmdDmi3);

    Cmd cmdDmi4;
    cmdDmi4.cmd = "dmidecode -t 4";
    cmdDmi4.file = "dmidecode_4.txt";
    cmdDmi4.canNotReplace = true;
    m_ListCmd.append(cmdDmi4);

    Cmd cmdDmi13;
    cmdDmi13.cmd = "dmidecode -t 13";
    cmdDmi13.file = "dmidecode_13.txt";
    cmdDmi13.canNotReplace = true;
    m_ListCmd.append(cmdDmi13);

    Cmd cmdDmi16;
    cmdDmi16.cmd = "dmidecode -t 16";
    cmdDmi16.file = "dmidecode_16.txt";
    cmdDmi16.canNotReplace = true;
    m_ListCmd.append(cmdDmi16);

    Cmd cmdDmi17;
    cmdDmi17.cmd = "dmidecode -t 17";
    cmdDmi17.file = "dmidecode_17.txt";
    cmdDmi17.canNotReplace = true;
    m_ListCmd.append(cmdDmi17);

    Cmd cmdHwinfoMonitor;
    cmdHwinfoMonitor.cmd = "hwinfo --monitor";
    cmdHwinfoMonitor.file = "hwinfo_monitor.txt";
    cmdHwinfoMonitor.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoMonitor);

    Cmd cmdHwinfoSound;
    cmdHwinfoSound.cmd = "hwinfo --sound";
    cmdHwinfoSound.file = "hwinfo_sound.txt";
    cmdHwinfoSound.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoSound);

    Cmd cmdHwinfoUsb;
    cmdHwinfoUsb.cmd = "hwinfo --usb";
    cmdHwinfoUsb.file = "hwinfo_usb.txt";
    cmdHwinfoUsb.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoUsb);

    Cmd cmdHwinfoNetwork;
    cmdHwinfoNetwork.cmd = "hwinfo --network";
    cmdHwinfoNetwork.file = "hwinfo_network.txt";
    cmdHwinfoNetwork.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoNetwork);

    Cmd cmdHwinfoKeyboard;
    cmdHwinfoKeyboard.cmd = "hwinfo --keyboard";
    cmdHwinfoKeyboard.file = "hwinfo_keyboard.txt";
    cmdHwinfoKeyboard.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoKeyboard);

    Cmd cmdHwinfoCdrom;
    cmdHwinfoCdrom.cmd = "hwinfo --cdrom";
    cmdHwinfoCdrom.file = "hwinfo_cdrom.txt";
    cmdHwinfoCdrom.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoCdrom);

    Cmd cmdHwinfoDisk;
    cmdHwinfoDisk.cmd = "hwinfo --disk";
    cmdHwinfoDisk.file = "hwinfo_disk.txt";
    cmdHwinfoDisk.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoDisk);

    Cmd cmdHwinfoDisplay;
    cmdHwinfoDisplay.cmd = "hwinfo --display";
    cmdHwinfoDisplay.file = "hwinfo_display.txt";
    cmdHwinfoDisplay.canNotReplace = true;
    m_ListCmd.append(cmdHwinfoDisplay);

    Cmd cmdHwinfoMouse;
    cmdHwinfoMouse.cmd = "hwinfo --mouse";
    cmdHwinfoMouse.file = "hwinfo_mouse.txt";
    cmdHwinfoMouse.canNotReplace = false;
    m_ListCmd.append(cmdHwinfoMouse);

    Cmd cmdUpower;
    cmdUpower.cmd = "upower --dump";
    cmdUpower.file = "upower_dump.txt";
    cmdUpower.canNotReplace = true;
    m_ListCmd.append(cmdUpower);

    Cmd cmdLscpu;
    cmdLscpu.cmd = "lscpu";
    cmdLscpu.file = "lscpu.txt";
    cmdLscpu.canNotReplace = true;
    m_ListCmd.append(cmdLscpu);

    Cmd cmdLsblk;
    cmdLsblk.cmd = "lsblk -d -o name,rota";
    cmdLsblk.file = "lsblk_d.txt";
    cmdLsblk.canNotReplace = false;
    m_ListCmd.append(cmdLsblk);

    Cmd cmdXrandr;
    cmdXrandr.cmd = "xrandr";
    cmdXrandr.file = "xrandr.txt";
    cmdXrandr.canNotReplace = false;
    m_ListCmd.append(cmdXrandr);

    Cmd cmdXrandrVerbose;
    cmdXrandrVerbose.cmd = "xrandr --verbose";
    cmdXrandrVerbose.file = "xrandr_verbose.txt";
    cmdXrandrVerbose.canNotReplace = false;
    m_ListCmd.append(cmdXrandrVerbose);

    Cmd cmdDmesg;
    cmdDmesg.cmd = "dmesg";
    cmdDmesg.file = "dmesg.txt";
    cmdDmesg.canNotReplace = true;
    m_ListCmd.append(cmdDmesg);

    Cmd cmdHciconfig;
    cmdHciconfig.cmd = "hciconfig -a";
    cmdHciconfig.file = "hciconfig.txt";
    cmdHciconfig.canNotReplace = false;
    m_ListCmd.append(cmdHciconfig);

    if (info.contains("klu")) {
        Cmd cmdGpuinfo;
        cmdGpuinfo.cmd = "gpuinfo";
        cmdGpuinfo.file = "gpuinfo.txt";
        cmdGpuinfo.canNotReplace = true;
        m_ListCmd.append(cmdGpuinfo);

        Cmd cmdBootdevice;
        cmdBootdevice.cmd = "cat /proc/bootdevice/product_name";
        cmdBootdevice.file = "bootdevice.txt";
        cmdBootdevice.canNotReplace = false;
        m_ListCmd.append(cmdBootdevice);

    } else if (info.contains("panguV")) {
        Cmd cmdGpuinfo;
        cmdGpuinfo.cmd = "gpuinfo";
        cmdGpuinfo.file = "gpuinfo.txt";
        cmdGpuinfo.canNotReplace = true;
        m_ListCmd.append(cmdGpuinfo);

        Cmd cmdBootdevice;
        cmdBootdevice.cmd = "cat /proc/bootdevice/product_name";
        cmdBootdevice.file = "bootdevice.txt";
        cmdBootdevice.canNotReplace = false;
        m_ListCmd.append(cmdBootdevice);

        Cmd cmdEdidHdmi;
        cmdEdidHdmi.cmd = "hexdump /sys/devices/platform/hisi-drm/drm/card0/card0-HDMI-A-1/edid";
        cmdEdidHdmi.file = "EDID_HDMI.txt";
        cmdEdidHdmi.canNotReplace = false;
        m_ListCmd.append(cmdEdidHdmi);

        Cmd cmdEdidVGA;
        cmdEdidVGA.cmd = "hexdump /sys/devices/platform/hisi-drm/drm/card0/card0-VGA-1/edid";
        cmdEdidVGA.file = "EDID_VGA.txt";
        cmdEdidVGA.canNotReplace = false;
        m_ListCmd.append(cmdEdidVGA);
    }
}
