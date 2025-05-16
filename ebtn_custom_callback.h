/** ***************************************************************************
 * @File Name: ebtn_custom_callback.h
 * @brief 自定义按键状态检测和事件处理函数
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.0.0
 * @Creat Date : 2025-05-16
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 * @Modifi Date :
 */
#ifndef EBTN_CUSTOM_CALLBACK_H
#define EBTN_CUSTOM_CALLBACK_H

#include "ebtn_app.h"
#include "ebtn_custom_hal.h"
#include "ebtn_custom_config.h"

/* -------------------------- 此处添加所需的按键触发事件的函数声明的头文件 ------------------------- */

/* -------------------------------- 自定义配置部分结束 ------------------------------- */

uint8_t ebtn_Get_State(struct ebtn_btn *btn);
void ebtn_Event_Handler(struct ebtn_btn *btn, ebtn_evt_t evt);

#endif
