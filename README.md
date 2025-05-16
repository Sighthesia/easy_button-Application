# easy_button-Application
An basic application for key detecting of easy_button, a powerful embbed button management library

# `easy_button_app` 快速移植指南（优化版）

本指南适用于 `easy_button_app` 目录下的自定义封装文件，帮助开发者在不同硬件平台上快速完成按键驱动的移植。

> ⚠️ **注意：** 本实现未附带 `easy_button` 官方库文件，请前往 [easy_button](https://github.com/bowenstudy/easy_button ) 获取最新版本以确保功能正常。

---

## 📁 文件结构说明
easy_button_app/
├── ebtn_app.c/h // 应用层接口与初始化
├── ebtn_custom_hal.c/h // 硬件抽象层适配
├── ebtn_custom_config.c/h // 按键参数与引脚配置
├── ebtn_custom_callback.c/h // 按键事件回调处理


---

## 🧭 移植步骤详解（按顺序执行）

### 1. 适配硬件抽象层（HAL 层）

**目标：** 实现平台相关的底层接口。

- 打开 `ebtn_custom_hal.h`，引入对应平台的 GPIO 和系统时钟头文件（如 STM32 的 `stm32f1xx_hal.h`）。
- 实现两个核心函数：
  - `ebtn_HAL_Read_Pin()`：读取指定引脚电平状态；
  - `ebtn_HAL_Get_Tick()`：获取当前系统时间戳（单位为毫秒）；
- 检查 `ebtn_custom_hal_t` 结构体中的函数指针是否与平台接口一致。

✅ **完成后标志：** 可以正确获取按键引脚状态和系统时间。

---

### 2. 配置按键信息（配置层）

**目标：** 设置按键硬件参数与行为逻辑。

- 在 `ebtn_custom_config.h` 中定义按键 ID（如 `KEY_1`, `KEY_2` 等）；
- 在 `key_list[]` 数组中填写每个按键对应的 GPIO 引脚、端口号和有效电平（0 表示低电平触发，1 表示高电平）；
- 根据需求修改以下宏定义：
  - `DEBOUNCE_TICKS`：消抖时间；
  - `LONG_PRESS_TICKS`：长按判定时间；
  - `REPEAT_TICKS`：连击间隔；
- 若使用组合键，在 `btn_combo_array[]` 中添加组合键定义；
- 将单个按键对象加入 `btn_array[]`。

✅ **完成后标志：** 按键可被识别，并具备所需行为（如防抖、长按等）。

---

### 3. 实现按键事件回调（回调层）

**目标：** 定义按键触发后的业务逻辑。

- 在 `ebtn_custom_callback.c` 中找到 `ebtn_Event_Handler()` 函数；
- 根据传入的按键 ID 和事件类型（如按下、释放、长按等），调用相应的处理函数；
- 推荐将不同按键或事件拆分为独立函数，提高代码可维护性；
- 可自定义事件响应逻辑，例如 UI 更新、任务调度等。

✅ **完成后标志：** 按键事件能触发预设动作。

---

### 4. 应用层调用（主程序集成）

**目标：** 初始化并周期性处理按键事件。

- 在主函数初始化阶段调用 `ebtn_APP_Key_INIT()` 完成按键模块初始化；
- 在主循环中或定时器中断中定期调用 `ebtn_APP_Key_Process()`（建议每 20ms 调用一次）；
- 如需查询按键状态，可调用辅助函数：
  - `ebtn_APP_Is_Key_Active(KEY_X)`：判断按键是否处于激活状态；
  - `ebtn_APP_Get_Key_State(KEY_X)`：获取按键当前状态；
  - `ebtn_APP_Get_Key_Press_Time(KEY_X)`：获取按键按下时间；

✅ **完成后标志：** 整个按键系统运行稳定，事件响应及时无误。

---

## ❓ 常见问题解答

### Q: 如何添加新按键？

A: 在 `ebtn_custom_config.h` 中新增 `KEY_X` 枚举值，并在 `key_list[]`、`btn_array[]` 中添加相应配置项即可。

### Q: 如何适配不同的 MCU 平台？

A: 只需修改 `ebtn_custom_hal.c/h` 文件中的底层函数实现，其余代码无需改动。

### Q: 如何自定义按键事件处理？

A: 在 `ebtn_custom_callback.c` 中编写具体处理函数，并在 `ebtn_Event_Handler()` 中根据按键 ID 和事件类型调用这些函数。

---

## 📚 参考资料

- [easy_button](https://github.com/bowenstudy/easy_button )
- 各 `.c/.h` 文件顶部注释提供详细使用示例

---

如有疑问或建议，欢迎提交 Issue 或 Pull Request！