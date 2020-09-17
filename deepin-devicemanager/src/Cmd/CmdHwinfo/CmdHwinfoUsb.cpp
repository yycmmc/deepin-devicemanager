#include "hd.h"

#include "CmdHwinfoUsb.h"
#include <QDebug>

CmdHwinfoUsb::CmdHwinfoUsb()
    : CmdHwinfo()
{
    initInfo();
}

void CmdHwinfoUsb::initInfo()
{
    hd_data_t *hd_data = nullptr;
    hd_data = static_cast<hd_data_t *>(calloc(1, sizeof * hd_data)) ;

    hd_t *hd, *hd0;
    hd0 = hd_list(hd_data, hw_usb, 1, nullptr);

    for (hd = hd0; hd; hd = hd->next) {

        QMap<QString, QString> mapInfo;

        // 基本信息
        addMapInfo(mapInfo, "Unique ID", hd->unique_id);
        addMapInfo(mapInfo, "SysFS ID", hd->sysfs_id);
        addMapInfo(mapInfo, "SysFS BusID", hd->sysfs_bus_id);
        addMapInfo(mapInfo, "Hardware Class", hd->base_class.name);          // 设备类别
        addMapInfo(mapInfo, "Model", hd->model);                             // 设备型号

        // hotplug
        QString hpStr = "";
        hd_hotplug_t hp = hd->hotplug;
        if (hp == hp_none) {
            hpStr = "";
        } else if (hp == hp_pcmcia) {
            hpStr = "PCMCIA";
        } else if (hp == hp_pci) {
            hpStr = "PCI";
        } else if (hp == hp_usb) {
            hpStr = "USB";
        } else if (hp == hp_cardbus) {
            hpStr = "CARDBUS";
        } else if (hp == hp_ieee1394) {
            hpStr = "IEEE 1394";
        }

        addMapInfo(mapInfo, "Hotplug", hpStr);

        addMapInfo(mapInfo, "Vendor", hd->vendor.name);                      // 设备厂商
        addMapInfo(mapInfo, "Device", hd->device.name);                      // 设备名称
        addMapInfo(mapInfo, "Revision", hd->revision.name);                  // 版本
        addMapInfo(mapInfo, "Driver", hd->driver);                           // 设备驱动
        addMapInfo(mapInfo, "Driver Modules", hd->driver_module);            // 驱动模块

        //　Device File
        QString deviceFile;
        QString unix_dev_name = QString("%1").arg(hd->unix_dev_name);
        QString unix_dev_name2 = QString("%1").arg(hd->unix_dev_name2);
        if (!unix_dev_name.isNull()) {
            deviceFile = unix_dev_name;
        }
        if (!unix_dev_name2.isNull()) {
            deviceFile += " (" + unix_dev_name2 + ")";
        }
        addMapInfo(mapInfo, "Device File", deviceFile);

        // Device Files
        QString deviceFiles;
        str_list_t *slt0, *slt;
        slt0 = hd->unix_dev_names;
        for (slt = slt0; slt; slt = slt->next) {
            if (slt->str && *slt->str != '\0') {
                deviceFiles += QString::fromLocal8Bit(slt->str);
                deviceFile += ", ";
            }
        }
        deviceFiles.replace(QRegExp(", $"), "");
        addMapInfo(mapInfo, "Device Files", deviceFiles);

//        addMapInfo(mapInfo, "Device Number", hd->unix_dev_num);               // 子厂商

        // speed
        QString speed;
        if (hd->res && hd->res->any.type == res_baud) {
            if (hd->res->baud.speed == 0 || hd->res->baud.speed % 100) {
                speed = QString("%1 bps").arg(hd->res->baud.speed);
            } else if (hd->res->baud.speed % 100000) {
                speed = QString("%1 kbps").arg(float2str(hd->res->baud.speed, 3));
            } else {
                speed = QString("%1 Mbps").arg(float2str(hd->res->baud.speed, 6));
            }
        }
        addMapInfo(mapInfo, "Speed", speed);       // 速度

        addMapInfo(mapInfo, "Module Alias", hd->modalias);            // 模块别名

        // XkbRules,XkbModel
        if (hd->driver_info && hd->driver_info->any.type == di_kbd) {
            if (hd->driver_info->kbd.XkbRules) {
                addMapInfo(mapInfo, "XkbRules", hd->driver_info->kbd.XkbRules);
            }
            if (hd->driver_info->kbd.XkbModel) {
                addMapInfo(mapInfo, "XkbModel", hd->driver_info->kbd.XkbModel);
            }
            if (hd->driver_info->kbd.XkbLayout) {
                addMapInfo(mapInfo, "XkbLayout", hd->driver_info->kbd.XkbLayout);
            }
            if (hd->driver_info->kbd.keymap) {
                addMapInfo(mapInfo, "keymap", hd->driver_info->kbd.keymap);
            }
        }

        // Buttons,Wheels,XFree86 Protocol,GPM Protocol
        if (hd->driver_info && hd->driver_info->any.type == di_mouse) {
            if (hd->driver_info->mouse.buttons >= 0) {
                addMapInfo(mapInfo, "Buttons", QString::number(hd->driver_info->mouse.buttons));
            }
            if (hd->driver_info->mouse.wheels >= 0) {
                addMapInfo(mapInfo, "Wheels", QString::number(hd->driver_info->mouse.wheels));
            }
            if (hd->driver_info->mouse.xf86) {
                addMapInfo(mapInfo, "XFree86 Protocol", hd->driver_info->mouse.xf86);
            }
            if (hd->driver_info->mouse.gpm) {
                addMapInfo(mapInfo, "GPM Protocol", hd->driver_info->mouse.gpm);
            }
        }

        //Config Status
        QString cfgStatus = "";
        int i = 0;
        if (
            hd_data->debug && (
                hd->status.configured ||
                hd->status.available ||
                hd->status.needed ||
                hd->status.active ||
                hd->status.invalid ||
                hd->is.manual
            )
        ) {
            if (hd->status.invalid) {
                cfgStatus += "invalid";
                ++i;
            }

            if (hd->is.manual) {
                cfgStatus += QString("%1manual").arg(i ? ", " : "");
                ++i;
            }

            QString s;
            if (hd->status.configured) {
                s = hd_status_value_name(static_cast<hd_status_value_t>(hd->status.configured));
                cfgStatus += QString("%1cfg=%2").arg(i ? ", " : "").arg(s);
                ++i;
            }

            if (hd->status.available) {
                s = hd_status_value_name(static_cast<hd_status_value_t>(hd->status.available));
                cfgStatus += QString("%1avail=%2").arg(i ? ", " : "").arg(s);
                ++i;
            }

            if (hd->status.needed) {
                s = hd_status_value_name(static_cast<hd_status_value_t>(hd->status.needed));
                cfgStatus += QString("%1need=%2").arg(i ? ", " : "").arg(s);
                ++i;
            }

            if (hd->status.active) {
                s = hd_status_value_name(static_cast<hd_status_value_t>(hd->status.active));
                cfgStatus += QString("%1active=%2").arg(i ? ", " : "").arg(s);
                ++i;
            }

            addMapInfo(mapInfo, "Config Status", cfgStatus);

        }


        addMMInfo(int(hd->idx), mapInfo);
    }
}
