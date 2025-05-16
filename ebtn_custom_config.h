/** ***************************************************************************
 * @File Name: ebtn_custom_config.h
 * @brief 自定义按键参数配置文件
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.0.0
 * @Creat Date : 2025-05-10
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 * @Modifi Date :
 */
#ifndef EBTN_CUSTOM_CONFIG_H
#define EBTN_CUSTOM_CONFIG_H

#include "ebtn.h"
#include "ebtn_custom_hal.h"

/* -------------------------------- 此处修改按键参数定义 -------------------------------- */

#define DEBOUNCE_TIME 20             // 防抖处理，按下防抖超时，配置为0，代表不启用
#define RELEASE_DEBOUNCE_TIME 20     // 防抖处理，松开防抖超时，配置为0，代表不启用
#define CLICK_AND_PRESS_MIN_TIME 20  // 按键超时处理，触发最短时间，小于该时间则不触发Click和Press，配置为0，代表不检查最小值。用于防误触
#define CLICK_AND_PRESS_MAX_TIME 200 // 按键超时处理，短按最长时间，配置为0xFFFF，代表不检查最大值。用于区分长按和短按事件，大于该时间则不触发Click而触发Press
#define MULTI_CLICK_MAX_TIME 200     // 多击处理超时结算，两个按键之间的时间是连击的超时时间(ms)
#define KEEPALIVE_TIME_PERIOD 600    // 长按处理，长按周期，每个周期增加keepalive_cnt计数(ms)
#define MAX_CLICK_COUNT 3            // 最大连续短击次数，配置为0，代表不进行连击检查

/* -------------------------------- 此处修改按键ID定义 -------------------------------- */

/** ***************************************************************************
 * @brief 按键ID枚举
 * @note 此处定义按键ID
 */
typedef enum
{
    // 示例：4个按键和四个组合键，包含最大按键，用于提供按键数量
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    MAX_KEY, // 最大按键，用于提供按键数量
    COMBO_KEY_1,
    COMBO_KEY_2,
    COMBO_KEY_3,
    COMBO_KEY_4,
    MAX_COMBO_KEY // 最大组合键，用于提供组合键数量
} ebtn_custom_config_key_enum_t;

/* ---------------------------------- 自定义配置部分结束 ---------------------------------- */

/** ***************************************************************************
 * @brief 自定义按键配置结构体宏定义
 */
typedef struct
{
    uint16_t key_id;         // 按键按键ID
    GPIO_TypeDef *gpio_port; // GPIO端口
    uint16_t gpio_pin;       // GPIO引脚
    uint8_t active_level;    // 有效电平(0=低电平有效，1=高电平有效)
} ebtn_custom_config_key_list_t;

extern ebtn_custom_config_key_list_t key_list[]; // 按键配置数组
extern ebtn_btn_t btn_array[];                   // 按键结构体数组
extern ebtn_btn_combo_t btn_combo_array[];       // 组合键结构体数组

extern const uint8_t btn_array_size;       // 按键结构体数组大小
extern const uint8_t btn_combo_array_size; // 组合键结构体数组大小
extern const uint8_t key_list_size;        // 按键配置数组大小

#endif /* EBTN_CUSTOM_CONFIG_H */