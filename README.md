# Taksh's Macropad

This is a custom 4-key macropad featuring an inverted-T arrow key layout, a 0.91" OLED display, and a fully 3D-printable sandwich-mount case. It is powered by a Seeeduino XIAO RP2040 and runs on custom QMK firmware.

## Features:
- Structural 3D-printed sandwich-mount enclosure (Bottom Case + Top Plate).
- 128x32 OLED Display.
- 4 mechanical switches arranged in a standard inverted-T layout.
- Direct-pin GPIO routing for maximum response time.
- Custom interactive QMK firmware that reacts to keystrokes!

## CAD Model:
The enclosure is a rigid sandwich-mount design. The 1.6mm PCB is safely housed inside a 13mm thick bottom cavity. A 3mm top plate sits flush on the 10mm outer margins, and the entire assembly is clamped together using four M3 bolts in the extreme corners. It features a side cutout for the XIAO USB-C cable.

<img src="assets/case_assembly.png" alt="Case Assembly" width="500"/>


<img src="assets/overall_view.png" alt="Overall View" width="500"/>

## PCB
The PCB was routed in KiCad using the Hack Club Care Package libraries. Because it is only a 4-key pad, the switches are routed directly to the RP2040 GPIO pins rather than using a diode matrix, keeping the board clean and simple.

**Schematic**
<img src="assets/schematic.png" alt="Schematic" width="400"/>


**PCB Layout**
<img src="assets/pcb.png" alt="PCB" width="400"/>
*(Note: Replace with a screenshot of your KiCad PCB layout)*

## Firmware Overview
This board runs on a custom [QMK](https://qmk.fm/) firmware configuration built specifically for the RP2040. 

- The 4 keys are bound to standard Arrow Keys (`KC_UP`, `KC_DOWN`, `KC_LEFT`, `KC_RIGHT`).
- The OLED display features a custom C script that renders a sleeping ASCII face. When an arrow key is pressed, a hardware listener intercepts the keystroke and wakes the face up, causing it to look in the direction of the arrow key you pressed!

## BOM (Bill of Materials):
Here is everything required to assemble this macropad:

**Electronics:**
- 1x Seeeduino XIAO RP2040
- 1x 0.91" 128x32 I2C OLED Display
- 4x Cherry MX-compatible Mechanical Switches
- 4x Mechanical Keycaps (DSA or OEM profile)

**Hardware & Enclosure:**
- 1x 3D Printed Bottom Case
- 1x 3D Printed Top Plate
- 4x M3 Bolts (for clamping the Top Plate to the Bottom Case)
- 4x M3 Nuts (if not threading directly into the plastic)