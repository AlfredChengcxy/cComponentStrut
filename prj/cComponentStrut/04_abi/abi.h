/*
 * abi.h
 *
 *  Created on: 2018��8��17��
 *      Author: pxf
 */

#ifndef ABI_H_
#define ABI_H_

// �����ӿڽ��з���
#include "..\01_std\std.h"

#include "inf.h"

#include ".\abiInf\isr.h"
#include ".\abiInf\measure.h"

#include ".\abiInf\gi.h"
#include ".\abiInf\go.h"


// �߳������ӿ�
extern isr timer;
extern isr mainLoop;

// ʱ����������ӿ�
extern measure time;

// ���������ӿ�
extern gi err;

// ��������ӿ�
extern go led;




// ����ӿڽ��г�ʼ��
void abiInit(void);

#endif /* ABI_H_ */
