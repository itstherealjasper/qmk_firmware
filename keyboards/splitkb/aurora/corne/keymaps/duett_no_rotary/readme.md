# Aurora Corne's Debug Keymap

To make debugging your build as easy as possible, we have provided a special debugging keymap. It is not intended to actually type on, it is just here to make sure that your hardware is working correctly.

## Keys

![Keys](https://i.imgur.com/y5zWjsZh.png)

The left side uses lowercase letters, the right side uses uppercase ones.

## Encoders

Encoders output a number of 0 or 1, depending on the installed position.
These correspond to the index used for custom encoder code.

The number is followed by either a `+` or a `-`, depending on the direction turned.

## LEDs

Both underglow and per-key RGB should be fading between red and off.

## OLEDs

Both the primary and secondary side should be filled with characters.


## Installation
atmega:
 1. QMK MSYS: `qmk compile -kb splitkb/aurora/corne -km duett_no_rotary`
 2. QMK Toolbox select .HEX file
 3. Set MCU to ATmega32U4
 4. Check Auto-Flash
 5. Hit reset on the controller