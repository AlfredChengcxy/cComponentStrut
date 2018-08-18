/*
 * vfbMcasSch.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "vfbMcasSch.h"
#include "..\..\09_cpc\cpcFdam\cpcFdam.h"


// --------------------------------------------------------------
// 管理组件初始化
// --------------------------------------------------------------
int16 vfbMcasSchInit(void)
{
    int16 rtv = 0;
    int16 id = 0;

    CNNP(vfbMcasSch, &vfbMcasSchA);
    if (OPRS(vfbMcasSchA) != OOPC_NULL)
    {
        rtv = vfbIcpcFdamInit();
        if (rtv == 0)
        {
            vfbIcasSchA.addTask(vfbIcasSchA.self, id, cpcFdamSch, 10000, 11);
            id++;
        }

    }
    else
    {
        rtv = -1;
    }

    return rtv;
}


// --------------------------------------------------------------
// 组件管理类定义
// --------------------------------------------------------------
hvfbMcasSch hvfbMcasSch_init(hvfbMcasSch cthis)
{
    return cthis;
}

void hvfbMcasSch_tickOut(hvfbMcasSch t)
{}
void hvfbMcasSch_err(hvfbMcasSch t, herrCode code)
{}

CC(vfbMcasSch)
{
    cthis->init = hvfbMcasSch_init;
    cthis->tickOut = hvfbMcasSch_tickOut;
    cthis->err = hvfbMcasSch_err;

    return cthis;
}
CD(vfbMcasSch)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 输出类接口定义
// --------------------------------------------------------------
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t)
{}
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code)
{}

// --------------------------------------------------------------
// 组件管理类实例
// --------------------------------------------------------------
vfbMcasSch vfbMcasSchA;
