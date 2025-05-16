[中文](README_CN.md) [English](README.md)

## 📌 Description

This is a basic key detection application using [easy_button](https://github.com/bobwenstudy/easy_button ), a powerful embedded button management library. The design incorporates hardware abstraction, decoupling the application layer, hardware abstraction layer (HAL), and adaptation layer to achieve high portability across different platforms.

## 🚀 Quick Porting Guide

Quickly adapt this key detection module to various hardware platforms.

- ✅ Already tested on STM32G030,STM32H750,CH32V203

> ⚠️ **Note:** This project does not include the official `easy_button` library files. Please download the latest version (`ebtn.h`, `ebtn.c`, `bit_array.h`) from [easy_button](https://github.com/bobwenstudy/easy_button ) to ensure proper functionality.

## 📁 File Structure
```
easy_button_app/
├── ebtn_app.c/h // Application layer interface and initialization
├── ebtn_custom_hal.c/h // Hardware Abstraction Layer (HAL)
├── ebtn_custom_config.c/h // Button pin configuration and parameters
├── ebtn_custom_callback.c/h // Callback handler for button events
```

## 🧭 Porting Steps

### 1. Adapt the Hardware Abstraction Layer (HAL)

**Goal:** Implement platform-specific low-level functions.

- Open `ebtn_custom_hal.h` and include the appropriate GPIO and system clock header files for your platform (e.g., `stm32f1xx_hal.h` for STM32).
- In `ebtn_custom_hal.c`, implement the following two core callback functions:
  - `ebtn_HAL_Read_Pin()`: Reads the current logic level of the specified pin.
  - `ebtn_HAL_Get_Tick()`: Returns the current system tick count in milliseconds.

---

### 2. Configure Button Settings (Adaptation Layer)

**Goal:** Define hardware pin mappings and button behavior.

- In `ebtn_custom_config.h`, define button IDs such as `KEY_1`, `KEY_2`, etc.
- Fill the `key_list[]` array in `ebtn_custom_config.c` with each button's corresponding GPIO port, pin number, and active level (0 = low, 1 = high).
- Modify the following macros according to your requirements:
  - `DEBOUNCE_TICKS`: Debounce time in ms.
  - `LONG_PRESS_TICKS`: Long press detection threshold.
  - `REPEAT_TICKS`: Repeat interval for auto-repeat keys.
  - Other optional settings...
- If using combo keys, add them to `btn_combo_array[]`, and call `ebtn_combo_btn_add_btn()` inside `ebtn_APP_Key_INIT()` in `ebtn_app.c` to bind individual buttons to the combo.
- Add single buttons to `btn_array[]`.

---

### 3. Implement Event Callbacks (Application Layer)

**Goal:** Define custom logic for handling button events.

- Locate the `ebtn_Event_Handler()` function in `ebtn_custom_callback.c`.
- Based on the incoming button ID and event type (e.g., pressed, released, long press), invoke the corresponding handler function.
- It is recommended to split the logic for different buttons or events into separate functions.
- Refer to the original `switch(ebtn->key)` structure inside `ebtn_Event_Handler()` and call the respective handler within each `case` block for better code readability and maintainability.
- You may implement custom responses like UI updates or task scheduling.

---

### 4. Call Key Processing Functions (Application Layer)

**Goal:** Initialize and periodically process button states.

- In your main function, call `ebtn_APP_Key_INIT()` during system initialization to initialize the button module.
- Periodically call `ebtn_APP_Key_Process()` in your main loop or timer interrupt (recommended every 5~20ms).
- To query button status, use the following helper functions:
  - `ebtn_APP_Is_Key_Active(KEY_X)`: Checks if a button is currently active.
  - `ebtn_APP_Get_Key_State(KEY_X)`: Gets the current state of a button.
  - `ebtn_APP_Get_Key_Press_Time(KEY_X)`: Gets how long a button has been pressed.

---

## ❓ FAQ

### Q: How to add a new button?

A: Add a new `KEY_X` enum value in `ebtn_custom_config.h`, then update `key_list[]` and `btn_array[]` in `ebtn_custom_config.c` accordingly.

### Q: How to port to a different MCU platform?

A: Simply modify the implementation of low-level functions (e.g., `GPIO_ReadPin`, `SysTick`) in `ebtn_custom_hal.c/h`. No changes are required in other files.

### Q: How to customize event handling?

A: Implement your own handler functions in `ebtn_custom_callback.c`, and invoke them inside `ebtn_Event_Handler()` based on the button ID and event type.

---

## ❤ Credit

- [easy_button](https://github.com/bobwenstudy/easy_button )

## 📚 References

- Detailed usage examples are provided in comments at the top of each `.c/.h` file.

---

If you have any questions or suggestions, feel free to open an Issue or submit a Pull Request!
