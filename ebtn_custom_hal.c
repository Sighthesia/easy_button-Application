/** ***************************************************************************
 * @File Name: ebtn_custom_hal.c
 * @brief ebtn应用层的抽象硬件操作回调函数具体实现
 * @note 需要搭配应用层ebtn_APP.c/h使用
 * @credit : bowenstudy / easy_button https://github.com/bowenstudy/easy_button
 * @Author : Sighthesia
 * @Version : 1.0.0
 * @Creat Date : 2025-05-06
 * ----------------------------------------------------------------------------
 * @Modification
 * @Author : Sighthesia
 * @Changes :
 * @Modifi Date :
 */
#include "ebtn_custom_hal.h"

/** ***************************************************************************
 * @brief  读取GPIO电平
 * @param  GPIOx: 指向GPIO端口的指针
 * @param  GPIO_Pin: GPIO引脚号
 * @return uint8_t: GPIO引脚的电平状态
 */
uint8_t ebtn_HAL_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    // return (uint8_t)HAL_GPIO_ReadPin(GPIOx, GPIO_Pin); //示例：STM32HAL库；强制转换uint8_t类型，确保通用性
}

/** ***************************************************************************
 * @brief  获取系统滴答计数器值
 * @return uint32_t: 系统滴答计数器值
 * @note   SysTick时基为1ms
 */
uint32_t ebtn_HAL_Get_Tick(void)
{
    // return HAL_GetTick(); //示例：STM32HAL库
}

/** ***************************************************************************
 * @brief  ebtn_Custom回调函数结构体实例化
 */

ebtn_custom_hal_t ebtn_custom_hal = {
    .Read_Pin = ebtn_HAL_Read_Pin,
    .Get_Tick = ebtn_HAL_Get_Tick,
};