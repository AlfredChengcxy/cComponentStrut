/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbIcsLedServ.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 14:40:50
* @brief        :���csLedServ �����ඨ��
* @others       :
* @history      :180901 pxf ���ν���
***************************************************************************/

#include "csLedServ.h"

/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbIcsLedServInit(void){
    int16 rtv = 0;

    CN(vfbIcsLedServ, &vfbIcsLedServA, &csLedServA);
    if(OPRS(vfbIcsLedServA) != OOPC_NULL){
        rtv = csLedServInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* ������붨��
***********************************************************/
/*������ʼ������
* ����: cthis vfbIcsLedServ��ָ��
* ���: hvfbIcsLedServ cthis/OOPC_NULL
***********************************************/
hvfbIcsLedServ vfbIcsLedServ_init(hvfbIcsLedServ cthis, hcsLedServ csLedServ){
    // ע��ʵ������
    cthis->csLedServ = csLedServ;
    //TODO

    return cthis;
}

/*��������๦�ܺ���
* ����: t vfbIcsLedServ��ָ��
* ���: ��
***********************************************/
void vfbIcsLedServ_input(hvfbIcsLedServ t){
    ;
}

/*����๹�캯��
* ����: cthis vfbIcsLedServ��ָ��
* ���: hvfbIcsLedServ cthis/OOPC_NULL
***********************************************/
CC(vfbIcsLedServ){
    // ���ܺ�������
    cthis->init = vfbIcsLedServ_init;
    //cthis->input = vfbIcsLedServ_input;
    //TODO

    return cthis;
}
/*�������������
* ����: cthis vfbIcsLedServ��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbIcsLedServ){
    return OOPC_TRUE;
}


/***********************************************************
* �������ʵ����
***********************************************************/
/*���������ʵ��
***********************************************/
vfbIcsLedServ vfbIcsLedServA;


/**************************** Copyright(C) pxf ****************************/
