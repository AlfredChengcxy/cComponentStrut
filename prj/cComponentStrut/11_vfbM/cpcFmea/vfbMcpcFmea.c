/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :���cpcFmea �����ඨ��
* @others       :
* @history      :180907 pxf ���ν���
***************************************************************************/

#include "vfbMcpcFmea.h"

/*�������id��ʱ���ã����ʵ��ʹ��ʱ������vbfMCfg.h������
***********************************************************/
//#define cpcFmea_id_priority_cfg   0


/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbMcpcFmeaInit(void){
    int16 rtv = 0;

    CN(vfbMcpcFmea, &vfbMcpcFmeaA, &vfbOcpcFmeaA, &vfbIcasSchA);
    if(OPRS(vfbMcpcFmeaA) != OOPC_NULL){
        vfbMcpcFmeaA.vfbOcpcFmea->schParam.id = cpcFmea_id_priority_cfg;
        vfbMcpcFmeaA.vfbOcpcFmea->schParam.prdTick = (CPCFMEA_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
        vfbMcpcFmeaA.vfbOcpcFmea->schParam.startTick = (CPCFMEA_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
        vfbMcpcFmeaA.vfbIcasSch->addTask(vfbMcpcFmeaA.vfbIcasSch,
            vfbMcpcFmeaA.vfbOcpcFmea->schParam.id, vfbMcpcFmeaA.vfbOcpcFmea->schParam.schTask,
            vfbMcpcFmeaA.vfbOcpcFmea->schParam.prdTick, vfbMcpcFmeaA.vfbOcpcFmea->schParam.startTick);

        rtv = 0;
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* ���������
***********************************************************/
/*����������ʼ������
* ����: cthis vfbMcpcFmea��ָ��
* ���: hvfbMcpcFmea cthis/OOPC_NULL
***********************************************/
hvfbMcpcFmea vfbMcpcFmea_init(hvfbMcpcFmea cthis, hvfbOcpcFmea vfbOcpcFmea, hvfbIcasSch vfbIcasSch){
    // ���ܺ�������
    //TODO

    // ��������
    cthis->vfbOcpcFmea = vfbOcpcFmea;
    cthis->vfbIcasSch = vfbIcasSch;
    //TODO

    return cthis;
}

/*��������ܺ���
* ����: t vfbMcpcFmea��ָ��
* ���: ��
***********************************************/
void vfbMcpcFmea_func(hvfbMcpcFmea t){
    ;
}

/*��������๹�캯��
* ����: cthis vfbMcpcFmea��ָ��
* ���: hvfbMcpcFmea cthis/OOPC_NULL
***********************************************/
CC(vfbMcpcFmea){
    // ���ܺ�������
    cthis->init = vfbMcpcFmea_init;
    //cthis->func = vfbMcpcFmea_func;
    //TODO

    // ��������
    //TODO

    return cthis;
}
/*�����������������
* ����: cthis vfbMcpcFmea��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbMcpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* ��������ӿڶ���
***********************************************************/
/*������������������
***********************************************/
//void vfbMcpcFmea_vfbOcpcFmea_err(hvfbOcpcFmea t, herrCode code){
    //TODO
//}

/*�������๦�ܺ���
***********************************************/
//void vfbMcpcFmea_vfbOcpcFmea_output(hvfbOcpcFmea t){
    //TODO
//}


/***********************************************************
* �������ʵ����
***********************************************************/
/*���������ʵ��
***********************************************/
vfbMcpcFmea vfbMcpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
