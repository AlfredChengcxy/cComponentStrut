/*
 * vfbOcpcFdam.c
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#include "cpcFdam.h"

// --------------------------------------------------------------
// ��������ʼ��
// --------------------------------------------------------------
// ��������ʼ��------------------------
int16 vfbOcpcFdamInit(void)
{
    int16 rtv = 0;

    CNNP(vfbOcpcFdam, &vfbOcpcFdamA);
    if (OPRS(vfbOcpcFdamA) != OOPC_NULL)
    {
        rtv = vfbMcpcFdamInit();
    }
    else
    {
        rtv = -1;
    }

    return rtv;
}


// --------------------------------------------------------------
// ��������ඨ��
// --------------------------------------------------------------
hvfbOcpcFdam vfbOcpcFdam_init(hvfbOcpcFdam cthis)
{
    return cthis;
}

CC(vfbOcpcFdam)
{
    cthis->init = vfbOcpcFdam_init;

    return cthis;
}
CD(vfbOcpcFdam)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// ���������ʵ����
// --------------------------------------------------------------
vfbOcpcFdam vfbOcpcFdamA;
