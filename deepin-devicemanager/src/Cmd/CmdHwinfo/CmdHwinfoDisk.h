#ifndef CMDHWINFODISK_H
#define CMDHWINFODISK_H

#include "CmdHwinfo.h"

class CmdHwinfoDisk : public CmdHwinfo
{
public:
    CmdHwinfoDisk();

protected:
    /**
     * @brief initInfo 初始化信息
     */
    void initInfo() override;
};

#endif // CMDHWINFODISK_H
