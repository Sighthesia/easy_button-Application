# Easy Button Application Layer - Entry-level Application Layer Wrapper for easy_button

🇺🇸 English | [🇨🇳 简体中文](README.md)

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-STM32%20%7C%20CH32V-green.svg)](README.md)
[![Version](https://img.shields.io/badge/Version-1.2.0-orange.svg)](README.md)

📌 **Description**

This is an **entry-level application layer wrapper based on the powerful [easy_button](https://github.com/bobwenstudy/easy_button) library, focusing on common button usage scenarios to help developers quickly get started with easy_button's core functionality**. Through the separation of Hardware Abstraction Layer (HAL), application layer, and adaptation layer, it achieves high cross-platform portability.

> 💡 **About easy_button Core Library**: easy_button is a feature-rich embedded button handling library that supports advanced features like single-click, multi-click, long-press, combo keys, debounce processing, and more. This wrapper library only utilizes its commonly used features. For more advanced capabilities, please refer to the [easy_button official documentation](https://github.com/bobwenstudy/easy_button).

## 🚀 Quick Start

### Requirements

- C99 compatible compiler
- Embedded platform with GPIO and system clock support
- [easy_button core library](https://github.com/bobwenstudy/easy_button)

### Clone the Project and Get Dependencies

This project has integrated the easy_button core library as a Git submodule. Get the complete project (including dependencies):

```bash
# Clone project and automatically get submodules
git clone --recursive https://github.com/Sighthesia/easy_button-Application.git

# Or step by step
git clone https://github.com/Sighthesia/easy_button-Application.git
cd easy_button-Application
git submodule update --init --recursive
```

Submodule includes core files:
- `easy_button/ebtn/ebtn.h` - Core header file
- `easy_button/ebtn/ebtn.c` - Core implementation
- `easy_button/ebtn/bit_array.h` - Bit array operations

**Update submodule to latest version:**
```bash
git submodule update --remote easy_button
```

## ✅ Tested Platforms

- **STM32G030** 
- **STM32H750**   
- **CH32V203** 

## 📁 Project Structure

```
easy_button-Application/
├── ebtn_APP.c/h                    # Application layer interface and initialization
├── ebtn_HAL_Config.c/h             # Hardware Abstraction Layer (HAL)
├── ebtn_Keys_Config.c/h            # Button pin configuration and parameters
├── ebtn_Event_Callback.c/h         # Button event callback handlers
└── easy_button/                    # easy_button core library submodule
    ├── ebtn/
    │   ├── ebtn.h                  # Core header file
    │   ├── ebtn.c                  # Core implementation
    │   └── bit_array.h             # Bit array operations
    ├── example_test.c              # Test examples
    ├── example_user.c              # User interaction examples
    └── README.md                   # Core library documentation
```

## 🧭 Porting Guide

### Step 1: Adapt Hardware Abstraction Layer (HAL)

**Goal**: Implement platform-specific low-level functions

1. **Modify Header Includes**
   
   Open `ebtn_HAL_Config.h` and include appropriate GPIO and system clock header files for your platform:
   
   ```c
   // Example: STM32F1 series
   #include "stm32f1xx_hal.h"
   
   // Example: CH32V series  
   #include "ch32v20x.h"
   ```

2. **Implement Core Callback Functions**
   
   In `ebtn_HAL_Config.c`, implement two key callback functions:
   
   ```c
   // Read logic level of specified pin
   uint8_t ebtn_HAL_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
   {
       return (uint8_t)HAL_GPIO_ReadPin(GPIOx, GPIO_Pin); // STM32 HAL
   }
   
   // Get current system tick count (milliseconds)
   uint32_t ebtn_HAL_Get_Tick(void)
   {
       return HAL_GetTick(); // STM32 HAL
   }
   ```

### Step 2: Configure Button Settings (Adaptation Layer)

**Goal**: Define hardware pin mappings and button behavior

1. **Define Button IDs**
   
   In `ebtn_Keys_Config.h`, define button IDs:
   
   ```c
   typedef enum
   {
       KEY_1 = 0,
       KEY_2,
       KEY_3,
       KEY_4,
       // Add more buttons...
       KEYS_COUNT // Total number of buttons
   } key_enum_t;
   ```

2. **Configure Button Hardware Mapping**
   
   In `ebtn_Keys_Config.c`, fill the `keys_config_list[]` array:
   
   ```c
   key_config_t keys_config_list[] = {
       {KEY_1, GPIOA, GPIO_PIN_0, EBTN_ACTIVE_LOW},  // PA0, active low
       {KEY_2, GPIOA, GPIO_PIN_1, EBTN_ACTIVE_HIGH}, // PA1, active high
       {KEY_3, GPIOB, GPIO_PIN_2, EBTN_ACTIVE_LOW},  // PB2, active low
       // Add more button configurations...
   };
   ```

3. **Adjust Timing Parameters** (Optional)
   
   Modify the following macro definitions as needed:
   
   ```c
   #define DEBOUNCE_TIME 20                // Debounce time (milliseconds)
   #define CLICK_AND_PRESS_MAX_TIME 200    // Long press threshold (milliseconds)
   #define KEEPALIVE_TIME_PERIOD 500       // Long press period (milliseconds)
   #define MAX_CLICK_COUNT 3               // Maximum click count
   ```

4. **Configure Combo Keys** (Optional)
   
   If combo keys are needed, add to `combo_keys_config_list[]` array:
   
   ```c
   const combo_config_t combo_keys_config_list[] = {
       COMBO_KEYS(COMBO_KEY_1, KEY_1, KEY_2),        // Key1 + Key2
       COMBO_KEYS(COMBO_KEY_2, KEY_1, KEY_3, KEY_4), // Key1 + Key3 + Key4
   };
   ```

### Step 3: Implement Event Callbacks (Application Layer)

**Goal**: Define custom handling logic for button events

In `ebtn_Event_Callback.c`, find the `ebtn_Event_Callback()` function and implement corresponding handling logic based on button ID and event type:

```c
void ebtn_Event_Callback(struct ebtn_btn *btn, ebtn_evt_t evt)
{
    switch (btn->key_id)
    {
        case KEY_1:
            if (evt == EBTN_EVT_ONPRESS)
            {
                // Key1 press handling
            }
            else if (evt == EBTN_EVT_ONRELEASE)
            {
                // Key1 release handling
            }
            else if (evt == EBTN_EVT_ONCLICK)
            {
                if (btn->click_cnt == 1)
                {
                    // Single click handling
                }
                else if (btn->click_cnt == 2)
                {
                    // Double click handling
                }
            }
            else if (evt == EBTN_EVT_KEEPALIVE)
            {
                if (btn->keepalive_cnt == 1)
                {
                    // First long press period handling
                }
            }
            break;
            
        case KEY_2:
            // Key2 handling logic...
            break;
            
        case COMBO_KEY_1:
            // Combo key1 handling logic...
            break;
            
        default:
            break;
    }
}
```

**Event Types**:
- `EBTN_EVT_ONPRESS` - Button press event
- `EBTN_EVT_ONRELEASE` - Button release event  
- `EBTN_EVT_ONCLICK` - Single/multi-click event (differentiated by `ebtn->click_cnt`)
- `EBTN_EVT_KEEPALIVE` - Long press keep-alive event (counted by `ebtn->keepalive_cnt`)

### Step 4: Integrate into Main Program (Application Layer)

**Goal**: Initialize button module and periodically process button states

1. **Call in System Initialization**:
   
   ```c
   #include "ebtn_APP.h" // Include header

   int main(void)
   {
       // System initialization...
       
       ebtn_APP_Keys_Init(); // Initialize button module
       
       while (1)
       {
           ebtn_APP_Process(); // Process button events periodically (recommended 5-20ms)
           
           // Other application logic...
           HAL_Delay(10);
       }
   }
   ```

2. **Or Call in Timer Interrupt**:
   
   ```c
   void TIM_IRQHandler(void)
   {
       if (/* Timer interrupt condition */)
       {
           ebtn_APP_Process(); // Call every 10-20ms
       }
   }
   ```

## 🔧 API Reference

### Core APIs

```c
void ebtn_APP_Keys_Init(void);    // Initialize button module
void ebtn_APP_Process(void);      // Process button events (call periodically)
```

### Advanced Queries (via easy_button core library APIs)

For additional query functionality, you can directly use APIs provided by the easy_button core library:

```c
// Get button instance by key ID
ebtn_btn_t *btn = ebtn_get_btn_by_key_id(KEY_1);

// Check if button is in active state
int is_active = ebtn_is_btn_active(btn);

// Check if button is in processing state
int in_process = ebtn_is_btn_in_process(btn);

// Check if any button is in processing (for low power)
int any_in_process = ebtn_is_in_process();
```

**Note**: Include the header file `#include "ebtn.h"` before using core library APIs

## ❓ FAQ

### Q: How to add a new button?
A: Add a new `KEY_X` enum value in `ebtn_Keys_Config.h`, then update the `keys_config_list[]` array configuration in `ebtn_Keys_Config.c`.

### Q: How to port to different MCU platforms?
A: Simply modify the implementation of low-level functions (like `GPIO_ReadPin`, `SysTick`) in `ebtn_HAL_Config.c/h`. No changes required in other files.

### Q: How to customize event handling?
A: Implement your own handler functions in `ebtn_Event_Callback.c` and call them in `ebtn_Event_Callback()` based on button ID and event type.

### Q: Compilation error about missing easy_button files?
A: Ensure you have correctly retrieved the submodules. Run `git submodule update --init --recursive` to get the easy_button core library files.

### Q: How to adjust debounce time?
A: Modify the `DEBOUNCE_TIME` macro definition in `ebtn_Keys_Config.h`, unit is milliseconds.

### Q: How to update easy_button core library to latest version?
A: Run `git submodule update --remote easy_button` to update the submodule to the latest version.

## 🎯 Feature Support

- ✅ **Single/Multi-click Detection** - Supports consecutive click detection
- ✅ **Long Press Detection** - Supports multi-level long press (via `keepalive_cnt`)
- ✅ **Combo Key Support** - Supports multi-button combinations
- ✅ **Debounce Processing** - Hardware-level debounce with configurable timing
- ✅ **Low Power Support** - Provides sleep state detection interface
- ✅ **Cross-platform Porting** - Hardware abstraction layer design for easy porting

## 🛠️ Advanced Configuration

### Custom Button Parameters

If certain buttons need special timing parameters, use special configuration in `ebtn_Keys_Config.c`:

```c
// Define special parameters
static ebtn_btn_param_t long_press_params = EBTN_PARAMS_INIT(
    20,    // Debounce time
    0,     // Release debounce time
    20,    // Minimum press time
    100,   // Maximum short press time
    200,   // Multi-click interval
    1000,  // Long press period (1 second)
    5      // Maximum click count
);

// Apply special parameters
const special_key_list_t special_keys_list[] = {
    KEY_SPECIAL_CONFIG(KEY_1, long_press_params),
};
```

### Low Power Mode

Use `ebtn_is_in_process()` to check if it's safe to enter deep sleep:

```c
if (!ebtn_is_in_process())
{
    // Safe to enter deep sleep mode
    HAL_PWR_EnterSTOPMode();
}
```

## ❤️ Credits

- **Core Library**: [bobwenstudy/easy_button](https://github.com/bobwenstudy/easy_button)
- **Design Inspiration**: [FlexibleButton](https://github.com/murphyzhao/FlexibleButton), [MultiButton](https://github.com/0x1abin/MultiButton), [lwbtn](https://github.com/MaJerle/lwbtn)

## 📚 More Resources

- [Easy Button Core Library Documentation](https://github.com/bobwenstudy/easy_button/blob/main/README.md)
- [Example Code and Test Cases](easy_button/example_test.c)
- [Porting Reference Guide](easy_button/example_user.c)

If you have any questions or suggestions, feel free to open an [Issue](https://github.com/Sighthesia/easy_button-Application/issues) or submit a [Pull Request](https://github.com/Sighthesia/easy_button-Application/pulls)!

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**Third-party Licenses**: The [easy_button core library](https://github.com/bobwenstudy/easy_button) used in this project is licensed under the Apache-2.0 License.

---

🤖 ☝️🤓 **Developed with GitHub Copilot assistance**