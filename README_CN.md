[中文](README_CN.md) [English](README.md)

# 📌简介
一个基于 [easy_button](https://github.com/bobwenstudy/easy_button ) （一个功能强大的嵌入式按键管理库）实现的按键检测基础应用示例。该实现采用硬件抽象设计理念，将应用层、硬件抽象层和适配层进行解耦分离，具备良好的可移植性。

# 🚀快速移植

以下为在不同硬件平台上快速完成按键驱动移植的教程。

- ✅ 已在STM32G030,STM32H750,CH32V203上测试成功

> ⚠️ **注意：** 本实现未附带 `easy_button` 官方库文件，请前往 [easy_button库](https://github.com/bobwenstudy/easy_button ) 获取最新版本库文件（ebtn.h，ebtn.c，bit_array.h）以确保功能正常。

---

## 📁 文件结构说明
```
easy_button_app/
├── ebtn_app.c/h // 应用层接口与初始化
├── ebtn_custom_hal.c/h // 硬件抽象层适配
├── ebtn_custom_config.c/h // 按键参数与引脚配置
├── ebtn_custom_callback.c/h // 按键事件回调处理
```

---

## 🧭 移植步骤详解

### 1. 适配硬件抽象层（HAL 层）

**目标：** 实现平台相关的底层接口。

- 打开 `ebtn_custom_hal.h`，引入对应平台的 GPIO 和系统时钟头文件（如 STM32 的 `stm32f1xx_hal.h`）。
- 在 'ebtn_custom_hal.c' 用当前平台的函数实现两个核心回调函数：
  - `ebtn_HAL_Read_Pin()`：读取指定引脚电平状态；
  - `ebtn_HAL_Get_Tick()`：获取当前系统时间戳（单位为1毫秒）；

---

### 2. 配置按键信息（适配层）

**目标：** 设置按键硬件参数与按键参数。

- 在 `ebtn_custom_config.h` 中定义按键 ID（如 `KEY_1`, `KEY_2` 等）；
- 在 `ebtn_custom_config.c` 的 `key_list[]` 数组中填写每个按键对应的 GPIO 引脚、端口号和有效电平（0 表示低电平触发，1 表示高电平）；
- 根据需求修改以下参数宏定义：
  - `DEBOUNCE_TICKS`：消抖时间；
  - `LONG_PRESS_TICKS`：长按判定时间；
  - `REPEAT_TICKS`：连击间隔；
  - 其他参数...
- 若使用组合键，在 `btn_combo_array[]` 中添加组合键定义,同时需要在`ebtn_app.c`的`ebtn_APP_Key_INIT()`函数中，在其中的初始化函数后使用如`ebtn_combo_btn_add_btn(&btn_combo_array[0], KEY_1);`向组合键加入按键；
- 将单个按键对象加入 `btn_array[]`。

---

### 3. 实现按键事件回调（应用层）

**目标：** 定义按键触发后的业务逻辑。

- 在 `ebtn_custom_callback.c` 中找到 `ebtn_Event_Handler()` 函数；
- 根据传入的按键 ID 和事件类型（如按下、释放、长按等），调用相应的处理函数；
- 推荐将不同按键或事件的处理逻辑拆分为独立的函数，并在 `ebtn_Event_Handler` 中参考原有的 `switch(ebtn->key)` 结构，在对应按键编号的 `case` 分支中调用相应的处理函数，以提升代码的可读性和可维护性；
- 可自定义事件响应逻辑，例如 UI 更新、任务调度等。

---

### 4. 调用按键处理函数（应用层）

**目标：** 初始化并周期性处理按键事件。

- 在主函数初始化阶段调用 `ebtn_APP_Key_INIT()` 完成按键模块初始化；
- 在主循环中或定时器中断中定期调用 `ebtn_APP_Key_Process()`（建议每 5~20ms 调用一次）；
- 如需查询按键状态，可调用辅助函数：
  - `ebtn_APP_Is_Key_Active(KEY_X)`：判断按键是否处于激活状态；
  - `ebtn_APP_Get_Key_State(KEY_X)`：获取按键当前状态；
  - `ebtn_APP_Get_Key_Press_Time(KEY_X)`：获取按键按下时间；

---

## ❓ 常见问题解答

### Q: 如何添加新按键？

A: 在 `ebtn_custom_config.h` 中新增 `KEY_X` 枚举值，并在 `ebtn_custom_config.c` 的 `key_list[]`、`btn_array[]` 中添加相应配置项即可。

### Q: 如何适配不同的 MCU 平台？

A: 只需修改 `ebtn_custom_hal.c/h` 文件中的底层函数（SysTick,GPIO_ReadPin)实现，其余代码无需改动。

### Q: 如何自定义按键事件处理？

A: 在 `ebtn_custom_callback.c` 中编写具体处理函数，并在 `ebtn_Event_Handler()` 中根据按键 ID 和事件类型调用这些函数。

---

## ❤ Credit

- [easy_button](https://github.com/bobwenstudy/easy_button )

## 📚参考

- 各 `.c/.h` 文件注释提供详细使用示例

---

如有疑问或建议，欢迎提交 Issue 或 Pull Request！
