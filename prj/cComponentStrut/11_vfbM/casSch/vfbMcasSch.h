/*
 * vfbMcasSch.h
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#ifndef VFBMCASSCH_H_
#define VFBMCASSCH_H_

#include "..\..\06_cas\casSch\casSch.h"

// --------------------------------------------------------------
// ���������ʼ��
// --------------------------------------------------------------
// ���������ʼ��------------------------
int16 vfbMcasSchInit(void);


// --------------------------------------------------------------
// ��������ඨ��
// --------------------------------------------------------------
// �������������------------------------
CL(vfbMcasSch)
{
    hvfbMcasSch self;
    hvfbMcasSch (*init)(hvfbMcasSch cthis);

    void (*tickOut)(hvfbMcasSch t);
    void (*err)(hvfbMcasSch t, herrCode code);
};

// �����ӿ�����------------------------
// �ӿڽṹ��������+�����+����ຯ��
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

// ���������ʵ��------------------------
extern vfbMcasSch vfbMcasSchA;

#endif /* VFBMCASSCH_H_ */
