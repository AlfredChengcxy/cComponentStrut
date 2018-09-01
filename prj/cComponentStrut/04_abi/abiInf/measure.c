/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :measure.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 16:25:01
* @brief        :�����ӿڳ����ඨ��
* @others       :
* @history      :180901 pxf ���ν���
***************************************************************************/

#include "..\abi.h"

/***********************************************************
* �����ӿڳ����ඨ��
***********************************************************/
/*�����ӿڳ������ʼ������
* ����: cthis measure��ָ��
* ���: hmeasure cthis/OOPC_NULL
***********************************************/
hmeasure measure_init(hmeasure cthis, void (*start)(uint32 *point), uint32 (*end)(uint32 point))
{
    cthis->iMeasure.start = start;
    cthis->iMeasure.end = end;

    return cthis;
}

/*�����ӿڳ����๹�캯��
* ����: cthis measuer��ָ��
* ���: hmeasure cthis/OOPC_NULL
***********************************************/
CC(measure)
{
    cthis->init = measure_init;
    return cthis;
}
/*�����ӿڳ�������������
* ����: cthis measure��ָ��
* ���: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(measure)
{
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
