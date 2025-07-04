> ⚠️ **WARNING**  
> This project has **not yet been tested on real hardware**.  
> The PCB has been designed, and the firmware is complete — but it hasn't been uploaded or verified on a physical board yet.  


# Ticklet
It is a minimalist yet feature-packed hardware timer designed for embedded systems and creative projects. Built using the Seeed Studio **XIAO RP2040**, it utilizes tactile switches, a rotary encoder, an OLED screen, and LEDs — all integrated into a compact PCB designed in KiCad.


## Features

- **Timer Functionality** with Start, Stop, Reset, and Set Time controls  
- **Rotary Encoder** to precisely adjust time in 5-second steps  
- *OLED Display (128x64)** shows live timer status and countdown  
- **LED Indicators** to show current state: idle, paused, or running  
- **Four Mechanical Buttons** for direct control  

---

## Preview

| State       | OLED Display     | LED Behavior        |
|------------|------------------|---------------------|
| Idle        | "Idle" & `00:00` | Only RED ON         |
| Set Mode    | "Set Timer"      | All LEDs OFF        |
| Running     | "Running..."     | Only GREEN ON       |
| Paused      | "Paused"         | Only BLUE ON        |

---

## How It Works

- **Button 1 (GPIO0)** → Start timer  
- **Button 2 (GPIO1)** → Stop timer  
- **Button 3 (GPIO2)** → Reset timer  
- **Button 4 (GPIO3)** → Toggle Set Mode  
- **Rotary Encoder (GPIO4 & GPIO26)** → Add/Subtract time in set mode  
- **OLED (I2C: GPIO6, GPIO7)** → Visual feedback  
- **LEDs (GPIO27, 28, 29)** → State indicators

---

## Pin Mapping

| Component           | Function        | Pin on XIAO RP2040 |
|---------------------|-----------------|---------------------|
| Button 1            | Start           | GPIO0               |
| Button 2            | Stop            | GPIO1               |
| Button 3            | Reset           | GPIO2               |
| Button 4            | Set Mode        | GPIO3               |
| Rotary CLK          | Encoder CLK     | GPIO4               |
| Rotary DT           | Encoder DT      | GPIO26              |
| OLED SDA            | I2C SDA         | GPIO6               |
| OLED SCL            | I2C SCL         | GPIO7               |
| LED 1 (RED)         | Idle Indicator  | GPIO27              |
| LED 2 (BLUE)        | Pause Indicator | GPIO28              |
| LED 3 (GREEN)       | Run Indicator   | GPIO29              |

---

## Firmware

The firmware is written in Arduino C++ using the following libraries:

- `Wire.h` (for I2C communication)
- `Adafruit_GFX.h` (OLED graphics)
- `Adafruit_SSD1306.h` (OLED driver)

👉 Located in: `Firmware/src.ino`

### ⬇️ Installation

1. Install the Arduino IDE
2. Add board support for **[Seeed XIAO RP2040](https://wiki.seeedstudio.com/XIAO-RP2040/)**
3. Install libraries:
   - `Adafruit GFX Library`
   - `Adafruit SSD1306`
4. Connect your XIAO RP2040 via USB-C
5. Upload `src.ino`

---

## PCB Design

- Created using **KiCad 7**
- All symbols and footprints are open source or from KiCad libraries.
- You’ll find:
  - `Kicad files.kicad_pcb` — PCB layout
  - `Kicad files.kicad_sch` — Schematic
  - `Resources/Symbols` — Custom symbols like OLED

---

## Screenshots

**Schematics**
<br>
![Schematics](<Screenshots/Schematics.png>)
<br>

**PCB**
<br>
![PCB](<Screenshots/PCB.png>)
<br>

**3D Front View**
<br>
![3D-Front](<Screenshots/3D-Front.png>)
<br>

**3D Back View**
<br>
![3D-Back](<Screenshots/3D-Back.png>)
<br>

## License

This project is open-source under the [MIT License](LICENSE).  
Feel free to fork, remix, or use it in your own creations!

---

## Author

Bhavika Nagdeo (Cracking Bytes)  
- [GitHub](https://github.com/cracking-bytes)  
- [LinkedIn](https://in.linkedin.com/in/bhavikanagdeo)  
- [Instagram](https://www.instagram.com/cracking.bytes/)  
- [Medium](https://crackingbytes.medium.com/)

## Feedback

If you have any feedback, ideas, or features to suggest, reach out at **bhavikanagdeo83@gmail.com**
