/** ***************************************************************************
 * @File Name: ebtn_app.c
 * @brief 基于easy_button库的事件回调按键处理应用层实现
 * 在此处修改按键触发事件
 * @note 为了实现多平台适配，本应用层的实现注入了硬件抽象相关回调函数ebtn_custom_config。同时需要依赖配置文件ebtn_Custom_Config.c/h
 * @note 由于直接使用了事件回调进行按键检测，层级间仍然存在一定耦合，按键触发事件仍需在此应用层文件实现
 * @ref ebtn_custom_hal.c/h
 * @credit : bowenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia
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

uint8_t ebtn_APP_Is_Key_Active(uint16_t key_id);
uint8_t ebtn_APP_Is_Any_Key_In_Process(void);
uint8_t ebtn_APP_Get_Key_State(uint16_t key_id);

#endif /* EBTN_APP_H */