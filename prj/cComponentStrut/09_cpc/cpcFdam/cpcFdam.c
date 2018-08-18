/*
 * cpcFdam.c
 *
 *  Created on: 2018��8��18��
 *      Author: pxf
 */

#include "cpcFdam.h"

// --------------------------------------------------------------
// �����ʼ��
// --------------------------------------------------------------
// �����ʼ��------------------------
int16 cpcFdamInit(void)
{
    int16 rtv = 0;

    CN(cpcFdam, &cpcFdamA, &vfbOcpcFdamA,
            &errCodeFifo, errCodeBuff, sizeof(errCodeBuff), sizeof(errCode));
    if (OPRS(cpcFdamA) != OOPC_NULL)
    {
        rtv = vfbOcpcFdamInit();
    }
    else
    {
        rtv = -1;
    }

    return rtv;
}

// --------------------------------------------------------------
// �������
// --------------------------------------------------------------
// ������е���--------------------------
void cpcFdamSch(void)
{
    cpcFdamA.run(cpcFdamA.self);
}



// --------------------------------------------------------------
// ͨ�ù��ܺ���
// --------------------------------------------------------------


// --------------------------------------------------------------
// ������״̬������
// --------------------------------------------------------------
void errDisposeSm_act_init(void *hStaRec)
{
    herrDisposeSmRec rec = (herrDisposeSmRec)hStaRec;

    rec->cpcFdam = (void *)&cpcFdamA;
    rec->next = errDisposeSm_sta_polling;
}
void errDisposeSm_act_polling(void *hStaRec)
{
    herrDisposeSmRec rec = (herrDisposeSmRec)hStaRec;

    if (((hcpcFdam)rec->cpcFdam)->fifo->currLen != 0)
    {
        rec->next = errDisposeSm_sta_dispose;
    }
    else
    {
        rec->next = errDisposeSm_sta_polling;
    }
}
void errDisposeSm_act_dispose(void *hStaRec)
{
    herrDisposeSmRec rec = (herrDisposeSmRec)hStaRec;
    errCode code;

    while (((hcpcFdam)rec->cpcFdam)->fifo->currLen != 0)
    {
        ((hcpcFdam)rec->cpcFdam)->fifo->pop(((hcpcFdam)rec->cpcFdam)->fifo, &code);
        ((hcpcFdam)rec->cpcFdam)->errCnt++;

        // ���¸�����ȼ�����
        if (code.errRanking == EC_ER_ignore)
        {
            ((hcpcFdam)rec->cpcFdam)->errIgnoreCnt++;
        }
        else if (code.errRanking == EC_ER_warning)
        {
            ((hcpcFdam)rec->cpcFdam)->errWarningCnt++;
        }
        else if (code.errRanking == EC_ER_serious)
        {
            ((hcpcFdam)rec->cpcFdam)->errSeriousCnt++;
        }
        else if (code.errRanking == EC_ER_fatal)
        {
            ((hcpcFdam)rec->cpcFdam)->errFatalCnt++;
        }
        else
        {
            ;
        }

        // ���¸�����������
        if (code.errClassify == EC_EC_cie)
        {
            ((hcpcFdam)rec->cpcFdam)->errCieCnt++;
        }
        else if (code.errClassify == EC_EC_coe)
        {
            ((hcpcFdam)rec->cpcFdam)->errCoeCnt++;
        }
        else if (code.errClassify == EC_EC_se)
        {
            ((hcpcFdam)rec->cpcFdam)->errSeCnt++;
        }
        else if (code.errClassify == EC_EC_fe)
        {
            ((hcpcFdam)rec->cpcFdam)->errFeCnt++;
        }
        else
        {
            ;
        }
    }

    // ���ز�ѯ״̬
    rec->next = errDisposeSm_sta_polling;
}
void errDisposeSm_act_default(void *hStaRec)
{
    herrDisposeSmRec rec = (herrDisposeSmRec)hStaRec;

    rec->next = errDisposeSm_sta_polling;
}

// --------------------------------------------------------------
// ����ඨ��
// --------------------------------------------------------------
errCode errCodeBuff[ERR_FIFO_LEN];
fifo errCodeFifo;

hcpcFdam cpcFdam_init(hcpcFdam cthis, hvfbOcpcFdam vfbOcpcFdam,
        hfifo errCodeFifo, void *listBuffer, int16 listBuffSize, int16 fifoObjSize)
{
    cthis->vfbOcpcFdam = vfbOcpcFdam;

    CCC(fifo, errCodeFifo, listBuffer, listBuffSize, fifoObjSize);
    if (OPRS(*errCodeFifo) == OOPC_NULL)
    {
        return OOPC_NULL;
    }
    cthis->fifo = errCodeFifo;

    return cthis;
}

void cpcFdam_saveErrCode(hcpcFdam t, herrCode code)
{
    t->fifo->push(t->fifo, code);
}
//void cpcFdam_getErrCode(hcpcFdam t, herrCode code)
//{
//    t->fifo->fout(t->fifo, code);
//}
void cpcFdam_run(hcpcFdam t)
{
    t->errDisposeSm[t->errDisposeSmRec.next](&t->errDisposeSmRec);
}

CC(cpcFdam)
{
    cthis->init = cpcFdam_init;
    cthis->saveErrCode = cpcFdam_saveErrCode;
//    cthis->getErrCode = cpcFdam_getErrCode;
    cthis->run = cpcFdam_run;

    cthis->errCnt = 0;
    cthis->errIgnoreCnt = 0;
    cthis->errWarningCnt = 0;
    cthis->errSeriousCnt = 0;
    cthis->errFatalCnt = 0;

    cthis->errCieCnt = 0;
    cthis->errCoeCnt = 0;
    cthis->errSeCnt = 0;
    cthis->errFeCnt = 0;

    cthis->errDisposeSmRec.next = errDisposeSm_sta_init;
    cthis->errDisposeSm[errDisposeSm_sta_init] = errDisposeSm_act_init;
    cthis->errDisposeSm[errDisposeSm_sta_polling] = errDisposeSm_act_polling;
    cthis->errDisposeSm[errDisposeSm_sta_dispose] = errDisposeSm_act_dispose;
    cthis->errDisposeSm[errDisposeSm_sta_default] = errDisposeSm_act_default;

    return cthis;
}
CD(cpcFdam)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// �첽���ȹ��ܺ���
// --------------------------------------------------------------


// --------------------------------------------------------------
// �����ʵ����
// --------------------------------------------------------------
cpcFdam cpcFdamA;
