# Easy Button Application Layer - 基于 easy_button 的入门级应用层封装库

[🇺🇸 English](README-EN.md) | 🇨🇳 简体中文

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-STM32%20%7C%20CH32V-green.svg)](README.md)
[![Version](https://img.shields.io/badge/Version-1.3.0-orange.svg)](README.md)

📌 **项目简介**

这是一个基于强大的 [easy_button](https://github.com/bobwenstudy/easy_button) 库的**入门级应用层封装，专注于常见按键使用场景，让开发者能够快速上手 easy_button 的核心功能**。通过硬件抽象层（HAL）、应用层和适配层的分离设计，实现了高度的跨平台可移植性。

> 💡 **关于 easy_button 核心库**：easy_button 是一个功能丰富的嵌入式按键处理库，支持单击、多击、长按、组合键、防抖处理等高级功能。本封装库仅使用了其中的常用功能，如需更多高级特性，请参考 [easy_button 官方文档](https://github.com/bobwenstudy/easy_button)。

## 🚀 快速开始

### 环境要求

- C99 兼容的编译器
- 支持 GPIO 和系统时钟的嵌入式平台
- [easy_button 核心库](https://github.com/bobwenstudy/easy_button)

### 克隆项目与获取依赖

本项目已将 easy_button 核心库作为 Git 子模块集成，获取完整项目（包含依赖库）：

```bash
# 克隆项目并自动获取子模块
git clone --recursive https://github.com/Sighthesia/easy_button-Application.git

# 或者分步操作
git clone https://github.com/Sighthesia/easy_button-Application.git
cd easy_button-Application
git submodule update --init --recursive
```

子模块包含的核心文件：
- `easy_button/ebtn/ebtn.h` - 核心头文件
- `easy_button/ebtn/ebtn.c` - 核心实现
- `easy_button/ebtn/bit_array.h` - 位数组操作

**更新子模块到最新版本：**
```bash
git submodule update --remote easy_button
```

## ✅ 已验证平台

- **STM32G030** 
- **STM32H750**   
- **CH32V203** 

## 📁 项目结构

```
easy_button-Application/
├── ebtn_APP.c/h                    # 应用层接口和初始化
├── ebtn_APP_HAL.c/h             # 硬件抽象层（HAL）
├── ebtn_APP_Keys.c/h            # 按键引脚配置和参数
├── ebtn_APP_Event.c/h         # 按键事件回调处理
└── easy_button/                    # easy_button 核心库子模块
    ├── ebtn/
    │   ├── ebtn.h                  # 核心头文件
    │   ├── ebtn.c                  # 核心实现
    │   └── bit_array.h             # 位数组操作
    ├── example_test.c              # 测试示例
    ├── example_user.c              # 用户交互示例
    └── README.md                   # 核心库说明文档
```

## 🧭 移植指南

### 第一步：适配硬件抽象层（HAL）

**目标**：实现平台相关的底层函数

1. **修改头文件包含**
   
   打开 `ebtn_APP_HAL.h`，包含适合你平台的 GPIO 和系统时钟头文件：
   
   ```c
   // 示例：STM32F1 系列
   #include "stm32f1xx_hal.h"
   
   // 示例：CH32V 系列  
   #include "ch32v20x.h"
   ```
   
   - 默认包含 `"mian.h"`，通常包含了 `GPIO_TypeDef` 等平台相关定义，如仍报错可包含具体文件。

2. **实现核心回调函数**
   
   在 `ebtn_APP_HAL.c` 中实现两个关键回调函数：
   
   ```c
   // 读取指定引脚的逻辑电平
   uint8_t ebtn_HAL_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
   {
       return (uint8_t)HAL_GPIO_ReadPin(GPIOx, GPIO_Pin); // STM32 HAL
   }
   
   // 获取当前系统滴答计数（毫秒）
   uint32_t ebtn_HAL_Get_Tick(void)
   {
       return HAL_GetTick(); // STM32 HAL
   }
   ```

### 第二步：配置按键设置（适配层）

**目标**：定义硬件引脚映射和按键行为

1. **定义按键 ID**
   
   在 `ebtn_APP_Keys.h` 中定义按键 ID：
   
   ```c
   typedef enum
   {
       KEY_1 = 0,
       KEY_2,
       KEY_3,
       KEY_4,
       // 添加更多按键...
       KEYS_COUNT // 按键总数
   } key_enum_t;
   ```

2. **配置按键硬件映射**
   
   在 `ebtn_APP_Keys.c` 中填写 `keys_config_list[]` 数组：
   
   ```c
   key_config_t keys_config_list[] = {
       {KEY_1, GPIOA, GPIO_PIN_0, EBTN_ACTIVE_LOW},  // PA0，低电平有效
       {KEY_2, GPIOA, GPIO_PIN_1, EBTN_ACTIVE_HIGH}, // PA1，高电平有效
       {KEY_3, GPIOB, GPIO_PIN_2, EBTN_ACTIVE_LOW},  // PB2，低电平有效
       // 添加更多按键配置...
   };
   ```

3. **调整时间参数**（可选）
   
   根据需要修改以下宏定义：
   
   ```c
   #define DEBOUNCE_TIME 20                // 防抖时间（毫秒）
   #define CLICK_AND_PRESS_MAX_TIME 200    // 长按判定阈值（毫秒）
   #define KEEPALIVE_TIME_PERIOD 500       // 长按周期（毫秒）
   #define MAX_CLICK_COUNT 3               // 最大连击次数
   ```

4. **配置组合键**（可选）
   
   如果需要组合键，添加到 `combo_keys_config_list[]` 数组：
   
   ```c
   const combo_config_t combo_keys_config_list[] = {
       COMBO_KEYS(COMBO_KEY_1, KEY_1, KEY_2),        // 按键1+按键2
       COMBO_KEYS(COMBO_KEY_2, KEY_1, KEY_3, KEY_4), // 按键1+按键3+按键4
   };
   ```

### 第三步：实现事件回调（应用层）

**目标**：定义按键事件的自定义处理逻辑

在 `ebtn_APP_Event.c` 中找到 `ebtn_APP_Event()` 函数，根据按键 ID 和事件类型实现相应的处理逻辑：

```c
void ebtn_APP_Event(struct ebtn_btn *btn, ebtn_evt_t evt)
{
    switch (btn->key_id)
    {
        case KEY_1:
            if (evt == EBTN_EVT_ONPRESS)
            {
                // 按键1按下处理
            }
            else if (evt == EBTN_EVT_ONRELEASE)
            {
                // 按键1释放处理
            }
            else if (evt == EBTN_EVT_ONCLICK)
            {
                if (btn->click_cnt == 1)
                {
                    // 单击处理
                }
                else if (btn->click_cnt == 2)
                {
                    // 双击处理
                }
            }
            else if (evt == EBTN_EVT_KEEPALIVE)
            {
                if (btn->keepalive_cnt == 1)
                {
                    // 长按1次周期处理
                }
            }
            break;
            
        case KEY_2:
            // 按键2的处理逻辑...
            break;
            
        case COMBO_KEY_1:
            // 组合键1的处理逻辑...
            break;
            
        default:
            break;
    }
}
```

**事件类型说明**：
- `EBTN_EVT_ONPRESS` - 按键按下事件
- `EBTN_EVT_ONRELEASE` - 按键释放事件  
- `EBTN_EVT_ONCLICK` - 单击/多击事件（通过 `ebtn->click_cnt` 区分）
- `EBTN_EVT_KEEPALIVE` - 长按保持事件（通过 `ebtn->keepalive_cnt` 计数）

### 第四步：集成到主程序（应用层）

**目标**：初始化按键模块并定期处理按键状态

1. **在系统初始化中调用**：
   
   ```c
   #include "ebtn_APP.h" // 包含头文件

   int main(void)
   {
       // 系统初始化...
       
       ebtn_APP_Keys_Init(); // 初始化按键模块
       
       while (1)
       {
           ebtn_APP_Process(); // 定期处理按键事件（建议5-20ms）
           
           // 其他应用逻辑...
           HAL_Delay(10);
       }
   }
   ```

2. **或在定时器中断中调用**：
   
   ```c
   void TIM_IRQHandler(void)
   {
       if (/* 定时器中断条件 */)
       {
           ebtn_APP_Process(); // 每10-20ms调用一次
       }
   }
   ```

## 🔧 API 参考

### 核心 API

```c
void ebtn_APP_Keys_Init(void);    // 初始化按键模块
void ebtn_APP_Process(void);      // 处理按键事件（需定期调用）
```

### 高级查询（通过 easy_button 核心库API）

如需更多查询功能，可以直接使用 easy_button 核心库提供的API：

```c
// 通过按键ID获取按键实例
ebtn_btn_t *btn = ebtn_get_btn_by_key_id(KEY_1);

// 检查按键是否处于激活状态
int is_active = ebtn_is_btn_active(btn);

// 检查按键是否正在处理中
int in_process = ebtn_is_btn_in_process(btn);

// 检查是否有任何按键正在处理（用于低功耗）
int any_in_process = ebtn_is_in_process();
```

**注意**：使用核心库API前，请包含头文件 `#include "ebtn.h"`

## ❓ 常见问题

### Q: 如何添加新按键？
A: 在 `ebtn_APP_Keys.h` 中添加新的 `KEY_X` 枚举值，然后在 `ebtn_APP_Keys.c` 中更新 `keys_config_list[]` 数组配置。

### Q: 如何移植到不同的 MCU 平台？
A: 只需修改 `ebtn_APP_HAL.c/h` 中的底层函数实现（如 `GPIO_ReadPin`、`SysTick`），其他文件无需修改。

### Q: 如何自定义事件处理？
A: 在 `ebtn_APP_Event.c` 中实现自己的处理函数，并在 `ebtn_APP_Event()` 中根据按键 ID 和事件类型调用。

### Q: 编译时提示找不到 easy_button 相关文件？
A: 请确保已正确获取子模块。运行 `git submodule update --init --recursive` 来获取 easy_button 核心库文件。

### Q: 如何调整防抖时间？
A: 修改 `ebtn_APP_Keys.h` 中的 `DEBOUNCE_TIME` 宏定义，单位为毫秒。

### Q: 如何更新 easy_button 核心库到最新版本？
A: 运行 `git submodule update --remote easy_button` 来更新子模块到最新版本。

## 🎯 特性支持

- ✅ **单击/多击检测** - 支持最多连续点击检测
- ✅ **长按检测** - 支持多级长按（通过 `keepalive_cnt` 实现）
- ✅ **组合键支持** - 支持多按键组合
- ✅ **防抖处理** - 硬件级防抖，可配置防抖时间
- ✅ **低功耗支持** - 提供睡眠状态检测接口
- ✅ **跨平台移植** - 硬件抽象层设计，易于移植

## 🛠️ 高级配置

### 自定义按键参数

如果某些按键需要特殊的时间参数，可以在 `ebtn_APP_Keys.c` 中使用特殊配置：

```c
// 定义特殊参数
static ebtn_btn_param_t long_press_params = EBTN_PARAMS_INIT(
    20,    // 防抖时间
    0,     // 释放防抖时间
    20,    // 最短按下时间
    100,   // 最长短按时间
    200,   // 多击间隔
    1000,  // 长按周期（1秒）
    5      // 最大连击次数
);

// 应用特殊参数
const special_key_list_t special_keys_list[] = {
    KEY_SPECIAL_CONFIG(KEY_1, long_press_params),
};
```

### 低功耗模式

使用 `ebtn_is_in_process()` 检查是否可以进入深度睡眠：

```c
if (!ebtn_is_in_process())
{
    // 安全进入深度睡眠模式
    HAL_PWR_EnterSTOPMode();
}
```

## ❤️ 致谢

- **核心库**：[bobwenstudy/easy_button](https://github.com/bobwenstudy/easy_button)
- **设计灵感**：[FlexibleButton](https://github.com/murphyzhao/FlexibleButton)、[MultiButton](https://github.com/0x1abin/MultiButton)、[lwbtn](https://github.com/MaJerle/lwbtn)

## 📚 更多资源

- [Easy Button 核心库文档](https://github.com/bobwenstudy/easy_button/blob/main/README.md)
- [示例代码和测试用例](easy_button/example_test.c)
- [移植参考指南](easy_button/example_user.c)

如有任何问题或建议，欢迎提交 [Issue](https://github.com/Sighthesia/easy_button-Application/issues) 或 [Pull Request](https://github.com/Sighthesia/easy_button-Application/pulls)！

## 📄 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

**第三方许可证**：本项目使用的 [easy_button 核心库](https://github.com/bobwenstudy/easy_button) 采用 Apache-2.0 许可证。

---

🤖 ☝️🤓 **由 GitHub Copilot 辅助开发**