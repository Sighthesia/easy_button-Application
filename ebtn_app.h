/** ***************************************************************************
 * @File Name: ebtn_app.c
 * @brief 基于easy_button库的应用层基础实现，提供最主要的静态按键支持
 * 带“APP”的函数为可外部调用的应用函数，其中重要函数有：
 * ebtn_APP_Key_INIT()：初始化函数，ebtn_APP_Key_Process()：处理函数
 * @note 为了实现多平台适配，本应用层的实现注入了硬件抽象回调函数，需要依赖其他文件一同使用
 * @ref ebtn_custom_hal.c/h
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.2.0
 * @Creat Date : 2025-03-01
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes : 添加回调函数机制，降低各层级耦合度，从而实现多平台适配
 * @Modifi Date : 2025-05-06
 */
#ifndef EBTN_APP_H
#define EBTN_APP_H

#include "ebtn.h"
#include "ebtn_app.h"
#include "ebtn_custom_callback.h"
#include "ebtn_custom_hal.h"
#include "ebtn_custom_config.h"

void ebtn_APP_Key_INIT(void);
void ebtn_APP_Key_Process(void);

uint8_t ebtn_APP_Is_Key_Active(uint16_t key_id);
uint8_t ebtn_APP_Is_Any_Key_In_Process(void);
uint8_t ebtn_APP_Get_Key_State(uint16_t key_id);

#endif /* EBTN_APP_H */