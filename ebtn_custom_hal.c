/** ***************************************************************************
 * @File Name: ebtn_custom_hal.c
 * @brief ebtn应用的抽象硬件操作回调函数具体实现
 * 在首次移植到特定平台后无需再更改
 * @credit : bowenstudy / easy_button https://github.com/bowenstudy/easy_button
 * @Author : Sighthesia / easy_button-Application https://github.com/Sighthesia/easy_button-Application/tree/main
 * @Version : 1.0.0
 * @Creat Date : 2025-05-06
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 * @Modifi Date :
 */
#include "ebtn_custom_hal.h"

/* ------------------------------ 此处实现硬件抽象回调函数 ------------------------------ */

/** ***************************************************************************
 * @brief 读取GPIO电平，在ebtn_app.c中被使用，用于读取按键引脚的电平
 * @param GPIOx 指向GPIO端口的指针
 * @param GPIO_Pin GPIO引脚号
 * @return GPIO引脚的电平状态（0/1）
 */
uint8_t ebtn_HAL_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    // return (uint8_t)HAL_GPIO_ReadPin(GPIOx, GPIO_Pin); // 示例：STM32HAL库；强制转换uint8_t类型，确保通用性
}

/** ***************************************************************************
 * @brief  获取系统滴答计数器值，用于为ebtn_process()函数提供时间基准
 * @note   SysTick时基为1ms
 * @return 系统滴答计数器ms时间值
 */
uint32_t ebtn_HAL_Get_Tick(void)
{
    // return HAL_GetTick(); // 示例：STM32HAL库
}

/* -------------------------------- 自定义配置部分结束 ------------------------------- */

/** ***************************************************************************
 * @brief  ebtn_Custom回调函数结构体实例化
 */

ebtn_custom_hal_t ebtn_custom_hal = {
    .Read_Pin = ebtn_HAL_Read_Pin,
    .Get_Tick = ebtn_HAL_Get_Tick,
};