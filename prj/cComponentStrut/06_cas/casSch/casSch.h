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

// ����������״̬��
#define SCH_SM_STA_LIST(_) \
    _(schSm, update) \
    _(schSm, execute)

SMDC(schSm, SCH_SM_STA_LIST)
{
    sta next;
};


// ͨ�ô�����
typedef struct
{
    void *id;
    struct
    {
        uint32 cpnPartId    :8;
        uint32 errClassify  :4;
        uint32 errRanking   :4;
        uint32 errCode      :16;
    };
} errCode, *herrCode;

// ��������ඨ��
CL(vfbOcasSch)
{
    hvfbOcasSch self;
    hvfbOcasSch (*init)(hvfbOcasSch cthis,
            void (*tickOut)(hvfbOcasSch t),
            void (*err)(hvfbOcasSch t, herrCode code));

    void (*tickOut)(hvfbOcasSch t);
    void (*err)(hvfbOcasSch t, herrCode code);
};


// ����ඨ��
// ������
#define SCH_TASK_GROUP_NUM  3  // ����������

typedef void(*schTask)(void);

typedef struct
{
    int16 taskGroupNum;
    uint16 actTick[SCH_TASK_GROUP_NUM];           // �������
    uint16 prdTick[SCH_TASK_GROUP_NUM];           // ���ڵ��Ƚ���
    uint32 actMask[SCH_TASK_GROUP_NUM];           // ����������������
    uint32 taskMask[SCH_TASK_GROUP_NUM];          // �ѷ�����������
    schTask taskGroup[SCH_TASK_GROUP_NUM][32];    // ������
} tasks;


CL(casSch)
{
    hcasSch self;
    hcasSch (*init)(hcasSch cthis, hmeasure time);

    uint16 tick;
    tasks task;
    schSmRec schSmRec;

    // �����ܺ���
    void (*timer)(hcasSch t);
    void (*run)(hcasSch t);

    // �������
    void (*tickOut)(hcasSch t);
    void (*err)(hcasSch t, herrCode code);

    // ���뺯��
    void (*addTask)(hcasSch t, int16 id, void(*schTask)(void));
    void (*delTask)(hcasSch t, int16 id, void(*schTask)(void));

    INJ(measure, time);
    INJ(vfbOcasSch, vfbOcasSch);
};

// ���������ඨ��
CL(vfbIcasSch)
{
    hvfbIcasSch self;
    hvfbIcasSch (*init)(hvfbIcasSch cthis);

    void (*addTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));
    void (*delTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));

    INJ(casSch, casSch);
};

// �첽���ȹ��ܺ���
void casSch_timer_bsp(void);
void casSch_mainLoop_bsp(void);

// �����๦�ܽӿ�



#endif /* CASSCH_H_ */
