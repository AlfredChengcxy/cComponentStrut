/*
 * vfbMcpcFdam.h
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#ifndef VFBMCPCFDAM_H_
#define VFBMCPCFDAM_H_

#include "..\..\09_cpc\cpcFdam\cpcFdam.h"

// --------------------------------------------------------------
// ���������ʼ��
// --------------------------------------------------------------
// ���������ʼ��------------------------
int16 vfbMcpcFdamInit(void);



// --------------------------------------------------------------
// ��������ඨ��
// --------------------------------------------------------------
// �������������------------------------
CL(vfbMcpcFdam)
{
    hvfbMcpcFdam self;
    hvfbMcpcFdam (*init)(hvfbMcpcFdam cthis);

    INJ(cpcFdam, cpcFdam);
};

// �����ӿ�����------------------------
// �ӿڽṹ��������+�����+����ຯ��


// ���������ʵ��------------------------
extern vfbMcpcFdam vfbMcpcFdamA;

#endif /* VFBMCPCFDAM_H_ */
