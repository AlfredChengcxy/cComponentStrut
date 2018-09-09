/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbOcsLedServ.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 22:42:51
* @brief        :���csLedServ ����ඨ��
* @others       :
* @history      :180907 pxf ���ν���
***************************************************************************/

#include "csLedServ.h"

/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbOcsLedServInit(void){
    int16 rtv = 0;

    CN(vfbOcsLedServ, &vfbOcsLedServA, vfbMcsLedServ_vfbOcsLedServ_err);
    if(OPRS(vfbOcsLedServA) != OOPC_NULL){
        rtv = vfbMcsLedServInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* ����������
***********************************************************/
/*������ʼ������
* ����: cthis vfbOcsLedServ��ָ��
* ���: hvfbOcsLedServ cthis/OOPC_NULL
***********************************************/
hvfbOcsLedServ vfbOcsLedServ_init(hvfbOcsLedServ cthis, void (*err)(hvfbOcsLedServ t, herrCode code)){
    // ���ܺ�������
    cthis->err = err;
    //cthis->output = output;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*����๹�캯��
* ����: cthis vfbOcsLedServ��ָ��
* ���: hvfbOcsLedServ cthis/OOPC_NULL
***********************************************/
CC(vfbOcsLedServ){
    // ���ܺ�������
    cthis->init = vfbOcsLedServ_init;
    //TODO

    // ��������
    cthis->schParam.id = 0;
    cthis->schParam.schTask = csLedServSch;
    cthis->schParam.startTick = (CSLEDSERV_START_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    cthis->schParam.prdTick = (CSLEDSERV_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    //TODO

    return cthis;
}
/*�������������
* ����: cthis vfbOcsLedServ��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbOcsLedServ){
    return OOPC_TRUE;
}


/***********************************************************
* ������ʵ����
***********************************************************/
/*��������ʵ��
***********************************************/
vfbOcsLedServ vfbOcsLedServA;


/**************************** Copyright(C) pxf ****************************/
