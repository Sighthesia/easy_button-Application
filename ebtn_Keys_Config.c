/** ***************************************************************************
 * @File Name: ebtn_Keys_Config.c
 * @brief 自定义按键参数配置文件及按键定义
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.0.0
 * @Creat Date : 2025-05-10
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 *   - 使用查表法定义键位与GPIO映射，增加 `EBTN_ACTIVE_LOW/HIGH` 语义化电平
 *   - 组合键配置改为变参宏 `COMBO_KEYS`，支持自适应长度
 *   - 导出数组与大小常量，便于 `ebtn_APP` 自动化初始化
 *   - 注释精简与开源风格统一
 * @Modifi Date : 2025-09-14
 */
#include "ebtn_Keys_Config.h"

/** ***************************************************************************
 * @brief 定义默认按键参数结构体
 * @ref ebtn_Keys_Config.h
 */
ebtn_btn_param_t buttons_parameters = EBTN_PARAMS_INIT(
    DEBOUNCE_TIME,            // 按下防抖超时
    RELEASE_DEBOUNCE_TIME,    // 松开防抖超时
    CLICK_AND_PRESS_MIN_TIME, // 按键最短时间
    CLICK_AND_PRESS_MAX_TIME, // 按键最长时间
    MULTI_CLICK_MAX_TIME,     // 连续点击最大间隔(ms)
    KEEPALIVE_TIME_PERIOD,    // 长按报告事件间隔(ms)
    MAX_CLICK_COUNT           // 最大连续点击次数
);

/* -------------------------------- 此处修改按键定义 -------------------------------- */

// 按键ID为 ebtn_Keys_Config.h 中的枚举定义，初始化函数会为所有枚举值初始化

/** ***************************************************************************
 * @brief 按键列表结构体数组，用于将按键ID与GPIO引脚以及触发电平进行绑定，
 * 同时使用查表检测,免去需要为每个按键手动添加检测方式
 * @note 此处填入所需的按键ID及其GPIO信息和触发时电平
 */
key_config_t keys_config_list[] = {
    // 按键ID，GPIO端口，    GPIO引脚， 触发电平
    {KEY_1, KEY_1_GPIO_Port, KEY_1_Pin, EBTN_ACTIVE_LOW}, // B1按键 PC4，低电平触发
    {KEY_2, KEY_2_GPIO_Port, KEY_2_Pin, EBTN_ACTIVE_LOW}, // B2按键 PC5，低电平触发
    {KEY_3, KEY_3_GPIO_Port, KEY_3_Pin, EBTN_ACTIVE_LOW}, // B3按键 PB0，低电平触发
    {KEY_4, KEY_4_GPIO_Port, KEY_4_Pin, EBTN_ACTIVE_LOW}, // B4按键 PB1，低电平触发
};

/* --------------------------------- 此处修改组合键配置 -------------------------------- */

/** ***************************************************************************
 * @brief 组合键配置表，定义每个组合键包含哪些单独按键
 * @note 支持自适应长度的按键数组，无固定长度限制
 */
const combo_config_t combo_keys_config_list[] = {
    //         组合键ID,    按键1, 按键2, ..., 按键N
    COMBO_KEYS(COMBO_KEY_1, KEY_1, KEY_2),
    // COMBO_KEYS(COMBO_KEY_2, KEY_2, KEY_3),
    // COMBO_KEYS(COMBO_KEY_3, KEY_1, KEY_2, KEY_3),
    // COMBO_KEYS(COMBO_KEY_4, KEY_1, KEY_2, KEY_3, KEY_4),
};

/* -------------------------------- 此处修改可选参数 -------------------------------- */

/** ***************************************************************************
 * @brief 按键单独参数配置表（可选）
 * @note 只为需要单独参数的按键配置，未配置的按键将自动使用默认的 buttons_parameters
 * @note 如果所有按键都使用默认参数，此表可以为空
 */
const special_key_list_t special_keys_list[] = {
    /* --------------------------------- 此处配置需要单独参数的按键 -------------------------------- */
    // 示例：只配置需要单独参数的按键

    // 方式1：使用单独参数配置宏（推荐）
    // KEY_SPECIAL_CONFIG(KEY_2, fast_response_parameters),  // KEY_2使用快速响应参数
    // KEY_SPECIAL_CONFIG(KEY_4, slow_response_parameters),  // KEY_4使用慢速响应参数

    // 方式2：手动配置
    // {KEY_3, &special_parameters},  // KEY_3使用单独参数

    // 如果所有按键都使用默认参数，可以留空
    // 初始化函数会为所有按键使用 buttons_parameters
};

/** ***************************************************************************
 * @brief 组合键单独参数配置表（可选）
 * @note 只为需要单独参数的组合键配置，未配置的组合键将自动使用默认的 buttons_parameters
 * @note 如果所有组合键都使用默认参数，此表可以为空
 */
const special_combo_key_list_t special_combo_keys_list[] = {
    /* --------------------------------- 此处配置需要单独参数的组合键 -------------------------------- */
    // 示例：只配置需要单独参数的组合键

    // 方式1：使用单独参数配置宏（推荐）
    // COMBO_SPECIAL_CONFIG(COMBO_KEY_1, long_press_parameters),  // COMBO_KEY_1使用长按参数
    // COMBO_SPECIAL_CONFIG(COMBO_KEY_3, quick_combo_parameters), // COMBO_KEY_3使用快速组合参数

    // 方式2：手动配置
    // {COMBO_KEY_2, &special_combo_parameters},  // COMBO_KEY_2使用单独组合参数

    // 如果所有组合键都使用默认参数，可以留空
    // 初始化函数会为所有组合键使用 buttons_parameters
};

/* -------------------------------- 自定义配置部分结束 ------------------------------- */

ebtn_btn_t btn_array[KEYS_COUNT] = {0};                                               // 基于枚举自动确定数组大小
ebtn_btn_combo_t btn_combo_array[COMBO_KEYS_COUNT] = {0};                             // 使用实际组合键数量
const uint8_t btn_array_size = KEYS_COUNT;                                            // 按键数组大小由枚举自动确定
const uint8_t btn_combo_array_size = COMBO_KEYS_COUNT;                                // 组合键数组大小为实际数量
const uint8_t keys_list_size = EBTN_ARRAY_SIZE(keys_config_list);                     // 硬件配置列表大小
const uint8_t combo_config_list_size = EBTN_ARRAY_SIZE(combo_keys_config_list);       // 组合键配置表大小
const uint8_t special_key_config_list_size = EBTN_ARRAY_SIZE(special_keys_list);      // 按键配置表大小
const uint8_t special_combo_key_list_size = EBTN_ARRAY_SIZE(special_combo_keys_list); // 组合键配置表大小