/*
 * vfbOcasSch.c
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#include "casSch.h"

// --------------------------------------------------------------
// ��������ඨ��
// --------------------------------------------------------------
hvfbOcasSch vfbOcasSch_init(hvfbOcasSch cthis,
        void (*tickOut)(hvfbOcasSch t),
        void (*err)(hvfbOcasSch t, herrCode code))
{
    cthis->tickOut = tickOut;
    cthis->err = err;

    return cthis;
}

CC(vfbOcasSch)
{
    cthis->init = vfbOcasSch_init;

    return cthis;
}
CD(vfbOcasSch)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// ���������ʵ����
// --------------------------------------------------------------
vfbOcasSch vfbOcasSchA;
