/*
 * casSch.c
 *
 *  Created on: 2018��8��17��
 *      Author: pxf
 */

#include "casSch.h"

// --------------------------------------------------------------
// ͨ�ù��ܺ���
// --------------------------------------------------------------
// Ĭ������
static void schTaskDefault(void)
{}

// ������2^n�Ķ�Ӧ�Ķ���n
static inline int16 log_2n(uint32 num)
{
    int16 n = 0;
    if ((num & 0xFFFF0000U) != 0U)
    {
        n += 16;
    }
    if ((num & 0xFF00FF00U) != 0U)
    {
        n += 8;
    }
    if ((num & 0xF0F0F0F0U) != 0U)
    {
        n += 4;
    }
    if ((num & 0xCCCCCCCCU) != 0U)
    {
        n += 2;
    }
    if ((num & 0xAAAAAAAAU) != 0U)
    {
        n += 1;
    }

    return n;
}


// --------------------------------------------------------------
// ����������״̬��
// --------------------------------------------------------------
void schSm_act_init(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;

    rec->casSch = &casSchA;

    rec->next = schSm_sta_update;
}
void schSm_act_update(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;

    for (i = 0; i < rec->task.taskGroupNum; i++)
    {
        // ���¸��鼤������
        taskMask = rec->task.taskMask[i];
        while (taskMask != 0)
        {
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            taskMask ^= curTask;
            taskIndex = log_2n(curTask);

            if ((rec->task.tick - rec->task.startTick[i][taskIndex]) >= rec->task.prdTick[i][taskIndex])
            {
                // ���¼���״̬�Լ���һ�������
                rec->task.actMask[i] |= curTask;
                rec->task.startTick[i][taskIndex] += rec->task.prdTick[i][taskIndex];
            }
        }
    }

    // ����������º����ִ��״̬�鿴�Ƿ���Ҫִ������
    rec->next = schSm_sta_execute;
}
void schSm_act_execute(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;
    errCode errcode;

    for (i = 0; i < rec->task.taskGroupNum; i++)
    {
        // �鿴�������񣬲�ִ��������ȼ�����
        taskMask = rec->task.actMask[i];
        if (taskMask != 0)
        {
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            //taskMask ^= curTask;
            //rec->task.actMask[i] ^= curTask; // �����������ɿؽ��
            rec->task.actMask[i] &= (~curTask);
            taskIndex = log_2n(curTask);

            // �ж��Ƿ�Ϊһ���������������������ȥ��
            if (rec->task.prdTick[i][taskIndex] == 0)
            {
                rec->task.taskMask[i] &= (~curTask);
            }

            // �������ִ���Ƿ��ж�ʧ
            if ((rec->task.tick - rec->task.startTick[i][taskIndex]) >= rec->task.prdTick[i][taskIndex])
            {
                // ����ʧ����Ϊֻ��ʧһ��
                errcode.id = (void *)(rec->task.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_serious;
                errcode.errCode = casSch_taskExecute_task_miss;
                ((hcasSch)rec->casSch)->err(rec->casSch, &errcode);

                // ������һ������ʼʱ��
                rec->task.startTick[i][taskIndex] += rec->task.prdTick[i][taskIndex];
            }
            else if ((rec->task.tick - rec->task.startTick[i][taskIndex]) >= (rec->task.prdTick[i][taskIndex] >> 1))
            {
                errcode.id = (void *)(rec->task.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_taskExecute_task_delay;
                ((hcasSch)rec->casSch)->err(rec->casSch, &errcode);
            }
            else
            {
                ;
            }

            // ִ������
            rec->task.taskGroup[i][taskIndex]();

            break;
        }
    }

    // ���ز�ѯ���񼤻�״̬
    rec->next = schSm_sta_update;
}
void schSm_act_default(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;
    errCode errcode;

    errcode.id = (void *)rec;
    errcode.cpnPartId = casSch_schSm_pi;
    errcode.errClassify = EC_EC_se;
    errcode.errRanking = EC_ER_serious;
    errcode.errCode = casSch_schSm_sta_default;
    ((hcasSch)rec->casSch)->err(rec->casSch, &errcode);

    rec->next = schSm_sta_update;
}


// --------------------------------------------------------------
// ������������ඨ��
// --------------------------------------------------------------
hcasSch casSch_init(hcasSch cthis, hmeasure time, hvfbOcasSch vfbOcasSch)
{
    cthis->time = time;
    cthis->vfbOcasSch = vfbOcasSch;

    return cthis;
}

void casSch_timer(hcasSch t)
{
    t->schSmRec.task.tick++;
    t->tickOut(t);
}
void casSch_run(hcasSch t)
{
    t->schSm[t->schSmRec.next](&t->schSmRec);
}

void casSch_tickOut(hcasSch t)
{
    t->vfbOcasSch->tickOut(t->vfbOcasSch);
}
void casSch_err(hcasSch t, herrCode code)
{
    t->vfbOcasSch->err(t->vfbOcasSch, code);
}

void casSch_addTask(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick)
{
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if (id > (t->schSmRec.task.taskGroupNum * 32))
    {
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_addTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_addTask_id_outOfRange;
        t->err(t, &errcode);
    }
    else
    {
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->schSmRec.task.taskMask[taskGroup];

        // �ж������Ƿ����
        if ((taskMask & curTask) != 0)
        {
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_addTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_addTask_task_exist;
            t->err(t, &errcode);
        }
        else
        {
            t->schSmRec.task.taskMask[taskGroup] |= curTask;
            t->schSmRec.task.taskGroup[taskGroup][taskIndex] = schTask;
            t->schSmRec.task.prdTick[taskGroup][taskIndex] = prdTick;
            t->schSmRec.task.startTick[taskGroup][taskIndex] = startTick;
        }
    }
}
void casSch_delTask(hcasSch t, int16 id, void(*schTask)(void))
{
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if (id > (t->schSmRec.task.taskGroupNum * 32))
    {
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_delTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_delTask_id_outOfRange;
        t->err(t, &errcode);
    }
    else
    {
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->schSmRec.task.taskMask[taskGroup];

        // �ж������Ƿ����
        if ((taskMask & curTask) == 0)
        {
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_delTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_delTask_task_null;
            t->err(t, &errcode);
        }
        else
        {
            // �ж��Ƿ�ΪĿ������
            if (t->schSmRec.task.taskGroup[taskGroup][taskIndex] != schTask)
            {
                errcode.id = (void *)t;
                errcode.cpnPartId = casSch_delTask_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_delTask_task_false;
                t->err(t, &errcode);
            }
            else
            {
                t->schSmRec.task.actMask[taskGroup] &= (~curTask);
                t->schSmRec.task.taskMask[taskGroup] &= (~curTask);
                t->schSmRec.task.taskGroup[taskGroup][taskIndex] = schTaskDefault;
                t->schSmRec.task.prdTick[taskGroup][taskIndex] = 0;
                t->schSmRec.task.startTick[taskGroup][taskIndex] = 0;
            }
        }
    }
}

CC(casSch)
{
    int16 i = 0;
    int16 j = 0;

    cthis->init = casSch_init;
    cthis->timer = casSch_timer;
    cthis->run = casSch_run;
    cthis->tickOut = casSch_tickOut;
    cthis->err = casSch_err;
    cthis->addTask = casSch_addTask;
    cthis->delTask = casSch_delTask;

    cthis->schSmRec.next = schSm_sta_init;
    cthis->schSmRec.task.tick = 0;
    cthis->schSmRec.task.taskGroupNum = SCH_TASK_GROUP_NUM;
    for (i = 0; i < cthis->schSmRec.task.taskGroupNum; i++)
    {
        cthis->schSmRec.task.actMask[i] = 0;
        cthis->schSmRec.task.taskMask[i] = 0;

        for (j = 0; j < 32; j++)
        {
            cthis->schSmRec.task.startTick[i][j] = 0;
            cthis->schSmRec.task.prdTick[i][j] = 0;
            cthis->schSmRec.task.taskGroup[i][j] = schTaskDefault;
        }
    }
    cthis->schSm[schSm_sta_init] = schSm_act_init;
    cthis->schSm[schSm_sta_update] = schSm_act_update;
    cthis->schSm[schSm_sta_execute] = schSm_act_execute;
    cthis->schSm[schSm_sta_default] = schSm_act_default;

    return cthis;
}
CD(casSch)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// �첽���ȹ��ܺ���
// --------------------------------------------------------------
void abi_casSch_timer(void)
{
    casSchA.timer(casSchA.self);
}
void abi_casSch_mainLoop(void)
{
    casSchA.run(casSchA.self);
}


// --------------------------------------------------------------
// �����ʵ����
// --------------------------------------------------------------
casSch casSchA;
