/** ***************************************************************************
 * @File Name: ebtn_app.c
 * @brief 基于easy_button库的事件回调按键处理应用层实现
 * 在此处修改按键触发事件
 * @note 为了实现多平台适配，本应用层的实现注入了硬件抽象相关回调函数ebtn_customebtn_custom_config。同时需要依赖配置文件ebtn_Custom_Config.c/h
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
#include "ebtn_app.h"

/* -------------------------------- 初始化和处理函数 -------------------------------- */

/** ***************************************************************************
 * @brief easy_button初始化
 * @note  在主函数中调用
 */
void ebtn_APP_Key_INIT(void)
{
    // 初始化easy_button库
    ebtn_init(btn_array, btn_array_size,
              btn_combo_array, btn_combo_array_size,
              ebtn_Get_State, ebtn_Event_Handler);

    /* ---------------------------- 此处向组合键结构体数组静态添加按键 --------------------------- */
    // 结构体数组索引位与配置中组合键结构体数组中对应的组合键ID枚举值一致
    ebtn_combo_btn_add_btn(&btn_combo_array[0], KEY_1);
    ebtn_combo_btn_add_btn(&btn_combo_array[0], KEY_2);

    ebtn_combo_btn_add_btn(&btn_combo_array[1], KEY_3);
    ebtn_combo_btn_add_btn(&btn_combo_array[1], KEY_4);

    ebtn_combo_btn_add_btn(&btn_combo_array[2], KEY_1);
    ebtn_combo_btn_add_btn(&btn_combo_array[2], KEY_3);

    ebtn_combo_btn_add_btn(&btn_combo_array[3], KEY_2);
    ebtn_combo_btn_add_btn(&btn_combo_array[3], KEY_4);
}

/* --------------------------------- 自定义配置部分结束 -------------------------------- */

/** ***************************************************************************
 * @brief  处理按键事件
 * @note  定期调用，建议以20ms为周期
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
