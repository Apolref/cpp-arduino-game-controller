# Hardware Notes

This folder is intended for hardware-related resources:

- Controller layout sketches
- Wiring diagrams (buttons → Arduino pins)
- 3D models (STL files) for the controller case
- Links to external resources (e.g., Thingiverse models)

## Example Setup

- Base board: Arduino Uno or Arduino Nano
- Buttons:
  - 4 directional buttons (UP, DOWN, LEFT, RIGHT)
  - 2 action buttons (A, B)
- Wiring:
  - Each button connected between an Arduino digital pin and GND
  - The corresponding pin configured as `INPUT_PULLUP` in the firmware

You can use open designs for Arduino game controllers as inspiration or starting point,
and adapt them to your own layout and number of buttons.
