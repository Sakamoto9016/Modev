# **Mo**dev
*This document was written on July 23rd, 2026. For **Mo**dev version 0.0.x(Succulent) and ups.*

---

## Introduction
**Mobile** Development or **Mo**dev, it's an open-source project that was made by **Andrew Dexembre**.

Modev aims to make developing mobile devices based on SoC microcontrollers easier. You can write a single program, and any device running Modev can execute it.

## Functions
[API Reference](function/a0.md)
(under construction.)


## Diagnostics
### 1. Power on self-test
#### 1.1 Information

After the display, memory, and other essential hardware have been initialized, **Mo**dev performs a Power-On Self-Test (POST). After POST, it should show a splash screen. If the splash screen does not appear, check whether the debug LED or the display backlight is blinking. The blinking pattern indicates the POST error code.

Normally, it would blink in a specific pattern that represents an error code. For example:

``Long-short-short-short``

Long delay represents 1 and short delay represents 0. Which is referred to:

``1000``

The blink code is transmitted least significant bit first (LSB-first). So now it's:

``0001``

And that also refers to error code 0x1 during POST.
#### 1.2 References
Here are some error code and its meanings:
<br>0x0: Undefined error.
<br>0x1: Failed to allocate PSRAM for screen buffer.
<br>0x2: Failed to initalize screen.