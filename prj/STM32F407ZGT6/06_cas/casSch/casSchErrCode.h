/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :casSchErrCode.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :���casSch �ڲ�����ɲ��ִ����붨��ͷ�ļ�
* @others       :
* @history      :180831 pxf ���ν���
***************************************************************************/

#ifndef CASSCHERRCODE_H_
#define CASSCHERRCODE_H_

/*errClassify
************************************************************
* #define EC_EC_cie      0 // communicationInputErr   ͨ���������
* #define EC_EC_coe      1 // communicationOutputErr  ͨ���������
* #define EC_EC_se       2 // schedularErr            ������ȴ���
* #define EC_EC_fe       3 // functionErr             ���ܴ���
***********************************************************/

/*errRanking
************************************************************
* #define EC_ER_ignore   0 // ignore   �ɺ���
* #define EC_ER_warning  1 // warning  ����
* #define EC_ER_serious  2 // serious  ���ش���
* #define EC_ER_fatal    3 // fatal    ��������
***********************************************************/

/*errDefine
************************************************************************************************************************
*                                | casSchPartId |   errCode  |  errClassify  |  errRanking     |
***********************************************************************************************************************/
#define casSch_addTask_pi          0                                                           // �������
#define casSch_addTask_id_outOfRange                0        // EC_EC_se        EC_ER_warning  // id������Χ
#define casSch_addTask_task_exist                   1        // EC_EC_se        EC_ER_warning  // �����Ѵ���
/**********************************************************************************************************************/
#define casSch_delTask_pi          1                                                           // ɾ������
#define casSch_delTask_id_outOfRange                0        // EC_EC_se        EC_ER_warning  // ɾ������ʧ��
#define casSch_delTask_task_null                    1        // EC_EC_se        EC_ER_warning  // ���񲻴���
#define casSch_delTask_task_false                   2        // EC_EC_se        EC_ER_warning  // ��Ŀ������
/**********************************************************************************************************************/
#define casSch_taskExecute_pi      2                                                           // �������
#define casSch_taskExecute_task_delay               0        // EC_EC_se        EC_ER_warning  // ����ִ���ӳ�
#define casSch_taskExecute_task_miss                1        // EC_EC_se        EC_ER_serious  // ����ִ�ж�ʧ
/**********************************************************************************************************************/
#define casSch_smcasSch_pi         3                                                           // ����״̬��
#define casSch_smcasSch_sta_default                 0        // EC_EC_se        EC_ER_serious  // ״̬���쳣����Ĭ��״̬
/**********************************************************************************************************************/

#endif /* CASSCHERRCODE_H_ */

/**************************** Copyright(C) pxf ****************************/
