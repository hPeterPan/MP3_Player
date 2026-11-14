# MP3_Player

MP3 Player build using Arduino nano

## Overview

This project is my first electronics build, I wanted to build something that relates to something I enjoy (music) and something that will be useful to an extent.

## Goal

Built to learn the basics of electronics like circuitry, soldering, debugging and test automation. I hope to be able to get the soldering down pat so that I can assemble it on a small enough PCB board to be handheld.

It should be able to turn on and off, display the track count on the display, I can plug in headphones and when i press play it will begin playing the track. When i want to skip a track i should be able to select next track without having to pause the track. I want to be able to navigate the display to change the volume of the audio play back. The MP3 Player should be able to function without having to be plugged in by using the battery that is connected to the charging module, and the charging module should be able to recharge the battery.

## Parts

### Main Components

| **Part**                            | **Qty** | **Purpose**                                              | **Notes** |
| ------------------------------- | --- | ---------------------------------------------------- | ----- |
| Arduino Nano                    | 1   | Main controller, used for speaking with the DFPlayer |       |
| DFPlayer Mini MP3 Module        | 1   | Audio playback module                                |       |
| Micro SD card                   | 1   | Holds the songs and inserts into the DFPlayer        |       |
| 1.3" OLED Display (SH1106) | 1   | Display for songs and controls                       |       |
| TP4056 Charging Module          | 1   | Charge the battery pack and supply power to build    |       |
| 3.7V Rechargeable Battery       | 1   | supply power to build                                |       |
| 3.5mm Audio jack                | 1   | Allow headphones for audio playback                  |       |
| JST-PH 2.0 Male Connector Cable | 1   | Connect battery to charging module                   |       |
| Push Buttons                    | 3   | Navigating the display, play/pause, volume up/down   |       |
| SPDT mini switch                | 1   | Turning power supply on/off                          |       |
| MT3068 Boost Converter          | 1   | Boost voltage to power Arduino properly              |       |

### Other supplies needed

1k Ohm Resistors\
10uF Capacitors\
PCB Board\
Soldering iron

## Diagrams and Photos

**Schematic:** ![Schematic](C:\Users\Hunter\OneDrive\Documents\MP3 Player.pdf)

# Build Phase

## Phase 1: Navigation Buttons
 
**Objective:** Wire three push buttons to the Arduino Nano and print a line in the serial monitor each time a button is pressed.
 
**New parts:** Arduino Nano (classic), 3 push buttons, breadboard and jumper wires.
 
**Wiring:**
 
| Button | Nano pin |
|---|---|
| Prev | D2 |
| Select | D3 |
| Next | D4 |
 
Each button connects its Nano pin to GND. [If you also used external 1k pull-up resistors and 100 nF capacitors on the breadboard, say so here. Otherwise delete this note.]
 
**How it works:**
- All three pins use `INPUT_PULLUP`, so the Nano's internal pull-up resistor holds each pin HIGH when the button is not pressed. This removes the need for external pull-up resistors.
- Pressing a button connects the pin to ground, so it reads LOW. This is "active low": LOW means pressed.
- The sketch compares each pin's current reading to its previous reading. A change from HIGH to LOW counts as one press, and a line is printed to the serial monitor, for example `Select Button Pressed`.
**Serial monitor screenshot:** ![Phase 1 serial output](C:\Users\Hunter\OneDrive\Pictures\Screenshots\Serial Monitor.png)
 
**Code:** [Sketch_MP3_Player.ino](C:\Users\Hunter\OneDrive\Documents\Arduino\Sketch_MP3_Player\Sketch_MP3_Player.ino)
 
**Expected result:** Nothing prints while the buttons are untouched. One line prints per press, naming the button.
 
**Actual result:** A print statement prints in the Serial Monitor each time a button is pressed.
 
**Problems and fixes:**
- **Problem:** On startup, the serial monitor printed a press for all three buttons, even though nothing had been touched.
- **Cause:** The sketch assumed every button started HIGH. If a pin read LOW for an instant at power-up, the sketch saw a HIGH-to-LOW change and reported a press that never happened. One button (Prev) was also set to plain `INPUT` instead of `INPUT_PULLUP`.
- **Fix:** Set all three pins to `INPUT_PULLUP`, wait about 200 ms in `setup()` for the pins to settle, then read the real state of each pin as the starting value.
 
**Lessons learned:**
- Buttons wired to ground read LOW when pressed, which is the opposite of what you might expect.
- Initialize "previous state" variables from the real pin readings, not from an assumption.
- When to use a resistor and why you would use one.
---
 
## Phase 2: OLED Display (SH1106, SPI)
 
**Objective:** Wire a 1.3" SH1106 OLED display to the Nano over SPI and show a message on it. Then continue from Phase 1 so that pressing a button shows its name on the display instead of in the serial monitor.
 
**New parts:** 1.3" SH1106 OLED display module (7-pin, SPI version).
 
**Wiring:**
 
| OLED pin | Nano pin |
|---|---|
| CLK  | D13 |
| MOSI | D11 |
| RES | A0 |
| DC | A1 |
| CS | A2 |
| VCC | 5V |
| GND | GND |
 
On the Nano, hardware SPI uses fixed pins: the clock is on D13 and the data line is on D11. RES, DC, and CS can be any free pins, and the sketch just has to match the wiring.
 
**Library and setup:** The sketch uses the U8g2 library with the hardware SPI constructor for this display:
 
```cpp
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 13, 11, A2, A1, A0);
```
 
**How it works:**
- First test: draw a short message on the display to confirm it works.
- Then combined with Phase 1: each time a button is pressed, the display clears and rewrites the button's name in the same place.
**Photo:** ![Phase 2 wiring]
**Photo of the working display:** ![Phase 2 display](C:\Users\Hunter\OneDrive\Pictures\Phase2_Display.jpeg)
 
**Code:** [Sketch_MP3_Player_OLED.ino](C:\Users\Hunter\OneDrive\Documents\Arduino\Sketch_MP3_Player_OLED\Sketch_MP3_Player_OLED.ino)
 
**Expected result:** The message appears on the display, and pressing a button updates it.
 
**Actual result:** The screen remains blank until a button is pressed and does not clear the screen until a button is pressed again.
 
**Problems and fixes:**
- **Problem:** The display stayed blank after uploading. The Nano's L LED was blinking.
- **What the LED told me:** On the Nano, the L LED is connected to D13, which is also the SPI clock pin. Blinking meant the Nano was running the code and sending data to the display, so the problem was on the display side (wiring, pin numbers, or display configuration).
- **Checks done:** Confirmed the pins in the code matched the pins on the wires, and confirmed the display's SPI/I2C selection resistor was in the SPI position.
- **Cause:** The CLK and MOSI wires were swapped. The module labels these pins D0 and D1, which is easy to mix up.
- **Fix:** Swapped the two wires so CLK goes to D13 and MOSI goes to D11. The display worked right away.
 
**Lessons learned:**
- Check wires against the labels printed on the module, not against pin position, since the order differs between vendors.
- A blinking L LED during SPI use means the clock line is active, which helps separate software problems from wiring problems.
- Hardware SPI only works on fixed pins; software SPI is a useful test to isolate whether the pin wiring is the issue.
- Analog pins will give you longer delay than Digital pins, I can switch the Reset, Data, and Chip Select pins to Digital down the line if I want faster responses in commands.
---
 
## Phase 3: Navigate on the Display
 
**Objective:** Use the three buttons to move through a menu on the display.
 
[To be written.]
 
---
 
## Phase 4: Turn on/off arduino with Switch

**Objective:** Manipulate power to Nano by adding switch to circuit.
 
[To be written.]

# Test Plan

# Key Takeaways
