/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :errCode.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 14:40:50
* @brief        :�������ͻ�׼���ݶ���
* @others       :
* @history      :180901 pxf ���ν���
***************************************************************************/

#ifndef ERRCODE_H_
#define ERRCODE_H_

/*ͨ�ô�����
***********************************************/
typedef struct{
    void *id;                     // �����ʵ����ʱʵ��
    struct
    {
        uint32 cpnPartId    :8;   // �������ʱΪ��������ID��������
        uint32 errClassify  :4;   // ͨ��ֻ��4������
        uint32 errRanking   :4;   // ͨ��ֻ��4��ȼ�
        uint32 errCode      :16;  // ������ID�¶�Ӧ�ĸ������ʵ�ʽ�������
    };
} errCode, *herrCode;

/*errClassify
***********************************************************/
#define EC_EC_cie      0 // communicationInputErr   ͨ���������
#define EC_EC_coe      1 // communicationOutputErr  ͨ���������
#define EC_EC_se       2 // schedularErr            ������ȴ���
#define EC_EC_fe       3 // functionErr             ���ܴ���
/**********************************************************/

/*errRanking
***********************************************************/
#define EC_ER_ignore   0 // ignore   �ɺ���
#define EC_ER_warning  1 // warning  ����
#define EC_ER_serious  2 // serious  ���ش���
#define EC_ER_fatal    3 // fatal    ��������
/**********************************************************/

/*errCode
***********************************************************/
#define EC32(cpnPartId, errClassify, errRanking, errCode)       (((cpnPartId) << 24) | ((errClassify) << 20) | ((errRanking) << 16) | (errRanking))
#define EC_PID(errcode)                                         (((errcode) & 0xFF000000) >> 24)
#define EC_ECF(errcode)                                         (((errcode) & 0x00F00000) >> 20)
#define EC_ERK(errcode)                                         (((errcode) & 0x000F0000) >> 16)
#define EC_EC(errcode)                                          (((errcode) & 0x0000FFFF) >> 0)

#endif /* ERRCODE_H_ */

/**************************** Copyright(C) pxf ****************************/
