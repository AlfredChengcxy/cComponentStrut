/*
 * abi.c
 *
 *  Created on: 2018��8��17��
 *      Author: pxf
 */

#include "abi.h"
#include "..\06_cas\casSch\casSch.h"
#include "..\03_bsp\bsp.h"

// �߳������ӿ�
isr timer;
isr mainLoop;

// ʱ����������ӿ�
measure time;

// ���������ӿ�
gi err;

// ��������ӿ�
go led;



void abiInit(void)
{
    int16 abiInitErr = 0;

    CN(isr, &timer, abi_casSch_timer);
    if (OPRS(timer) == OOPC_NULL)
    {
        abiInitErr++;
    }
    CN(isr, &mainLoop, abi_casSch_mainLoop);
    if (OPRS(mainLoop) == OOPC_NULL)
    {
        abiInitErr++;
    }

    CN(measure, &time, bspMeasureStart, bspMeasureEnd);
    if (OPRS(time) == OOPC_NULL)
    {
        abiInitErr++;
    }

    CN(gi, &err, bspGiErr);
    if (OPRS(err) == OOPC_NULL)
    {
        abiInitErr++;
    }

    CN(go, &led, bspGoLed);
    if (OPRS(led) == OOPC_NULL)
    {
        abiInitErr++;
    }

}


