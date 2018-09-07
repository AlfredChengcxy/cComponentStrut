/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbOcpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :���cpcFmea ����ඨ��
* @others       :
* @history      :180907 pxf ���ν���
***************************************************************************/

#include "cpcFmea.h"

/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbOcpcFmeaInit(void){
    int16 rtv = 0;

    CNNP(vfbOcpcFmea, &vfbOcpcFmeaA);
    if(OPRS(vfbOcpcFmeaA) != OOPC_NULL){
        rtv = vfbMcpcFmeaInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* ����������
***********************************************************/
/*������ʼ������
* ����: cthis vfbOcpcFmea��ָ��
* ���: hvfbOcpcFmea cthis/OOPC_NULL
***********************************************/
hvfbOcpcFmea vfbOcpcFmea_init(hvfbOcpcFmea cthis){
    // ���ܺ�������
    //cthis->err = err;
    //cthis->output = output;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*����๹�캯��
* ����: cthis vfbOcpcFmea��ָ��
* ���: hvfbOcpcFmea cthis/OOPC_NULL
***********************************************/
CC(vfbOcpcFmea){
    // ���ܺ�������
    cthis->init = vfbOcpcFmea_init;
    //TODO

    // ��������
    cthis->schParam.id = 0;
    cthis->schParam.schTask = cpcFmeaSch;
    cthis->schParam.startTick = (CPCFMEA_START_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    cthis->schParam.prdTick = (CPCFMEA_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    //TODO

    return cthis;
}
/*�������������
* ����: cthis vfbOcpcFmea��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbOcpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* ������ʵ����
***********************************************************/
/*��������ʵ��
***********************************************/
vfbOcpcFmea vfbOcpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
