
# Simple 3D visualizations in embedded systems.

Uses ATMega328p MCU and SSD1306 OLED display.


## Requirements

- make
- avr-gcc
- avr-libc
- avrdude

## Build

Clone the repository:

```bash
  git clone --recurse-submodules https://github.com/blr-ophon/Atividade_TEE
```


Compile
```bash
  make
```

And Upload. Required avrdude. Uses an arduino board.
```bash
  make upload
```


# Usage

## Buttons

**PD2**: Active Low. Rotate around Z counterclockwise.  
**PD3**: Active Low. Rotate around Z clockwise. 
**PD4**: Active Low. Rotate around X clockwise. 
**PD5**: Active Low. Rotate around X counterclockwise.  
**PD6**: Active Low. Rotate around Y clockwise. 
**PD7**: Active Low. Rotate around Y counterclockwise.  
**PC1**: Active Low. Bit 0 of game select.
**PC0**: Active Low. Bit 1 of game select.

## Games

**0**: Menu
**1**: Cube
**2**: Tetrahedron
