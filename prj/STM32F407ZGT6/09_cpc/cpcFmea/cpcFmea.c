/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :cpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :���cpcFmea ����ඨ��
* @others       :
* @history      :180907 pxf ���ν���
***************************************************************************/

#include "cpcFmea.h"

/***********************************************************
* �����ʼ��
***********************************************************/
/*�����ʼ��
* ����: ��
* ���: int16 0-�ɹ�,-1-ʧ��
***********************************************/
int16 cpcFmeaInit(void){
    int16 rtv = 0;

    CN(cpcFmea, &cpcFmeaA, &smcpcFmea[0], &vfbOcpcFmeaA,
            &cpcFmeaA.smcpcFmeaRec.code, sizeof(cpcFmeaA.smcpcFmeaRec.code), sizeof(errCode));
    if(OPRS(cpcFmeaA) != OOPC_NULL){
        rtv = vfbOcpcFmeaInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* �������
***********************************************************/
/*������е���
* ����: ��
* ���: ��
***********************************************/
void cpcFmeaSch(void){
    cpcFmeaA.run(cpcFmeaA.self);
}


/***********************************************************
* ���ͨ�ù��ܺ���
***********************************************************/


/***********************************************************
* ���״̬��
***********************************************************/
/*���״̬������
***********************************************/
SMDF(smcpcFmea, SM_CPCFMEA_STA_LIST);

/*smcpcFmea_act_init
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcpcFmea_act_init(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;

    rec->cpcFmea = (void *)&cpcFmeaA;
    //TODO

    rec->next = smcpcFmea_sta_default;
}

/*smcpcFmea_act_sta1
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcpcFmea_act_sta1(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;
    //((hcpcFmea)(rec->cpcFmea))->
    //TODO

    rec->next = smcpcFmea_sta_default;
}

/*smcpcFmea_act_sta2
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcpcFmea_act_sta2(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;
    //((hcpcFmea)(rec->cpcFmea))->
    //TODO

    rec->next = smcpcFmea_sta_default;
}

/*smcpcFmea_act_default
* ����: hStaRec ״̬��¼�ṹ��ָ��
* ���: ��
***********************************************/
void smcpcFmea_act_default(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;
    //((hcpcFmea)(rec->cpcFmea))->
    //TODO

    rec->next = smcpcFmea_sta_default;
}


/***********************************************************
* �������
***********************************************************/
/*������ʼ������
* ����: cthis cpcFmea��ָ��
* ���: hcpcFmea cthis/OOPC_NULL
***********************************************/
hcpcFmea cpcFmea_init(hcpcFmea cthis, hstaAct smcpcFmea, hvfbOcpcFmea vfbOcpcFmea,
        void *listBuffer, int16 listBuffSize, int16 fifoObjSize){
    // ���ܺ�������
    CCC(fifo, &cthis->smcpcFmeaRec.errFifo, listBuffer, listBuffSize, fifoObjSize);
    if(OPRS(*cthis->fifo) == OOPC_NULL){
        return OOPC_NULL;
    }
    //TODO

    // ��������
    cthis->smcpcFmea = smcpcFmea;
    cthis->vfbOcpcFmea = vfbOcpcFmea;
    //TODO

    return cthis;
}

/*������к���
* ����: t cpcFmea��ָ��
* ���: ��
***********************************************/
void cpcFmea_run(hcpcFmea t){
    SMRE(t->smcpcFmea, t->smcpcFmeaRec);
}

/*cpcFmea_save
* ����: t cpcFmea��ָ��
* ���: ��
***********************************************/
void cpcFmea_save(hcpcFmea t, herrCode code){
    t->fifo->push(t->fifo, code);
}

/*��������������
* ����: t cpcFmea��ָ��
* ���: ��
***********************************************/
//void cpcFmea_err(hcpcFmea t, herrCode code){
//    t->vfbOcpcFmea->err(t->vfbOcpcFmea, code);
//}

/*����๹�캯��
* ����: cthis cpcFmea��ָ��
* ���: hcpcFmea cthis/OOPC_NULL
***********************************************/
CC(cpcFmea){
    // ���ܺ�������
    cthis->init = cpcFmea_init;
    cthis->run = cpcFmea_run;
    //cthis->err = cpcFmea_err;
    //TODO

    // ��������
    cthis->smcpcFmeaRec.next = smcpcFmea_sta_init;

    //TODO

    return cthis;
}
/*�������������
* ����: cthis cpcFmea��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(cpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* ����첽���ȹ��ܺ���
***********************************************************/
/*�첽���ȹ��ܺ���
***********************************************/
//void cpcFmea_abi_example(void){
    //TODO
//}


/***********************************************************
* ���ʵ����
***********************************************************/
/*�����ʵ��
***********************************************/
cpcFmea cpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
