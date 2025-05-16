/** ***************************************************************************
 * @File Name: ebtn_custom_hal.h
 * @brief ebtn应用层的抽象硬件操作回调函数声明
 * @note 需要搭配应用层ebtn_app.c/h使用
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
#ifndef EBTN_CUSTOM_HAL_H
#define EBTN_CUSTOM_HAL_H

/* ------------------------------ 此处包含单片机平台的头文件 ----------------------------- */
// 需要包含单片机平台GPIO和SysTick的头文件
// #include "stm32h7xx_hal.h" // 示例：STM32H7系列单片机的HAL库头文件

/* ------------------------ 此处修改适配层回调函数自定义声明（如有需求） ------------------------ */
/** ***************************************************************************
 * @brief  自定义回调函数结构体声明
 */
typedef struct
{
    /** ***************************************************************************
     * @brief 读取GPIO电平
     * @note  在ebtn_APP.c中调用，用于读取按键引脚的电平
     * @param GPIOx 指向GPIO端口的指针
     * @param GPIO_Pin GPIO引脚号
     * @return GPIO引脚的电平状态
     */
    // 如果GPIO_TyepDef不同则修改
    uint8_t (*Read_Pin)(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

    /** ***************************************************************************
     * @brief  获取系统滴答计数器值
     * @note   需要定期调用,建议20ms一次
     * @note   SysTick时基为1ms
     * @return 系统滴答计数器值
     */
    uint32_t (*Get_Tick)(void);
} ebtn_custom_hal_t;

/* -------------------------------- 自定义配置部分结束 ------------------------------- */

extern ebtn_custom_hal_t ebtn_custom_hal; // ebtn适配层回调函数结构声明

#endif /* EBTN_CUSTOM_HAL_H */