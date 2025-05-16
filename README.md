# easy_button-Application
An basic application for key detecting of easy_button, a powerful embbed button management library

# easy_button_app 快速移植指南

本指南适用于 `easy_button_app` 目录下的自定义封装文件，帮助开发者在不同硬件平台上快速完成按键驱动的移植。

---

## 目录结构说明

```
easy_button_app/
├── ebtn_app.c/h                // 应用层接口与初始化
├── ebtn_custom_hal.c/h         // 硬件抽象层（HAL）适配
├── ebtn_custom_config.c/h      // 按键参数与引脚配置
├── ebtn_custom_callback.c/h    // 按键状态与事件回调
```

---

## 移植流程图

```
┌─────────────────────────────────────────────┐
│           easy_button 快速移植流程           │
└─────────────────────────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────────┐
│ 1. 适配硬件抽象层 ebtn_custom_hal.c/h        │
│   - 修改 Read_Pin、Get_Tick 函数            │
│   - 引入对应平台的 GPIO/SysTick 头文件       │
└─────────────────────────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────────┐
│ 2. 配置按键信息 ebtn_custom_config.c/h       │
│   - 定义按键ID（KEY_1, KEY_2...）           │
│   - 填写 key_list[] 绑定引脚和有效电平       │
│   - 配置参数宏（防抖、长按、连击等）         │
│   - 配置 btn_array[]、btn_combo_array[]      │
└─────────────────────────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────────┐
│ 3. 实现按键事件回调 ebtn_custom_callback.c/h │
│   - 按需实现 ebtn_Event_Handler              │
│   - 可拆分为各按键/事件专用处理函数         │
└─────────────────────────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────────┐
│ 4. 应用层调用 ebtn_app.c/h                   │
│   - 在主循环或定时器中断中定期调用 ebtn_APP_Key_Process  │
│   - 使用 ebtn_APP_Key_INIT 初始化            │
│   - 按需调用辅助接口                         │
└─────────────────────────────────────────────┘
```

---

## 详细移植步骤

### 1. 适配硬件抽象层（HAL）

- 打开 `ebtn_custom_hal.h`，包含你平台的 GPIO/SysTick 头文件。
- 实现 `ebtn_HAL_Read_Pin` 和 `ebtn_HAL_Get_Tick`，分别用于读取引脚电平和获取系统时间（ms）。
- 检查 `ebtn_custom_hal_t` 结构体，确保接口与平台匹配。

### 2. 配置按键信息

- 在 `ebtn_custom_config.h` 中定义你的按键ID（如 KEY_1、KEY_2）。
- 在 `key_list[]` 中填写每个按键的 GPIO 端口、引脚号和有效电平（0=低，1=高）。
- 根据实际需求调整参数宏（防抖、长按、连击等）。
- 在 `btn_array[]` 和 `btn_combo_array[]` 中添加你的按键和组合键。

### 3. 实现按键事件回调

- 在 `ebtn_custom_callback.c` 的 `ebtn_Event_Handler` 中，根据按键ID和事件类型调用你的处理函数。
- 推荐将每个按键/事件的处理逻辑拆分为独立函数，便于维护。

### 4. 应用层调用

- 在主函数初始化时调用 `ebtn_APP_Key_INIT()`。
- 在主循环或定时器中定期调用 `ebtn_APP_Key_Process()`（建议周期20ms）。
- 如需判断按键状态，可调用 `ebtn_APP_Is_Key_Active`、`ebtn_APP_Get_Key_State` 等辅助接口。

---

## 常见问题

- **如何添加新按键？**  
  在 `ebtn_custom_config.h` 增加新的 KEY_X 枚举，并在 `key_list[]` 和 `btn_array[]` 中补充对应项。

- **如何适配不同MCU？**  
  只需修改 `ebtn_custom_hal.c/h`，其余文件无需更改。

- **如何自定义事件处理？**  
  在 `ebtn_custom_callback.c` 中实现对应的事件处理函数，并在 `ebtn_Event_Handler` 中调用。

---

## 参考

- [easy_button Github](https://github.com/bowenstudy/easy_button)
- 示例代码详见各 .c/.h 文件顶部注释

---

如有疑问，欢迎 issue 或 PR！
