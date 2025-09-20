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
 * @Changes :
 *   - 梳理应用层接口与调用流程（Init/Process），注释精简
 *   - 明确依赖：Keys_Config、HAL_Config、Event_Callback 三者注入
 *   - 将平台头包含策略调整为：`ebtn_APP_HAL.h` 默认包含平台头（如 `main.h`），实现文件包含 HAL 头以获取平台定义，从而减少传递包含
 *   - 保持 API 不变，增强可读性与可维护性
 * @Modifi Date : 2025-09-14
 */
#ifndef EBTN_APP_H
#define EBTN_APP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void ebtn_APP_Keys_Init(void);
    void ebtn_APP_Process(void);

#ifdef __cplusplus
}
#endif

#endif /* EBTN_APP_H */