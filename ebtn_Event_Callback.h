/** ***************************************************************************
 * @File Name: ebtn_Event_Callback.h
 * @brief 自定义按键状态检测和事件处理函数
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.0.0
 * @Creat Date : 2025-05-16
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 *   - 优化按键状态检测说明，强调查表法配合 Keys_Config 使用
 *   - 添加事件分发示例结构，鼓励解耦与函数化处理
 *   - 注释统一与开源风格对齐
 * @Modifi Date : 2025-09-14
 */
#ifndef EBTN_CUSTOM_CALLBACK_H
#define EBTN_CUSTOM_CALLBACK_H

#include "ebtn_APP.h"

/* -------------------------- 此处添加所需的按键触发事件的函数声明的头文件 ------------------------- */

/* -------------------------------- 自定义配置部分结束 ------------------------------- */

#ifdef __cplusplus
extern "C"
{
#endif

    uint8_t Get_Key_State(struct ebtn_btn *btn);
    void ebtn_Event_Callback(struct ebtn_btn *btn, ebtn_evt_t evt);

#ifdef __cplusplus
}
#endif

#endif /* EBTN_CUSTOM_CALLBACK_H */
