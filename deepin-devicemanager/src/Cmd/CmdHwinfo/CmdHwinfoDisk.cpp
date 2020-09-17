#include "hd.h"
#include "CmdHwinfoDisk.h"

#include <QDebug>

CmdHwinfoDisk::CmdHwinfoDisk()
    : CmdHwinfo()
{
    initInfo();
}

void CmdHwinfoDisk::initInfo()
{
    hd_data_t *hd_data = nullptr;
    hd_data = static_cast<hd_data_t *>(calloc(1, sizeof * hd_data)) ;

    hd_t *hd, *hd0;
    hd0 = hd_list(hd_data, hw_disk, 1, nullptr);

    for (hd = hd0; hd; hd = hd->next) {

        QMap<QString, QString> mapInfo;

        // 基本信息
        addMapInfo(mapInfo, "Unique ID", hd->unique_id);
        addMapInfo(mapInfo, "Parent ID", hd->parent_id);
        addMapInfo(mapInfo, "SysFS ID", hd->sysfs_id);
        addMapInfo(mapInfo, "SysFS BusID", hd->sysfs_bus_id);
        addMapInfo(mapInfo, "SysFS Device Link", hd->sysfs_device_link);
        addMapInfo(mapInfo, "Hardware Class", hd->base_class.name);          // 设备类别
        addMapInfo(mapInfo, "Model", hd->model);                             // 设备型号
        addMapInfo(mapInfo, "Vendor", hd->vendor.name);                      // 设备厂商
        addMapInfo(mapInfo, "Device", hd->device.name);                      // 设备名称
        addMapInfo(mapInfo, "Revision", hd->revision.name);                  // 版本
        addMapInfo(mapInfo, "Serial ID", hd->serial);                        // 设备序列号
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

        QStringList geoTypeStr;
        geoTypeStr << "Physical"
                   << "Logical"
                   << "BIOS EDD"
                   << "BIOS Legacy";

        // Geometry
        QString type;
        QString val;

//        qDebug() << hd->res << hd->res->any.type << res_disk_geo;
        if (hd->res && hd->res->any.type == res_disk_geo) {
            type = hd->res->disk_geo.geotype < geoTypeStr.size() ? geoTypeStr[hd->res->disk_geo.geotype] : "";

            QString val;
            val = QString("CHS %1/%2/%3")
                  .arg(hd->res->disk_geo.cyls)
                  .arg(hd->res->disk_geo.heads)
                  .arg(hd->res->disk_geo.sectors);

            addMapInfo(mapInfo, QString("Geometry (%1)").arg(type), val);

            // Size
            if (hd->res && hd->res->disk_geo.size) {

                val = QString("%" PRIu64 " sectors").arg(hd->res->disk_geo.sectors);
                addMapInfo(mapInfo, QString("Size (%1)").arg(type), val);
            }
        }

        // Size
        QString unit = "";
        QString b0, b1;

        if (hd->res) {
            qDebug() << "no null";
        } else {
            qDebug() << "null";
        }
        if (hd->res && hd->res->any.type == res_size) {
            switch (hd->res->size.unit) {
            case size_unit_cinch:
                unit = "''";
                b0 = float2str(static_cast<unsigned int>(hd->res->size.val1), 2);
                b1 = float2str(static_cast<unsigned int>(hd->res->size.val2), 2);
                break;

            default:
                switch (hd->res->size.unit) {
                case size_unit_cm:
                    unit = "cm";
                    break;
                case size_unit_mm:
                    unit = "mm";
                    break;
                case size_unit_sectors:
                    unit = "sectors";
                    break;
                case size_unit_kbyte:
                    unit = "kByte";
                    break;
                default:
                    unit = "some unit";
                }

                b0 = QString("% PRIu64").arg(hd->res->size.val1);
                b1 = QString("% PRIu64").arg(hd->res->size.val2);

                if (!hd->res->size.val2) {
                    addMapInfo(mapInfo, "Size", QString("%1 %2").arg(b0).arg(unit));
                } else if (hd->res->size.unit == size_unit_sectors) {
                    addMapInfo(mapInfo, "Size", QString("%1 %2 a %3 bytes").arg(b0).arg(unit).arg(b1));

                    // Capacity
                    QString cap;
                    cap = QString("%" PRIu64 " GB (%" PRIu64 " bytes)")
                          .arg((hd->res->size.val1 * hd->res->size.val2) >> 30)
                          .arg(hd->res->size.val1 * hd->res->size.val2);
                    addMapInfo(mapInfo, "Capacity", cap);

                } else {
                    addMapInfo(mapInfo, "Size", QString("%1x%2 %3").arg(b0).arg(b1).arg(unit));
                }
            }
            break;
        }

        addMMInfo(int(hd->idx), mapInfo);
    }
}






