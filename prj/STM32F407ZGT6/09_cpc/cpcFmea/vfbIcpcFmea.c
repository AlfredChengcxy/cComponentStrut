/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbIcpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :���cpcFmea �����ඨ��
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
int16 vfbIcpcFmeaInit(void){
    int16 rtv = 0;

    CN(vfbIcpcFmea, &vfbIcpcFmeaA, &cpcFmeaA);
    if(OPRS(vfbIcpcFmeaA) != OOPC_NULL){
        rtv = cpcFmeaInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* ������붨��
***********************************************************/
/*������ʼ������
* ����: cthis vfbIcpcFmea��ָ��
* ���: hvfbIcpcFmea cthis/OOPC_NULL
***********************************************/
hvfbIcpcFmea vfbIcpcFmea_init(hvfbIcpcFmea cthis, hcpcFmea cpcFmea){
    // ���ܺ�������
    //TODO

    // ��������
    cthis->cpcFmea = cpcFmea;
    //TODO

    return cthis;
}

/*vfbIcpcFmea_save
* ����: t vfbIcpcFmea��ָ�룬code errCodeָ��
* ���: ��
***********************************************/
void vfbIcpcFmea_save(hvfbIcpcFmea t, herrCode code){
    t->cpcFmea->save(t->cpcFmea, code);
}

/*����๹�캯��
* ����: cthis vfbIcpcFmea��ָ��
* ���: hvfbIcpcFmea cthis/OOPC_NULL
***********************************************/
CC(vfbIcpcFmea){
    // ���ܺ�������
    cthis->init = vfbIcpcFmea_init;
    cthis->save = vfbIcpcFmea_save;
    //TODO

    // ��������
    //TODO

    return cthis;
}
/*�������������
* ����: cthis vfbIcpcFmea��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbIcpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* �������ʵ����
***********************************************************/
/*���������ʵ��
***********************************************/
vfbIcpcFmea vfbIcpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
