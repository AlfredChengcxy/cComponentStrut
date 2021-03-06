/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcsLedServ.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 22:42:51
* @brief        :组件csLedServ 管理类数据类型声明
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#ifndef VFBMCSLEDSERV_H_
#define VFBMCSLEDSERV_H_

#include "../../01_std/std.h"
#include "../../06_cas/casSch/casSch.h"
#include "../../09_cpc/cpcFmea/cpcFmea.h"
#include "../../07_cs/csLedServ/csLedServ.h"
#include "../vfbMCfg.h"

/***********************************************************
* 组件管理初始化
***********************************************************/
/*组件管理初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbMcsLedServInit(void);


/***********************************************************
* 组件管理类定义
***********************************************************/
/*组件管理类声明
***********************************************/
CL(vfbMcsLedServ){
    hvfbMcsLedServ self;
    hvfbMcsLedServ (*init)(hvfbMcsLedServ cthis, hvfbOcsLedServ vfbOcsLedServ,
            hvfbIcasSch vfbIcasSch, hvfbIcpcFmea vfbIcpcFmea);

    // 组件管理参数
    //TODO

    // 组件管理功能函数
    //void (*func)(hvfbMcsLedServ t);
    //TODO

    // 注入组件输出类及其他功能类
    INJ(vfbOcsLedServ, vfbOcsLedServ);
    INJ(vfbIcasSch, vfbIcasSch);
    INJ(vfbIcpcFmea, vfbIcpcFmea);
};

/*组件输出类接口声明
* 命名方式: 存放类+实际类+实际类功能
***********************************************/
void vfbMcsLedServ_vfbOcsLedServ_err(hvfbOcsLedServ t, herrCode code);
//void vfbMcsLedServ_vfbOcsLedServ_output(hvfbOcsLedServ t);

/*组件管理类实例
***********************************************/
extern vfbMcsLedServ vfbMcsLedServA;


#endif /* VFBMCSLEDSERV_H_ */

/**************************** Copyright(C) pxf ****************************/
