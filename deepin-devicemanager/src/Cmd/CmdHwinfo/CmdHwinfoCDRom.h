#ifndef CMDHWINFOCDROM_H
#define CMDHWINFOCDROM_H

#include "CmdHwinfo.h"

class CmdHwinfoCDRom : public CmdHwinfo
{
public:
    CmdHwinfoCDRom();

protected:
    /**
     * @brief initInfo 初始化信息
     */
    void initInfo() override;
};

#endif // CMDHWINFOCDROM_H
