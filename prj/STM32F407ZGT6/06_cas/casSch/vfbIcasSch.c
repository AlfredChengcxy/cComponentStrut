/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbIcasSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :���casSch �����ඨ��
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
int16 vfbIcasSchInit(void){
    int16 rtv = 0;

    CN(vfbIcasSch, &vfbIcasSchA, &casSchA);
    if(OPRS(vfbIcasSchA) != OOPC_NULL){
        rtv = casSchInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* ������붨��
***********************************************************/
/*������ʼ������
* ����: cthis vfbIcasSch��ָ��
* ���: hvfbIcasSch cthis/OOPC_NULL
***********************************************/
hvfbIcasSch vfbIcasSch_init(hvfbIcasSch cthis, hcasSch casSch){
    // ע��ʵ������
    cthis->casSch = casSch;
    //TODO

    return cthis;
}

/*vfbIcasSch_addTask ����������������
* ����: cthis vfbIcasSch��ָ��
* ���: ��
***********************************************/
void vfbIcasSch_addTask(hvfbIcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick)
{
    t->casSch->addTask(t->casSch, id, schTask, prdTick, startTick);
}

/*vfbIcasSch_delTask �������ɾ��������
* ����: cthis vfbIcasSch��ָ��
* ���: ��
***********************************************/
void vfbIcasSch_delTask(hvfbIcasSch t, int16 id, void(*schTask)(void))
{
    t->casSch->delTask(t->casSch, id, schTask);
}

/*����๹�캯��
* ����: cthis vfbIcasSch��ָ��
* ���: hvfbIcasSch cthis/OOPC_NULL
***********************************************/
CC(vfbIcasSch){
    // ���ܺ�������
    cthis->init = vfbIcasSch_init;
    cthis->addTask = vfbIcasSch_addTask;
    cthis->delTask = vfbIcasSch_delTask;

    return cthis;
}
/*�������������
* ����: cthis vfbIcasSch��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbIcasSch){
    return OOPC_TRUE;
}


/***********************************************************
* �������ʵ����
***********************************************************/
/*���������ʵ��
***********************************************/
vfbIcasSch vfbIcasSchA;


/**************************** Copyright(C) pxf ****************************/
