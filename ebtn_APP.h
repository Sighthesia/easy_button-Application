/** ***************************************************************************
 * @File Name: ebtn_app.c
 * @brief 基于easy_button库的应用层基础实现，提供最主要的静态按键支持
 * 带“APP”的函数为可外部调用的应用函数，其中重要函数有：
 * ebtn_APP_Keys_Init()：初始化函数，ebtn_APP_Process()：处理函数
 * @note 为了实现多平台适配，本应用层的实现注入了硬件抽象回调函数，需要依赖其他文件一同使用
 * @ref ebtn_HAL_Config.c/h
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.2.0
 * @Creat Date : 2025-03-01
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 *   - 梳理应用层接口与调用流程（Init/Process），注释精简
 *   - 明确依赖：Keys_Config、HAL_Config、Event_Callback 三者注入
 *   - 保持 API 不变，增强可读性与可维护性
 * @Modifi Date : 2025-09-14
 */
#ifndef EBTN_APP_H
#define EBTN_APP_H

#include "ebtn.h"
#include "ebtn_Keys_Config.h"
#include "ebtn_Event_Callback.h"
#include "ebtn_HAL_Config.h"

void ebtn_APP_Keys_Init(void);
void ebtn_APP_Process(void);

#endif /* EBTN_APP_H */