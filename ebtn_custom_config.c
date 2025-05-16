/** ***************************************************************************
 * @File Name: ebtn_custom_config.c
 * @brief  自定义按键参数配置文件及按键定义
 * @credit : bowenstudy / easy_button https://github.com/bowenstudy/easy_button
 * @Author : Sighthesia
 * @Version : 1.0.0
 * @Creat Date : 2025-05-10
 *          ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 * @Modifi Date :
 */
#include "ebtn_custom_config.h"

/** ***************************************************************************
 * @brief 按键参数
 * @ref ebtn_Custom_x.h
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

/* --------------------------------- 此处修改按键 --------------------------------- */
// 所需的按键ID定义在ebtn_custom_config.h中增添

/** ***************************************************************************
 * @brief 按键列表结构体数组，用于将按键ID与GPIO引脚以及触发电平进行绑定,免去一个个地手动添加扫描方式
 * @note 此处填入所需的按键ID及其GPIO信息和触发电平
 */
ebtn_custom_config_key_list_t key_list[] = {
    // {KEY_1, GPIOA, GPIO_Pin_4, 0},  // EC11按键，PA4，低电平有效
    // {KEY_2, GPIOB, GPIO_Pin_13, 0}, // KEY_2按键，PB13，低电平有效
    // {KEY_3, GPIOB, GPIO_Pin_1, 0},  // KEY_3按键，PB1，低电平有效
    // {KEY_4, GPIOB, GPIO_Pin_12, 0}, // KEY_4按键，PB12，低电平有效
};

/** ***************************************************************************
 * @brief 按键结构体数组，用于将按键ID与按键参数进行绑定
 * @note 此为静态注册方法，动态注册详见easy_button库Github仓库
 */
ebtn_btn_t btn_array[] = {
    EBTN_BUTTON_INIT(KEY_1, &buttons_parameters),
    EBTN_BUTTON_INIT(KEY_2, &buttons_parameters),
    EBTN_BUTTON_INIT(KEY_3, &buttons_parameters),
    EBTN_BUTTON_INIT(KEY_4, &buttons_parameters),
};

/** ***************************************************************************
 * @brief 组合键结构体数组，用于将多个按键组合成一个按键
 * @note 此为静态注册方法，动态注册详见easy_button库Github仓库
 * @note 需要在ebtn_APP.c的void ebtn_APP_Key_INIT(void)函数中使用ebtn_Combo_btn_add_btn向组合键结构体数组添加对应按键，其中结构体数组索引与此处结构体数组的顺序一致
 */
ebtn_btn_combo_t btn_combo_array[] = {
    EBTN_BUTTON_COMBO_INIT(COMBO_KEY_1, &buttons_parameters),
    EBTN_BUTTON_COMBO_INIT(COMBO_KEY_2, &buttons_parameters),
    EBTN_BUTTON_COMBO_INIT(COMBO_KEY_3, &buttons_parameters),
    EBTN_BUTTON_COMBO_INIT(COMBO_KEY_4, &buttons_parameters),
};

/* -------------------------------- 自定义配置部分结束 ------------------------------- */

const uint8_t btn_array_size = EBTN_ARRAY_SIZE(btn_array);
const uint8_t btn_combo_array_size = EBTN_ARRAY_SIZE(btn_combo_array);
const uint8_t key_list_size = EBTN_ARRAY_SIZE(key_list);