/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcasSch.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :���casSch ������������������
* @others       :
* @history      :180831 pxf ���ν���
***************************************************************************/

#ifndef VFBMCASSCH_H_
#define VFBMCASSCH_H_

#include "../../01_std/std.h"
#include "../../06_cas/casSch/casSch.h"
#include "../vfbMCfg.h"

/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbMcasSchInit(void);


/***********************************************************
* ��������ඨ��
***********************************************************/
/*�������������
***********************************************/
CL(vfbMcasSch){
    hvfbMcasSch self;
    hvfbMcasSch (*init)(hvfbMcasSch cthis, hvfbOcasSch vfbOcasSch, hvfbIcasSch vfbIcasSch);

    // �������������ܺ���
    void (*tickOut)(hvfbMcasSch t);
    void (*err)(hvfbMcasSch t, herrCode code);

    // ע���������༰����������
    INJ(vfbOcasSch, vfbOcasSch);
    INJ(vfbIcasSch, vfbIcasSch);
};

/*��������ӿ�����
* ������ʽ: �����+ʵ����+ʵ���๦��
***********************************************/
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

/*���������ʵ��
***********************************************/
extern vfbMcasSch vfbMcasSchA;


#endif /* VFBMCASSCH_H_ */

/**************************** Copyright(C) pxf ****************************/
