/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbOcasSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :���casSch ����ඨ��
* @others       :
* @history      :180831 pxf ���ν���
***************************************************************************/

#include "casSch.h"

/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbOcasSchInit(void){
    int16 rtv = 0;

    CN(vfbOcasSch, &vfbOcasSchA, vfbMcasSch_vfbOcasSch_tickOut, vfbMcasSch_vfbOcasSch_err);
    if(OPRS(vfbOcasSchA) != OOPC_NULL){
        rtv = vfbMcasSchInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* ����������
***********************************************************/
/*������ʼ������
* ����: cthis vfbOcasSch��ָ��
* ���: hvfbOcasSch cthis/OOPC_NULL
***********************************************/
hvfbOcasSch vfbOcasSch_init(hvfbOcasSch cthis,
        void (*tickOut)(hvfbOcasSch t),
        void (*err)(hvfbOcasSch t, herrCode code)){
	// �����������	
    cthis->tickOut = tickOut;
    cthis->err = err;

    return cthis;
}

/*����๹�캯��
* ����: cthis vfbOcasSch��ָ��
* ���: hvfbOcasSch cthis/OOPC_NULL
***********************************************/
CC(vfbOcasSch){
    // ���ܺ�������
    cthis->init = vfbOcasSch_init;
    //TODO

    return cthis;
}
/*�������������
* ����: cthis vfbOcasSch��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbOcasSch){
    return OOPC_TRUE;
}


/***********************************************************
* ������ʵ����
***********************************************************/
/*��������ʵ��
***********************************************/
vfbOcasSch vfbOcasSchA;


/**************************** Copyright(C) pxf ****************************/
