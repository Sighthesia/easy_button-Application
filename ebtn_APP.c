/** ***************************************************************************
 * @File Name: ebtn_app.c
 * @brief 基于easy_button库的应用层基础实现，提供最主要的静态按键支持
 * @ref ebtn_APP_HAL.c/h
 * @credit : bobwenstudy / easy_button https://github.com/bobwenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.3.0
 * @Creat Date : 2025-03-01
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes : 添加回调函数机制，降低各层级耦合度，从而实现多平台适配
 * @Modifi Date : 2025-05-06
 * @Author : Sighthesia
 * @Changes :
 *   - 自动化初始化：遍历枚举与配置表，免手动注册
 *   - 支持组合键：通过 `COMBO_KEYS_COUNT` 与转换内联函数建立索引映射
 *   - 注释精简，突出使用方法（Init+Process 周期）
 *   - 将平台定义统一通过 `ebtn_APP_HAL.h` 提供，应用实现文件通过包含 HAL 头获取平台类型与 HAL 实现
 * @Modifi Date : 2025-09-14
 */
#include "ebtn_APP.h"
#include "ebtn.h"
#include "ebtn_APP_Keys.h"
#include "ebtn_APP_Event.h"
#include "ebtn_APP_HAL.h"

/** ***************************************************************************
 * @brief easy_button初始化
 * @note  在主函数中调用
 * 基于单按键和组合键配置列表循环查表自动初始化，通常无需手动配置
 */
void ebtn_APP_Keys_Init(void)
{
    // 1. 遍历所有按键枚举值，自动查表初始化
    for (key_enum_t key_id = 0; key_id < KEYS_COUNT; key_id++)
    {
        // 查找按键配置表中是否有该按键的配置
        ebtn_btn_param_t *params = &buttons_parameters; // 默认参数

        // 在配置表中查找自定义参数
        for (uint8_t i = 0; i < special_key_config_list_size; i++)
        {
            if (special_keys_list[i].key_id == key_id)
            {
                params = special_keys_list[i].params; // 使用配置表中的参数
                break;
            }
        }

        // 初始化按键结构体
        btn_array[key_id] = (ebtn_btn_t)EBTN_BUTTON_INIT(key_id, params);
    }

    // 2. 遍历所有组合键枚举值，自动查表初始化
    for (uint8_t i = 0; i < COMBO_KEYS_COUNT; i++)
    {
        combo_key_enum_t combo_id = index_to_combo_id(i);

        // 查找组合键配置表中是否有该组合键的配置
        ebtn_btn_param_t *params = &buttons_parameters; // 默认参数

        // 在配置表中查找自定义参数
        for (uint8_t j = 0; j < special_combo_key_list_size; j++)
        {
            if (special_combo_keys_list[j].combo_key_id == combo_id)
            {
                params = special_combo_keys_list[j].params; // 使用配置表中的参数
                break;
            }
        }

        // 初始化组合键结构体，使用数组索引而非枚举值
        btn_combo_array[i] = (ebtn_btn_combo_t)EBTN_BUTTON_COMBO_INIT(combo_id, params);
    }

    // 3. 初始化easy_button库，使用实际数组大小
    ebtn_init(btn_array, KEYS_COUNT,
              btn_combo_array, COMBO_KEYS_COUNT,
              Get_Key_State, ebtn_APP_Event);

    // 4. 遍历组合键配置表，自动添加组合键
    for (uint8_t i = 0; i < combo_config_list_size; i++)
    {
        const combo_config_t *config = &combo_keys_config_list[i];

        // 转换组合键ID为数组索引
        uint8_t index = combo_id_to_index(config->combo_key_id);
        if (index < COMBO_KEYS_COUNT)
        {
            // 向该组合键添加所有配置的按键
            for (uint8_t k = 0; k < config->key_count; k++)
            {
                ebtn_combo_btn_add_btn(&btn_combo_array[index], config->keys[k]);
            }
        }
    }
}

/** ***************************************************************************
 * @brief 处理按键事件，需要定期调用，建议以20ms为周期执行一次
 * @note  Tick时基为1ms
 */
void ebtn_APP_Process(void)
{
    ebtn_process(ebtn_APP_HAL.Get_Tick()); // 获取时间处理按键事件
}
