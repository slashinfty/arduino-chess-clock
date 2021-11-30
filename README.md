# Flagged
A simple chess clock driven by an Arduino Nano with TM1637 4-digit 7-segment displays.

Note: requires the Arduino library `Grove_4Digital_Display`.

## Functionality

Allows time up to 99 minutes and 59 seconds. Allows either bonus (added at the end of each turn) or delay (doesn't start countdown for a set time), both up to 5 minutes. Each player can have times set individually.

Starts up with 10 minutes for both players and no bonus/delay. Setup buttons are for +5, +1, -1, -5, and enter. It starts with the left player's minutes, then seconds, then the right player's minutes, then seconds, then the left player's bonus/delay time in seconds, then the right player's bonus/delay time in seconds, then whether it is bonus or delay.

When ready to start, press a player's button to start the timer for the other player. During this, the enter button functions as a pause button, and the increment/decrement buttons have no function. When one timer reaches 0, the program stops running, and the timer needs to be restarted to start again.

## Repository Organization
- `clock/` contains the Arduino code
- `diylc/` contains the DIY Layout Creator files (schematic & stripboard)
- `images/` contains all images for the README
- `prints/` contains the STL files for the case

## Bill of Materials
- 1x Arduino Nano
- 2x TM1637 4-digit displays
- 1x 9V battery connector
- 9x 1K resistors
- 2x LEDs
- 7x momentary push buttons
- 1x SPST switch (optional - on/off switch)

## Schematic
![Schematic](images/schematic.png)

## Case Design
Designed in Tinkercad, sliced with Cura, and printed in PLA+ on a CR-10 Mini.

Uses tactile switch buttons and keyboard switches, along with a 9V battery snap connector.
