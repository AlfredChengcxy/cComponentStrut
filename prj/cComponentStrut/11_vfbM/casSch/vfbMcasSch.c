/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcasSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :���casSch �����ඨ��
* @others       :
* @history      :180831 pxf ���ν���
***************************************************************************/

#include "vfbMcasSch.h"
#include "..\..\07_cs\csLedServ\csLedServ.h"
#include "..\..\09_cpc\cpcFmea\cpcFmea.h"

/*�������id��ʱ���ã����ʵ��ʹ��ʱ������vbfMCfg.h������
***********************************************************/
//#define casSch_id_priority_cfg   0


/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbMcasSchInit(void){
    int16 rtv = 0;

    CN(vfbMcasSch, &vfbMcasSchA, &vfbOcasSchA, &vfbIcasSchA);
    if(OPRS(vfbMcasSchA) != OOPC_NULL){
        rtv |= vfbIcsLedServInit();
        rtv |= vfbIcpcFmeaInit();
        //TODO ������������г�ʼ��

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
* ����: cthis vfbMcasSch��ָ��
* ���: hvfbMcasSch cthis/OOPC_NULL
***********************************************/
hvfbMcasSch vfbMcasSch_init(hvfbMcasSch cthis, hvfbOcasSch vfbOcasSch, hvfbIcasSch vfbIcasSch){
    // ע��ʵ������
    cthis->vfbOcasSch = vfbOcasSch;
    cthis->vfbIcasSch = vfbIcasSch;
    //TODO

    return cthis;
}

/*hvfbMcasSch_tickOut �������
* ����: cthis vfbMcasSch��ָ��
* ���: ��
***********************************************/
void vfbMcasSch_tickOut(hvfbMcasSch t)
{}

/*hvfbMcasSch_err �������
* ����: cthis vfbMcasSch��ָ��
* ���: ��
***********************************************/
void vfbMcasSch_err(hvfbMcasSch t, herrCode code)
{}

/*��������๹�캯��
* ����: cthis vfbMcasSch��ָ��
* ���: hvfbMcasSch cthis/OOPC_NULL
***********************************************/
CC(vfbMcasSch){
    // ���ܺ�������
    cthis->init = vfbMcasSch_init;
    cthis->tickOut = vfbMcasSch_tickOut;
    cthis->err = vfbMcasSch_err;

    return cthis;
}
/*�����������������
* ����: cthis vfbMcasSch��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbMcasSch){
    return OOPC_TRUE;
}


/***********************************************************
* ��������ӿڶ���
***********************************************************/
/*�������๦�ܺ���
***********************************************/
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t){}
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code){}


/***********************************************************
* �������ʵ����
***********************************************************/
/*���������ʵ��
***********************************************/
vfbMcasSch vfbMcasSchA;


/**************************** Copyright(C) pxf ****************************/
