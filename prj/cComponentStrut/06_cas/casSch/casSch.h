/*
 * casSch.h
 *
 *  Created on: 2018��8��17��
 *      Author: pxf
 */

#ifndef CASSCH_H_
#define CASSCH_H_

#include "..\..\01_std\std.h"
#include "..\..\04_abi\abi.h"
#include "casSchErrCode.h"

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
CL(vfbOcasSch)
{
    hvfbOcasSch self;
    hvfbOcasSch (*init)(hvfbOcasSch cthis,
            void (*tickOut)(hvfbOcasSch t),
            void (*err)(hvfbOcasSch t, herrCode code));

    void (*tickOut)(hvfbOcasSch t);
    void (*err)(hvfbOcasSch t, herrCode code);
};

// �ⲿ�ӿ�����--------------------------
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);                 // �ӿڽṹ�������+������+�����ຯ��
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

// ���������ʵ��------------------------
extern vfbOcasSch vfbOcasSchA;


// --------------------------------------------------------------
// ����ඨ��
// --------------------------------------------------------------
// ������--------------------------------
#define SCH_TASK_GROUP_NUM  3  // ��������������
typedef void(*schTask)(void);  // ͨ�õ�����������
// ��������鶨��
typedef struct
{
    int16 taskGroupNum;
    uint16 tick;
    uint16 startTick[SCH_TASK_GROUP_NUM][32];     // ����������ʼ����
    uint16 prdTick[SCH_TASK_GROUP_NUM][32];       // ���ڵ��Ƚ���
    uint32 actMask[SCH_TASK_GROUP_NUM];           // ����������������
    uint32 taskMask[SCH_TASK_GROUP_NUM];          // �ѷ�����������
    schTask taskGroup[SCH_TASK_GROUP_NUM][32];    // ������
} tasks;

// ����������״̬��-----------------------
#define SCH_SM_STA_LIST(_) \
    _(schSm, update) \
    _(schSm, execute)

// ����״̬������
SMDC(schSm, SCH_SM_STA_LIST)
{
    sta next;
    tasks task;

    // ע������������������
    void *casSch;
};

// �����������������----------------------
CL(casSch)
{
    hcasSch self;
    hcasSch (*init)(hcasSch cthis, hmeasure time, hvfbOcasSch vfbOcasSch);

    schSmRec schSmRec;
    staAct schSm[schSm_sta_default + 1];

    // �����ܺ���
    void (*timer)(hcasSch t);
    void (*run)(hcasSch t);

    // �������
    void (*tickOut)(hcasSch t);
    void (*err)(hcasSch t, herrCode code);

    // ���뺯��
    void (*addTask)(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hcasSch t, int16 id, void(*schTask)(void));

    INJ(measure, time);
    INJ(vfbOcasSch, vfbOcasSch);
};

// �첽���ȹ��ܺ���---------------------------
void abi_casSch_timer(void);
void abi_casSch_mainLoop(void);

// �����ʵ��---------------------------------
extern casSch casSchA;

// --------------------------------------------------------------
// ���������ඨ��
// --------------------------------------------------------------
// ��������������------------------------------
CL(vfbIcasSch)
{
    hvfbIcasSch self;
    hvfbIcasSch (*init)(hvfbIcasSch cthis, hcasSch casSch);

    void (*addTask)(hvfbIcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));

    INJ(casSch, casSch);
};

// ����������ʵ��------------------------------
extern vfbIcasSch vfbIcasSchA;

#endif /* CASSCH_H_ */
