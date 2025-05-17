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
#include "ebtn_app.h"

/* -------------------------------- 初始化和处理函数 -------------------------------- */

/** ***************************************************************************
 * @brief easy_button初始化,在主函数中调用
 * @note  如果使用组合键，则需要在ebtn_init之后调用ebtn_combo_btn_add_btn添加组合键
 */
void ebtn_APP_Key_INIT(void)
{
    // 初始化easy_button库
    ebtn_init(btn_array, btn_array_size,
              btn_combo_array, btn_combo_array_size,
              ebtn_Get_State, ebtn_Event_Handler);

    /* ---------------------------- 此处向组合键结构体数组静态添加按键 --------------------------- */
    // 结构体数组索引值与ebtn_custom_config.c中组合键结构体数组btn_combo_array中的索引值一致
    // 示例：四个组合键
    // 为组合键1添加按键KEY_1和KEY_2
    // ebtn_combo_btn_add_btn(&btn_combo_array[0], KEY_1);
    // ebtn_combo_btn_add_btn(&btn_combo_array[0], KEY_2);

    // // 为组合键2添加按键KEY_3和KEY_4
    // ebtn_combo_btn_add_btn(&btn_combo_array[1], KEY_3);
    // ebtn_combo_btn_add_btn(&btn_combo_array[1], KEY_4);

    // // 为组合键3添加按键KEY_1和KEY_3
    // ebtn_combo_btn_add_btn(&btn_combo_array[2], KEY_1);
    // ebtn_combo_btn_add_btn(&btn_combo_array[2], KEY_3);

    // // 为组合键4添加按键KEY_2和KEY_4
    // ebtn_combo_btn_add_btn(&btn_combo_array[3], KEY_2);
    // ebtn_combo_btn_add_btn(&btn_combo_array[3], KEY_4);
}

/* --------------------------------- 自定义配置部分结束 -------------------------------- */

/** ***************************************************************************
 * @brief 处理按键事件，需要定期调用，建议以20ms为周期执行一次
 * @note  Tick时基为1ms
 */
void ebtn_APP_Key_Process(void)
{
    ebtn_process(ebtn_custom_hal.Get_Tick()); // 获取时间处理按键事件
}

/* -------------------------------- 辅助部分 ------------------------------- */

/** ***************************************************************************
 * @brief  检查按键是否激活
 * @param  key_id: 按键ID
 * @return uint8_t: 1-激活，0-未激活
 */
uint8_t ebtn_APP_Is_Key_Active(uint16_t key_id)
{
    ebtn_btn_t *btn = ebtn_get_btn_by_key_id(key_id);
    return ebtn_is_btn_active(btn);
}

/** ***************************************************************************
 * @brief  检查是否有按键处于处理中
 * @return uint8_t: 1-有按键处理中，0-无按键处理中
 */
uint8_t ebtn_APP_Is_Any_Key_In_Process(void)
{
    return ebtn_is_in_process();
}

/** ***************************************************************************
 * @brief  获取指定按键的按键状态
 * @param  key_id: 按键ID
 * @return uint8_t: 1-按下，0-松开
 */
uint8_t ebtn_APP_Get_Key_State(uint16_t key_id)
{
    ebtn_btn_t *btn = ebtn_get_btn_by_key_id(key_id);
    if (btn == NULL)
    {
        return 0;
    }
    return ebtn_Get_State(btn);
}
