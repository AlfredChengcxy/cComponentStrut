/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :cpcFmea.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :���cpcFmea �����ࡢ����ࡢ�����������������ͷ�ļ�
* @others       :
* @history      :180907 pxf ���ν���
***************************************************************************/

#ifndef CPCFMEA_H_
#define CPCFMEA_H_

#include "..\..\01_std\std.h"
#include "..\..\02_bm\fifo\fifo.h"
#include "..\..\06_cas\casSch\casSch.h"
#include "cpcFmeaCfg.h"
#include "cpcFmeaErrCode.h"

/***********************************************************
* �����ʼ��
***********************************************************/
/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbIcpcFmeaInit(void);

/*�����ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 cpcFmeaInit(void);

/*��������ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 vfbOcpcFmeaInit(void);

/*���������ʼ���ⲿ����
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
extern int16 vfbMcpcFmeaInit(void);


/***********************************************************
* �������
***********************************************************/
/*������е���
* ����: ��
* ���: ��
***********************************************/
void cpcFmeaSch(void);


/***********************************************************
* ���������ͨ����������
***********************************************************/


/***********************************************************
* ��������ͨ����������
***********************************************************/


/***********************************************************
* �������ඨ��
***********************************************************/
/*������������
***********************************************/
CL(vfbOcpcFmea){
    hvfbOcpcFmea self;
    hvfbOcpcFmea (*init)(hvfbOcpcFmea cthis);

    // �����������
    schParam schParam;    // ������Ȳ���
    //TODO

    // �������๦�ܺ���
    //void (*err)(hvfbOcpcFmea t, herrCode code);
    //void (*output)(hvfbO%s t);
    //TODO
};

/*���������ⲿ�ӿ�����
* ������ʽ: �����+ʵ����+ʵ���๦��
***********************************************/
//extern void vfbMcpcFmea_vfbOcpcFmea_err(hvfbOcpcFmea t, herrCode code);
//extern void vfbMcpcFmea_vfbOcpcFmea_output(hvfbOcpcFmea t);
//TODO

/*��������ʵ��
***********************************************/
extern vfbOcpcFmea vfbOcpcFmeaA;


/***********************************************************
* ����ඨ��
***********************************************************/
/*���״̬��״̬
* ������״̬init/default��״̬list����ʾ��Ĭ�ϸ���
* ״̬list�����ʵ��Ӧ�ý�����д��list�޸ĺ���Ӧ״̬�����ö�Ӧ�޸�
***********************************************/
#define SM_CPCFMEA_STA_LIST(_) \
    _(smcpcFmea, sta1)\
    _(smcpcFmea, sta2)

/*���״̬������
***********************************************/
SMDC(smcpcFmea, SM_CPCFMEA_STA_LIST){
    sta next;
    errCode code[CPCFMEA_ERRCODE_FIFO_LEN_CFG];
    fifo errFifo;
    //TODO

    // ע�������
    void *cpcFmea;
};


/*���������
***********************************************/
CL(cpcFmea){
    hcpcFmea self;
    hcpcFmea (*init)(hcpcFmea cthis, hstaAct smcpcFmea, hvfbOcpcFmea vfbOcpcFmea,
            void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

    // �������״̬��
    smcpcFmeaRec smcpcFmeaRec;
    hstaAct smcpcFmea;

    // ���������ز���
    //TODO

    // ������й��ܺ���
    void (*run)(hcpcFmea t);
    //void (*example)(hcpcFmea t);
    //TODO

    // ������빦�ܺ���
    void (*save)(hcpcFmea t, herrCode code);
    //TODO

    // ���������ܺ���
    //void (*err)(hcpcFmea t, herrCode code);
    //void (*output)(hcpcFmea t);
    //TODO

    // ע���������༰����������
    INJ(vfbOcpcFmea, vfbOcpcFmea);
    EXT(fifo);
};

/*�첽���ȹ��ܺ���
* ������ʽ: �����+ʵ����+ʵ���๦��
* ֻ��cas����������д˺���
***********************************************/
//void cpcFmea_abi_example(void);
//TODO

/*�����ʵ��
***********************************************/
extern cpcFmea cpcFmeaA;


/***********************************************************
* ��������ඨ��
***********************************************************/
/*�������������
***********************************************/
CL(vfbIcpcFmea){
    hvfbIcpcFmea self;
    hvfbIcpcFmea (*init)(hvfbIcpcFmea cthis, hcpcFmea cpcFmea);

    // ��������๦�ܺ���
    void (*save)(hvfbIcpcFmea t, herrCode code);
    //TODO

    // ע�������
    INJ(cpcFmea, cpcFmea);
};

/*���������ʵ��
***********************************************/
extern vfbIcpcFmea vfbIcpcFmeaA;


#endif /* CPCFMEA_H_ */

/**************************** Copyright(C) pxf ****************************/
