/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcpcFmea.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :���cpcFmea ������������������
* @others       :
* @history      :180907 pxf ���ν���
***************************************************************************/

#ifndef VFBMCPCFMEA_H_
#define VFBMCPCFMEA_H_

#include "../../01_std/std.h"
#include "../../06_cas/casSch/casSch.h"
#include "../../09_cpc/cpcFmea/cpcFmea.h"
#include "../vfbMCfg.h"

/***********************************************************
* ��������ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbMcpcFmeaInit(void);


/***********************************************************
* ��������ඨ��
***********************************************************/
/*�������������
***********************************************/
CL(vfbMcpcFmea){
    hvfbMcpcFmea self;
    hvfbMcpcFmea (*init)(hvfbMcpcFmea cthis, hvfbOcpcFmea vfbOcpcFmea, hvfbIcasSch vfbIcasSch);

    // ����������
    //TODO

    // ��������ܺ���
    //void (*func)(hvfbMcpcFmea t);
    //TODO

    // ע���������༰����������
    INJ(vfbOcpcFmea, vfbOcpcFmea);
    INJ(vfbIcasSch, vfbIcasSch);
};

/*��������ӿ�����
* ������ʽ: �����+ʵ����+ʵ���๦��
***********************************************/
//void vfbMcpcFmea_vfbOcpcFmea_err(hvfbOcpcFmea t, herrCode code);
//void vfbMcpcFmea_vfbOcpcFmea_output(hvfbOcpcFmea t);

/*���������ʵ��
***********************************************/
extern vfbMcpcFmea vfbMcpcFmeaA;


#endif /* VFBMCPCFMEA_H_ */

/**************************** Copyright(C) pxf ****************************/
