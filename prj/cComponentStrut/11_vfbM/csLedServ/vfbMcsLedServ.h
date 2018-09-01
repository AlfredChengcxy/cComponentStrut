/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcsLedServ.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 14:40:50
* @brief        :���csLedServ ������������������
* @others       :
* @history      :180901 pxf ���ν���
***************************************************************************/

#ifndef VFBMCSLEDSERV_H_
#define VFBMCSLEDSERV_H_

#include "..\..\01_std\std.h"
#include "..\..\06_cas\casSch\casSch.h"
#include "..\..\07_cs\csLedServ\csLedServ.h"
#include "..\vfbMCfg.h"

/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbMcsLedServInit(void);


/***********************************************************
* ��������ඨ��
***********************************************************/
/*�������������
***********************************************/
CL(vfbMcsLedServ){
    hvfbMcsLedServ self;
    hvfbMcsLedServ (*init)(hvfbMcsLedServ cthis, hvfbOcsLedServ vfbOcsLedServ, hvfbIcasSch vfbIcasSch);

    // �������������ܺ���
    //void (*output)(hvfbMcsLedServ t);
    //TODO

    // ע���������༰����������
    INJ(vfbOcsLedServ, vfbOcsLedServ);
    INJ(vfbIcasSch, vfbIcasSch);
};

/*��������ӿ�����
* ������ʽ: �����+ʵ����+ʵ���๦��
***********************************************/
//void vfbMcsLedServ_vfbOcsLedServ_output(hvfbOcsLedServ t);

/*���������ʵ��
***********************************************/
extern vfbMcsLedServ vfbMcsLedServA;


#endif /* VFBMCSLEDSERV_H_ */

/**************************** Copyright(C) pxf ****************************/
