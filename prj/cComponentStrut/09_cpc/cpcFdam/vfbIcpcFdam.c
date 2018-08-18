/*
 * vfbIcpcFdam.c
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#include "cpcFdam.h"

// --------------------------------------------------------------
// ��������ʼ��
// --------------------------------------------------------------
// ��������ʼ��------------------------
int16 vfbIcpcFdamInit(void)
{
    int16 rtv = 0;

    CN(vfbIcpcFdam, &vfbIcpcFdamA, &cpcFdamA);
    if (OPRS(vfbIcpcFdamA) != OOPC_NULL)
    {
        rtv = cpcFdamInit();
    }
    else
    {
        rtv = -1;
    }

    return rtv;
}


// --------------------------------------------------------------
// ���������ඨ��
// --------------------------------------------------------------
hvfbIcpcFdam vfbIcpcFdam_init(hvfbIcpcFdam cthis, hcpcFdam cpcFdam)
{
    cthis->cpcFdam = cpcFdam;

    return cthis;
}

void vfbIcpcFdam_saveErrCode(hvfbIcpcFdam t, herrCode code)
{
    t->cpcFdam->saveErrCode(t->cpcFdam, code);
}

CC(vfbIcpcFdam)
{
    cthis->init = vfbIcpcFdam_init;
    cthis->saveErrCode = vfbIcpcFdam_saveErrCode;

    return cthis;
}
CD(vfbIcpcFdam)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// ����������ʵ����
// --------------------------------------------------------------
vfbIcpcFdam vfbIcpcFdamA;
