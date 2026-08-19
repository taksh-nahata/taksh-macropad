# Nexus-4 (my first piece of hardware)

Okay, okay, okay. Let me introduce you to Nexus-4, a custom 4-key macropad. It features an inverted-T arrow key layout, a 128x32 OLED display, and a 3D-printed sandwich-mount case. So I run the the software of this on a Seeed Studio XIAO RP2040 that runs my custom QMK firmware. I've even made some simple ASCII art animations(currently very simple tho)!

---

## Completed Build & Demo

<p align="center">
  <img src="assets/final_build_1.jpg" alt="Finished Nexus-4 Top View" width="48%" />
  <img src="assets/final_build_2.jpg" alt="Finished Nexus-4 Angle View" width="48%" />
  <img src="assets/final_build_colored.jpg" alt="Built and colored Nexus-4 Top View" width="50%">
</p>

### Video Demonstration
[Watch the Nexus-4 in action](https://drive.google.com/file/d/1Elsz5yWcckBbZZuh22iVLzsOhnGGIkVX/view?usp=sharing)

---

## Some Features
* **Custom 3D-Printed Enclosure:** So basically, I made a two-piece sandwich-mount case (Top Plate + Bottom Case) which are connected together using screws at the corner.
* **Interactive OLED Animation:** I've got a 0.91" 128x32 I2C OLED display at the top middle of the macropad, which shows ASCII animations that I made, and they react to your keystrokes.

---

## Hardware & CAD Design

The cadded box I made for the macropad is a sandwich-mount structure, and I made it on Fusion 360. The PCB rests inside this enclosure, and it is topped by the Top Plate, which is secured using screws at the four corners. I've also made a side cutout in the Bottom Case, to give access to the RP2040's USB-C connector.

<p align="center">
  <img src="assets/case_assembly.png" alt="Case Assembly" width="48%" />
  <img src="assets/overall_view.png" alt="Overall View" width="48%" />
</p>

---

## PCB & Schematic

I made the PCB in KiCad completely. I used direct-pin connections to simplify the overall layout and also reduce the number of components I need.

* **Microcontroller:** Seeed Studio XIAO RP2040
* **Display Interface:** I2C (SDA on `GP6`, SCL on `GP7`)
* **Switch Routing:**
  * **Up Switch (SW1):** `GP2` (Pin D8)
  * **Left Switch (SW2):** `GP3` (Pin D10)
  * **Down Switch (SW3):** `GP4` (Pin D9)
  * **Right Switch (SW4):** `GP1` (Pin D7)

<p align="center">
  <img src="assets/schematic.png" alt="Schematic" width="48%" />
  <img src="assets/pcb.png" alt="PCB Layout" width="48%" />
</p>

---

## Firmware & OLED Logic

The firmware is compiled with QMK for the RP2040 (`promicro_rp2040` target).

Layout:
* `KC_UP` (Up Arrow)
* `KC_LEFT` (Left Arrow)
* `KC_DOWN` (Down Arrow)
* `KC_RIGHT` (Right Arrow)

* **Keymaps:** This is pretty standard and straight forward. It's just mapped to standard navigation keys (`KC_UP`, `KC_LEFT`, `KC_DOWN`, `KC_RIGHT`).
* **OLED Engine:** The OLED screen shows an inverted (because the OLED is positioned the wrong way on the PCB), and centered ASCII text and animation. When there are no keys being pressed, there is a simple breathing sleep animation (`zZz`) and this cycles continuously. Pressing any key triggers `process_record_user()` to update the active expression in the direction of input (`owo`, `>_<`, `o_o`, `-w-`).

---

## Bill of Materials (BOM)

This does not include all tools I used to build this. Only the components which are directly on the macropad. To view a full list of materials, you can view the BOM file I've attached to this repo.

| Category | Component | Quantity |
| :--- | :--- | :--- |
| **Electronics** | Seeed Studio XIAO RP2040 | 1 |
| **Electronics** | 0.91" 128x32 I2C OLED Display | 1 |
| **Electronics** | Cherry MX-Compatible Switches | 4 |
| **Electronics** | Custom 2-Layer PCB | 1 |
| **Hardware** | 3D-Printed Top Plate | 1 |
| **Hardware** | 3D-Printed Bottom Case | 1 |
| **Hardware** | M4 (or M3) Screws & Nuts | 4 |
| **Keycaps** | 1u Keycaps | 4 |

---

## How can you make this?

1. **Surface-Mount the microchip:** Start by soldering the RP2040 chip directly, flat to the PCB pads, using its castellated edges. This is to ensure that the chip is not raised any more than necessary to give enough spaces for the pins of the switches.
2. **Mount the OLED:** Remove the plastic collar from the 4 pin header and then solder the bare pins between the PCB and the OLED. You will need to solder both sides, on the back side of the PCB and on top of the OLED, to ensure the connection is secure.
3. **Mount the Switches:** Fit the switches perfectly into the holes from the top of the Top Plate (you will hear a click), and then you can align the PCB with the pins of the switches. Once perfectly aligned and all pins are somewhat through the holes of the PCB, you can solder them all to the PCB. Feed 2-3 mm of solder for this.
4. **Enclosure Assembly:** You're basically done! Just drop the PCB assembly into the bottom case and then secure the sandwich using four corner bolts and nuts.
5. **Flash Firmware:**
   * Enter bootloader mode by holding the **Boot** key or grounding `GP26` (`D0`) on startup to mount the `RPI-RP2` drive.
   * Compile and copy the `.uf2` file:
     ```bash
     qmk compile -kb taksh_macropad -km default
     ```
   * Drag and drop `Nexus-4_default` into `RPI-RP2`.