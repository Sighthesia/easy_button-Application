/** ***************************************************************************
 * @File Name: ebtn_custom_callback.h
 * @brief 自定义按键状态获取和事件处理函数
 * @Author : Sighthesia
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

uint8_t ebtn_Get_State(struct ebtn_btn *btn);
void ebtn_Event_Handler(struct ebtn_btn *btn, ebtn_evt_t evt);

#endif
