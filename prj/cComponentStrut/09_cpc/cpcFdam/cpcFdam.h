/*
 * cpcFdam.h
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#ifndef CPCFDAM_H_
#define CPCFDAM_H_

#include "..\..\01_std\std.h"
#include "..\..\02_bm\fifo\fifo.h"

// --------------------------------------------------------------
// �����ʼ��
// --------------------------------------------------------------
// ��������ʼ��------------------------
// 0�ɹ���-1ʧ��
int16 vfbIcpcFdamInit(void);

// �����ʼ��----------------------------
int16 cpcFdamInit(void);

// ��������ʼ��------------------------
int16 vfbOcpcFdamInit(void);

// ���������ʼ���ⲿ����----------------
extern int16 vfbMcpcFdamInit(void);

// --------------------------------------------------------------
// �������
// --------------------------------------------------------------
// ������е���--------------------------
void cpcFdamSch(void);

// --------------------------------------------------------------
// ����������ͨ����������
// --------------------------------------------------------------

// --------------------------------------------------------------
// ���������ͨ����������
// --------------------------------------------------------------

// --------------------------------------------------------------
// ��������ඨ��
// --------------------------------------------------------------
// �������������------------------------
CL(vfbOcpcFdam)
{
    hvfbOcpcFdam self;
    hvfbOcpcFdam (*init)(hvfbOcpcFdam cthis);
};

// �ⲿ�ӿ�����--------------------------

// ���������ʵ��------------------------
extern vfbOcpcFdam vfbOcpcFdamA;

// --------------------------------------------------------------
// ����ඨ��
// --------------------------------------------------------------
// ������״̬������--------------------
#define ERR_DISPOSE_SM_LIST(_) \
    _(errDisposeSm, polling)   \
    _(errDisposeSm, dispose)
SMDC(errDisposeSm, ERR_DISPOSE_SM_LIST)
{
    sta next;
    void *cpcFdam;
};
// ���󻺴���ж���----------------------
#define ERR_FIFO_LEN     20  // һ�δ������洢19��������Ϣ
extern errCode errCodeBuff[ERR_FIFO_LEN];
extern fifo errCodeFifo;

// ���������----------------------------
CL(cpcFdam)
{
    hcpcFdam self;
    hcpcFdam (*init)(hcpcFdam cthis, hvfbOcpcFdam vfbOcpcFdam,
            hfifo errCodeFifo, void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

    uint32 errCnt;
    // 0  ignore    �ɺ���
    // 1  warning   ����
    // 2  serious   ���ش���
    // 3  fatal     ��������
    uint32 errIgnoreCnt;
    uint32 errWarningCnt;
    uint32 errSeriousCnt;
    uint32 errFatalCnt;
    // 0  communicationInputErr  ͨ���������
    // 1  communicationOutputErr ͨ���������
    // 2  schedularErr           ������ȴ���
    // 3  functionErr            ���ܴ���
    uint32 errCieCnt;
    uint32 errCoeCnt;
    uint32 errSeCnt;
    uint32 errFeCnt;

    errDisposeSmRec errDisposeSmRec;
    staAct errDisposeSm[errDisposeSm_sta_default + 1];

    void (*saveErrCode)(hcpcFdam t, herrCode code);
//    void (*getErrCode)(hcpcFdam t, herrCode code);
    void (*run)(hcpcFdam t);

    INJ(vfbOcpcFdam, vfbOcpcFdam);
    EXT(fifo);
};

// �첽���ȹ��ܺ���----------------------


// �����ʵ��----------------------------
extern cpcFdam cpcFdamA;

// --------------------------------------------------------------
// ���������ඨ��
// --------------------------------------------------------------
// ��������������------------------------
CL(vfbIcpcFdam)
{
    hvfbIcpcFdam self;
    hvfbIcpcFdam (*init)(hvfbIcpcFdam cthis, hcpcFdam cpcFdam);

    void (*saveErrCode)(hvfbIcpcFdam t, herrCode code);

    INJ(cpcFdam, cpcFdam);
};

// ����������ʵ��------------------------
extern vfbIcpcFdam vfbIcpcFdamA;

#endif /* CPCFDAM_H_ */
