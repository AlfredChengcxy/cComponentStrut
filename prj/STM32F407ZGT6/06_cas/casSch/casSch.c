/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :casSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :���casSch ����ඨ��
* @others       :
* @history      :180831 pxf ���ν���
***************************************************************************/

#include "casSch.h"
#include "../../02_bm/func/func.h"
#include "../../04_abi/casSch/abicasSch.h"

/***********************************************************
* �����ʼ��
***********************************************************/
/*�����ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 casSchInit(void){
    int16 rtv = 0;

    CN(casSch, &casSchA, &smcasSch[0], &vfbOcasSchA, &time);
    if(OPRS(casSchA) != OOPC_NULL){
        rtv = vfbOcasSchInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* �������
***********************************************************/
/*������е���
* ����: ��
* ���: ��
***********************************************/
//void casSchSch(void){
//    casSchA.run(casSchA.self);
//}


/***********************************************************
* ���ͨ�ù��ܺ���
***********************************************************/
/*schTaskDefaultĬ������
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
static void schTaskDefault(void){}

/*log_2n ������2^n�Ķ�Ӧ�Ķ���n
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
static inline int16 log_2n(uint32 num){
    int16 n = 0;

    if((num & 0xFFFF0000U) != 0U){
        n += 16;
    }
    if((num & 0xFF00FF00U) != 0U){
        n += 8;
    }
    if((num & 0xF0F0F0F0U) != 0U){
        n += 4;
    }
    if ((num & 0xCCCCCCCCU) != 0U){
        n += 2;
    }
    if ((num & 0xAAAAAAAAU) != 0U){
        n += 1;
    }

    return n;
}

/***********************************************************
* ���״̬��
***********************************************************/
/*���״̬������
***********************************************/
SMDF(smcasSch, SM_CASSCH_STA_LIST);

/*smcasSch_act_init
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcasSch_act_init(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;

    rec->casSch = (void *)&casSchA;
    rec->next = smcasSch_sta_update;
}

/*smcasSch_sta_update
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcasSch_act_update(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;
    //((hcasSch)(rec->casSch))->
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;

    for(i = 0; i < rec->taskGroups.taskGroupNum; i++){
        // ���¸��鼤������
        taskMask = rec->taskGroups.taskMask[i];
        while(taskMask != 0){
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            taskMask ^= curTask;
            taskIndex = log_2n(curTask);

            if((rec->taskGroups.tick - rec->taskGroups.startTick[i][taskIndex]) >= rec->taskGroups.prdTick[i][taskIndex]){
                // ���¼���״̬�Լ���һ������ʼ����
                rec->taskGroups.actMask[i] |= curTask;
                rec->taskGroups.startTick[i][taskIndex] += rec->taskGroups.prdTick[i][taskIndex];
            }
        }
    }

    // ����������º����ִ��״̬�鿴�Ƿ���Ҫִ������
    rec->next = smcasSch_sta_execute;
}

/*smcasSch_act_execute
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcasSch_act_execute(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;
    //((hcasSch)(rec->casSch))->
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;
    errCode errcode;
#if (CASSCH_TASK_MEASURE_ENABLE == 1)
    static uint32 taskTimePot = 0;
    uint32 currUsage = 0;
    ((hcasSch)(rec->casSch))->time->iMeasure.start(&taskTimePot);
#endif

    for(i = 0; i < rec->taskGroups.taskGroupNum; i++){
        // �鿴�������񣬲�ִ��������ȼ�����
        taskMask = rec->taskGroups.actMask[i];
        if(taskMask != 0){
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            //taskMask ^= curTask;
            //rec->taskGroups.actMask[i] ^= curTask; // �����������ɿؽ��
            rec->taskGroups.actMask[i] &= (~curTask);
            taskIndex = log_2n(curTask);

            // �ж��Ƿ�Ϊһ���������������������ȥ��
            if(rec->taskGroups.prdTick[i][taskIndex] == 0){
                rec->taskGroups.taskMask[i] &= (~curTask);
            }

            // �������ִ���Ƿ��ж�ʧ
            if((rec->taskGroups.tick - rec->taskGroups.startTick[i][taskIndex]) >= rec->taskGroups.prdTick[i][taskIndex]){
                // ����ʧ����Ϊֻ��ʧһ��
                errcode.id = (void *)(rec->taskGroups.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_serious;
                errcode.errCode = casSch_taskExecute_task_miss;
                ((hcasSch)(rec->casSch))->err(rec->casSch, &errcode);

                // ������һ������ʼʱ��
                rec->taskGroups.startTick[i][taskIndex] += rec->taskGroups.prdTick[i][taskIndex];
            }else if((rec->taskGroups.tick - rec->taskGroups.startTick[i][taskIndex]) >= (rec->taskGroups.prdTick[i][taskIndex] >> 1)){
                errcode.id = (void *)(rec->taskGroups.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_taskExecute_task_delay;
                ((hcasSch)(rec->casSch))->err(rec->casSch, &errcode);
            }else{
                ;
            }

            // ִ������
            rec->taskGroups.taskGroup[i][taskIndex]();

            break;
        }
    }

    // ���ز�ѯ���񼤻�״̬
    rec->next = smcasSch_sta_update;

#if (CASSCH_TASK_MEASURE_ENABLE == 1)
    ((hcasSch)(rec->casSch))->taskTime = ((hcasSch)(rec->casSch))->time->iMeasure.end(taskTimePot);
    // ��ǰʹ������Ҫ��taskTime����CASSCH_TIMER_PRD_CFG/CASSCH_TIME_MEASURE_PRECISION_CFG���м���
    // Ŀǰʱ�������ȷ��0.1us��ʹ���ʾ�ȷ��0.1%����ֵ��ϵ��Ҫ����1000����ϵ������taskTime�պ�����
    //currUsage = ((hcasSch)(rec->casSch))->taskTime / ((CASSCH_TIMER_PRD_CFG / CASSCH_TIME_MEASURE_PRECISION_CFG) / 1000.0L));
    currUsage = ((hcasSch)(rec->casSch))->taskTime;
    ((hcasSch)(rec->casSch))->usage = lowpassFilter(currUsage, ((hcasSch)(rec->casSch))->usage, 3);
#endif
}

/*smcasSch_act_default
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcasSch_act_default(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;
    //((hcasSch)(rec->casSch))->
    errCode errcode;

    errcode.id = (void *)rec;
    errcode.cpnPartId = casSch_smcasSch_pi;
    errcode.errClassify = EC_EC_se;
    errcode.errRanking = EC_ER_serious;
    errcode.errCode = casSch_smcasSch_sta_default;
    ((hcasSch)(rec->casSch))->err(rec->casSch, &errcode);

    rec->next = smcasSch_sta_update;
}


/***********************************************************
* �������
***********************************************************/
/*������ʼ������
* ����: cthis casSch��ָ��
* ���: hcasSch cthis/OOPC_NULL
***********************************************/
hcasSch casSch_init(hcasSch cthis, hstaAct smcasSch, hvfbOcasSch vfbOcasSch, hmeasure time){
    // ע��ʵ������
    cthis->smcasSch = smcasSch;
    cthis->vfbOcasSch = vfbOcasSch;
    cthis->time = time;

    return cthis;
}

/*������к���
* ����: t casSch��ָ��
* ���: ��
***********************************************/
void casSch_run(hcasSch t){
    SMRE(t->smcasSch, t->smcasSchRec);
}

/*casSch_tick ���ĸ���
* ����: t casSch��ָ��
* ���: ��
***********************************************/
void casSch_tick(hcasSch t){
    t->smcasSchRec.taskGroups.tick++;
    t->tickOut(t);
}

/*casSch_tickOut �������
* ����: t casSch��ָ��
* ���: ��
***********************************************/
void casSch_tickOut(hcasSch t){
    t->vfbOcasSch->tickOut(t->vfbOcasSch);
}

/*casSch_delay ������ʱ
* ����: t casSch��ָ��
*       tick �洢��ʱ���ļ���ʼ���ģ���15λ�洢��ʱ���ģ���16λ�洢��ʼ����
*            ��16λ�洢�Ƿ��ѽ�����ʱ���ѽ�����ʱ�����1������Ϊ0
*            ����ʱ�ѵ�����£���16λ������һ����ʱ��������¸���Ϊ��һ�ε���ʼ����
* ���: 0��ʱ�ѵ�����0��ʱδ��
***********************************************/
int16 casSch_delay(hcasSch t, uint32 *tick){
    uint32 tickTemp = 0;
    int16 rtv = 0;

    if(!(*tick & 0x00008000)){
        tickTemp = t->smcasSchRec.taskGroups.tick;
        tickTemp = (tickTemp << 16);
        tickTemp |= 0x00008000;  // �����ѽ�����ʱ��־
        *tick &= 0x00007FFF;
        *tick |= tickTemp;
    }

    tickTemp = ((*tick & 0xFFFF0000) >> 16);
    rtv = ((t->smcasSchRec.taskGroups.tick - tickTemp) >= (*tick & 0x00007FFF));
    if(!rtv){
        *tick &= 0xFFFF7FFF;     // ���������ʱ��־
    }

    return rtv;
}

/*casSch_err �������
* ����: t casSch��ָ��
* ���: ��
***********************************************/
void casSch_err(hcasSch t, herrCode code){
    t->vfbOcasSch->err(t->vfbOcasSch, code);
}

/*casSch_addTask �������
* ����: t casSch��ָ��
* ���: ��
***********************************************/
void casSch_addTask(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick){
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if(id > (t->smcasSchRec.taskGroups.taskGroupNum * 32)){
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_addTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_addTask_id_outOfRange;
        t->err(t, &errcode);
    }else{
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->smcasSchRec.taskGroups.taskMask[taskGroup];

        // �ж������Ƿ����
        if ((taskMask & curTask) != 0){
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_addTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_addTask_task_exist;
            t->err(t, &errcode);
        }else{
            t->smcasSchRec.taskGroups.taskMask[taskGroup] |= curTask;
            t->smcasSchRec.taskGroups.taskGroup[taskGroup][taskIndex] = schTask;
            t->smcasSchRec.taskGroups.prdTick[taskGroup][taskIndex] = prdTick;
            t->smcasSchRec.taskGroups.startTick[taskGroup][taskIndex] = startTick;
        }
    }
}

/*casSch_delTask ɾ������
* ����: t casSch��ָ��
* ���: ��
***********************************************/
void casSch_delTask(hcasSch t, int16 id, void(*schTask)(void)){
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if(id > (t->smcasSchRec.taskGroups.taskGroupNum * 32)){
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_delTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_delTask_id_outOfRange;
        t->err(t, &errcode);
    }else{
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->smcasSchRec.taskGroups.taskMask[taskGroup];

        // �ж������Ƿ����
        if((taskMask & curTask) == 0){
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_delTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_delTask_task_null;
            t->err(t, &errcode);
        }else{
            // �ж��Ƿ�ΪĿ������
            if(t->smcasSchRec.taskGroups.taskGroup[taskGroup][taskIndex] != schTask){
                errcode.id = (void *)t;
                errcode.cpnPartId = casSch_delTask_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_delTask_task_false;
                t->err(t, &errcode);
            }else{
                t->smcasSchRec.taskGroups.actMask[taskGroup] &= (~curTask);
                t->smcasSchRec.taskGroups.taskMask[taskGroup] &= (~curTask);
                t->smcasSchRec.taskGroups.taskGroup[taskGroup][taskIndex] = schTaskDefault;
                t->smcasSchRec.taskGroups.prdTick[taskGroup][taskIndex] = 0;
                t->smcasSchRec.taskGroups.startTick[taskGroup][taskIndex] = 0;
            }
        }
    }
}

/*����๹�캯��
* ����: cthis casSch��ָ��
* ���: hcasSch cthis/OOPC_NULL
***********************************************/
CC(casSch){
    int16 i = 0;
    int16 j = 0;

    // ���ܺ�������
    cthis->init = casSch_init;
    cthis->run = casSch_run;
    cthis->tick = casSch_tick;
    cthis->delay = casSch_delay;
    cthis->tickOut = casSch_tickOut;
    cthis->err = casSch_err;
    cthis->addTask = casSch_addTask;
    cthis->delTask = casSch_delTask;

    // ��������
    cthis->usage = 0;
    cthis->taskTime = 0;

    cthis->smcasSchRec.next = smcasSch_sta_init;
    cthis->smcasSchRec.taskGroups.tick = 0;
    cthis->smcasSchRec.taskGroups.taskGroupNum = SCH_TASK_GROUP_NUM;
    for(i = 0; i < cthis->smcasSchRec.taskGroups.taskGroupNum; i++){
        cthis->smcasSchRec.taskGroups.actMask[i] = 0;
        cthis->smcasSchRec.taskGroups.taskMask[i] = 0;

        for(j = 0; j < 32; j++){
            cthis->smcasSchRec.taskGroups.startTick[i][j] = 0;
            cthis->smcasSchRec.taskGroups.prdTick[i][j] = 0;
            cthis->smcasSchRec.taskGroups.taskGroup[i][j] = schTaskDefault;
        }
    }

    return cthis;
}
/*�������������
* ����: cthis casSch��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(casSch){
    return OOPC_TRUE;
}


/***********************************************************
* ����첽���ȹ��ܺ���
***********************************************************/
/*�첽���ȹ��ܺ���
***********************************************/
void casSch_abi_timer(void){
    casSchA.tick(casSchA.self);
}
void casSch_abi_mainLoop(void){
    casSchA.run(casSchA.self);
}


/***********************************************************
* ���ʵ����
***********************************************************/
/*�����ʵ��
***********************************************/
casSch casSchA;


/**************************** Copyright(C) pxf ****************************/
