/** ***************************************************************************
 * @File Name: ebtn_Keys_Config.h
 * @brief 自定义按键参数配置文件
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.0.0
 * @Creat Date : 2025-05-10
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 *   - 统一命名：`MAX_KEY` → `KEYS_COUNT`，结构体/数组命名更语义化
 *   - 修正组合键数组大小：引入 `COMBO_KEYS_COUNT=(MAX_COMBO_KEY-COMBO_KEY_BASE)`
 *   - 增加类型安全的内联转换函数：`combo_id_to_index` / `index_to_combo_id`
 *   - 注释精简与开源风格统一，强调配置思路与用法
 * @Modifi Date : 2025-09-14
 */
#ifndef EBTN_KEYS_CONFIG_H
#define EBTN_KEYS_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ebtn_HAL_Config.h"

/* ------------------------------- 此处修改按键参数定义 ------------------------------- */

// 统一单位: ms；特殊值说明：0=不启用，0xFFFF=不限制上限（按库语义）
#define DEBOUNCE_TIME 20             // 防抖：按下防抖超时
#define RELEASE_DEBOUNCE_TIME 20     // 防抖：松开防抖超时
#define CLICK_AND_PRESS_MIN_TIME 20  // 触发最短时间（小于该值不触发 Click/Press）
#define CLICK_AND_PRESS_MAX_TIME 200 // 短按最长时间（超过则触发 Press；0xFFFF=不检查最大值）
#define MULTI_CLICK_MAX_TIME 200     // 连击间隔超时（两个按键之间的最大间隔）
#define KEEPALIVE_TIME_PERIOD 600    // 长按周期（每周期增加 keepalive_cnt）
#define MAX_CLICK_COUNT 3            // 最大连续短击次数（0=不检查连击）

    /* -------------------------------- 此处修改按键ID定义 -------------------------------- */

    /** ***************************************************************************
     * @brief 按键ID枚举
     */
    typedef enum
    {
        KEY_1 = 0,
        KEY_2,
        KEY_3,
        KEY_4,
        // 更多按键......
        KEYS_COUNT // 最大按键，用于提供按键数量
    } key_enum_t;

#define COMBO_KEY_BASE 100 // 组合键ID基值，根据实际按键数量调整，避免与单键 ID 空间重叠

    /** ***************************************************************************
     * @brief 组合键ID枚举
     */
    typedef enum
    {
        COMBO_KEY_1 = COMBO_KEY_BASE, // 组合键基值，避免与单键 ID 空间重叠
        COMBO_KEY_2,
        COMBO_KEY_3,
        COMBO_KEY_4,
        // 更多组合键......
        MAX_COMBO_KEY // 最大组合键，用于提供组合键数量
    } combo_key_enum_t;

    /* ---------------------------------- 自定义配置部分结束 ---------------------------------- */

    /** ***************************************************************************
     * @brief 自定义按键配置结构体宏定义
     */
    typedef struct
    {
        key_enum_t key_id;       // 按键按键ID
        GPIO_TypeDef *gpio_port; // GPIO端口
        uint16_t gpio_pin;       // GPIO引脚
        uint8_t active_level;    // 有效电平(EBTN_ACTIVE_LOW=低电平有效，EBTN_ACTIVE_HIGH=高电平有效)
    } key_config_t;

    /** ***************************************************************************
     * @brief 组合键配置结构体
     */
    typedef struct
    {
        combo_key_enum_t combo_key_id; // 组合键ID
        uint8_t key_count;             // 组合键包含的按键数量
        const uint8_t *keys;           // 按键数组指针，支持自适应长度
    } combo_config_t;

    /* -------------------------------- 查表配置结构体 -------------------------------- */

    /** ***************************************************************************
     * @brief 按键配置表项结构体
     */
    typedef struct
    {
        key_enum_t key_id;        // 按键ID
        ebtn_btn_param_t *params; // 按键参数指针
    } special_key_list_t;

    /** ***************************************************************************
     * @brief 组合键配置表项结构体
     */
    typedef struct
    {
        combo_key_enum_t combo_key_id; // 组合键ID
        ebtn_btn_param_t *params;      // 组合键参数指针
    } special_combo_key_list_t;

/* -------------------------------- 配置表辅助宏定义 -------------------------------- */

/** ***************************************************************************
 * @brief 按键特殊参数配置宏
 * @note 用于配置需要特殊参数的按键
 */
#define KEY_SPECIAL_CONFIG(key_id, params) {key_id, &params}

/** ***************************************************************************
 * @brief 组合键特殊参数配置宏
 * @note 用于配置需要特殊参数的组合键
 */
#define COMBO_SPECIAL_CONFIG(combo_key_id, params) {combo_key_id, &params}

/** ***************************************************************************
 * @brief 通用可变参数宏，支持任意数量按键
 */
#define COMBO_KEYS(combo_id, ...)                                                                       \
    {                                                                                                   \
        combo_id, sizeof((uint8_t[]){__VA_ARGS__}) / sizeof(uint8_t), (const uint8_t[]) { __VA_ARGS__ } \
    }

    /* ------------------------------ 组合键数量计算 ------------------------------ */

#define COMBO_KEYS_COUNT (MAX_COMBO_KEY - COMBO_KEY_BASE) // 实际组合键数量

    /*------------------------------ 语义化有效电平定义 ------------------------------ */

#define EBTN_ACTIVE_LOW 0u  // 低电平有效
#define EBTN_ACTIVE_HIGH 1u // 高电平有效

    extern key_config_t keys_config_list[];    // 按键硬件配置数组
    extern ebtn_btn_t btn_array[];             // 按键结构体数组
    extern ebtn_btn_combo_t btn_combo_array[]; // 组合键结构体数组

    extern const combo_config_t combo_keys_config_list[];            // 组合键配置表
    extern const special_key_list_t special_keys_list[];             // 按键配置表
    extern const special_combo_key_list_t special_combo_keys_list[]; // 组合键配置表

    extern const uint8_t btn_array_size;               // 按键结构体数组大小
    extern const uint8_t btn_combo_array_size;         // 组合键结构体数组大小
    extern const uint8_t keys_list_size;               // 按键配置数组大小
    extern const uint8_t combo_config_list_size;       // 组合键配置表大小
    extern const uint8_t special_key_config_list_size; // 按键特殊参数配置表大小
    extern const uint8_t special_combo_key_list_size;  // 组合键特殊参数配置表大小

    // 添加组合键索引转换函数声明
    static inline uint8_t combo_id_to_index(combo_key_enum_t combo_id);
    static inline combo_key_enum_t index_to_combo_id(uint8_t index);
    extern ebtn_btn_param_t buttons_parameters; // 默认按键参数

#ifdef __cplusplus
}
#endif

/* ------------------------------ 内联函数实现 ------------------------------ */
// 组合键 ID 到数组索引的转换
static inline uint8_t combo_id_to_index(combo_key_enum_t combo_id)
{
    return (uint8_t)(combo_id - COMBO_KEY_BASE);
}

// 数组索引到组合键 ID 的转换
static inline combo_key_enum_t index_to_combo_id(uint8_t index)
{
    return (combo_key_enum_t)(index + COMBO_KEY_BASE);
}

#endif /* EBTN_KEYS_CONFIG_H */