/** ***************************************************************************
 * @File Name: ebtn_APP_Event.h
 * @brief 自定义按键状态检测和事件处理函数
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.3.0
 * @Creat Date : 2025-05-16
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 *   - 优化按键状态检测说明，强调查表法配合 Keys_Config 使用
 *   - 添加事件分发示例结构，鼓励解耦与函数化处理
 *   - 头文件减少传递包含，使用前向声明；实现文件包含 `ebtn_APP_HAL.h` 获取平台定义
 *   - 注释统一与开源风格对齐
 * @Modifi Date : 2025-09-14
 */
#ifndef EBTN_CUSTOM_CALLBACK_H
#define EBTN_CUSTOM_CALLBACK_H

#include "ebtn.h"

struct ebtn_btn;

#ifdef __cplusplus
extern "C"
{
#endif

    uint8_t Get_Key_State(struct ebtn_btn *btn);
    void ebtn_APP_Event(struct ebtn_btn *btn, ebtn_evt_t evt);

#ifdef __cplusplus
}
#endif

#endif /* EBTN_CUSTOM_CALLBACK_H */
