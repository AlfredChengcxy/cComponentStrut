/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :casSch.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :���casSch �����ࡢ����ࡢ�����������������ͷ�ļ�
* @others       :
* @history      :180831 pxf ���ν���
***************************************************************************/

#ifndef CASSCH_H_
#define CASSCH_H_

#include "..\..\01_std\std.h"
//#include "..\..\06_cas\casSch\casSch.h"
#include "..\..\04_abi\abi.h"
#include "casSchCfg.h"
#include "casSchErrCode.h"

/***********************************************************
* �����ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbIcasSchInit(void);

/*�����ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 casSchInit(void);

/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbOcasSchInit(void);

/*���������ʼ���ⲿ����
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
extern int16 vfbMcasSchInit(void);


/***********************************************************
* �������
***********************************************************/
/*������е���
* ����: ��
* ���: ��
***********************************************/
//void casSchSch(void);


/***********************************************************
* ���������ͨ����������
***********************************************************/


/***********************************************************
* ��������ͨ����������
***********************************************************/


/***********************************************************
* �������ඨ��
***********************************************************/
/*������������
***********************************************/
CL(vfbOcasSch){
    hvfbOcasSch self;
    hvfbOcasSch (*init)(hvfbOcasSch cthis,
            void (*tickOut)(hvfbOcasSch t),
            void (*err)(hvfbOcasSch t, herrCode code));

    // ������Ȳ���
    //schParam schParam;

    // �������๦�ܺ���
    void (*tickOut)(hvfbOcasSch t);
    void (*err)(hvfbOcasSch t, herrCode code);
};

/*���������ⲿ�ӿ�����
* ������ʽ: �����+ʵ����+ʵ���๦��
***********************************************/
extern void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);
extern void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

/*��������ʵ��
***********************************************/
extern vfbOcasSch vfbOcasSchA;


/***********************************************************
* ����ඨ��
***********************************************************/
/*������
***********************************************/
#define SCH_TASK_GROUP_NUM  SCH_TASK_GROUP_NUM_CFG   // ��������������
typedef void(*schTask)(void);                        // ͨ�õ�����������

/*��������鶨��
***********************************************/
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

/*���״̬��״̬
* ������״̬init/default��״̬list����ʾ��Ĭ�ϸ���
* ״̬list�����ʵ��Ӧ�ý�����д��list�޸ĺ���Ӧ״̬�����ö�Ӧ�޸�
***********************************************/
#define SM_CASSCH_STA_LIST(_) \
    _(smcasSch, update)\
    _(smcasSch, execute)

/*���״̬������
***********************************************/
SMDC(smcasSch, SM_CASSCH_STA_LIST)
{
    sta next;
    tasks task;

    // ע�������
    void *casSch;
};

/*������ȵ��Ȳ�������������غ���Ա��
***********************************************/
typedef struct
{
    int16 id;                // �������id���������ʼ��ʱ����
    void(*schTask)(void);    // �������
    uint16 startTick;        // ����������ʼ����
    uint16 prdTick;          // ���ڵ��Ƚ���
} schParam;

/*���������
***********************************************/
CL(casSch){
    hcasSch self;
    hcasSch (*init)(hcasSch cthis, hstaAct smcasSch, hvfbOcasSch vfbOcasSch, hmeasure time);

    // �������״̬��
    smcasSchRec smcasSchRec;
    hstaAct smcasSch;

    // ���������ز���
    uint32 usage;        // cpuʹ���ʣ���112��ʾ11.2%
    uint32 taskTime;     // ��ǰ����ִ��ʱ�䣬��ʱ��������һ��

    // ������й��ܺ���
    void (*run)(hcasSch t);
    void (*tick)(hcasSch t);

    // ������빦�ܺ���
    void (*addTask)(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hcasSch t, int16 id, void(*schTask)(void));

    // ���������ܺ���
    void (*tickOut)(hcasSch t);
    void (*err)(hcasSch t, herrCode code);

    // ע���������༰����������
    INJ(vfbOcasSch, vfbOcasSch);
    INJ(measure, time);
};

/*�첽���ȹ��ܺ���
* ������ʽ: �����+ʵ����+ʵ���๦��
* ֻ��cas����������д˺���
***********************************************/
void casSch_abi_timer(void);
void casSch_abi_mainLoop(void);

/*�����ʵ��
***********************************************/
extern casSch casSchA;


/***********************************************************
* ��������ඨ��
***********************************************************/
/*�������������
***********************************************/
CL(vfbIcasSch){
    hvfbIcasSch self;
    hvfbIcasSch (*init)(hvfbIcasSch cthis, hcasSch casSch);

    // ��������๦�ܺ���
    void (*addTask)(hvfbIcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));

    // ע�������
    INJ(casSch, casSch);
};

/*���������ʵ��
***********************************************/
extern vfbIcasSch vfbIcasSchA;


#endif

/**************************** Copyright(C) pxf ****************************/
