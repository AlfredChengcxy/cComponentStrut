/*
 * vfbMcpcFdam.c
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#include "vfbMcpcFdam.h"

// --------------------------------------------------------------
// ���������ʼ��
// --------------------------------------------------------------
// ���������ʼ��------------------------
int16 vfbMcpcFdamInit(void)
{
    int16 rtv = 0;

    CNNP(vfbMcpcFdam, &vfbMcpcFdamA);
    if (OPRS(vfbMcpcFdamA) != OOPC_NULL)
    {
        rtv = 0;
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
hvfbMcpcFdam vfbMcpcFdam_init(hvfbMcpcFdam cthis)
{
    return cthis;
}

CC(vfbMcpcFdam)
{
    cthis->init = vfbMcpcFdam_init;

    return cthis;
}
CD(vfbMcpcFdam)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// �����ӿڶ���
// --------------------------------------------------------------




// --------------------------------------------------------------
// ���������ʵ��
// --------------------------------------------------------------
vfbMcpcFdam vfbMcpcFdamA;
