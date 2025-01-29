# AX8052 SDCC Project

This project demonstrates programming for the Axsem AX8052 microcontroller using SDCC (Small Device C Compiler) within Visual Studio Code with EIDE (Embedded IDE).

## Prerequisites

- Visual Studio Code
- EIDE Extension
- SDCC Compiler
- AX8052 SDK

## Project Setup

1. Install EIDE in VS Code
2. Create new SDCC project
3. Configure project settings for AX8052
4. Add SDK include paths

## Building

the ide needs fixing, so a tool was made to get the right SDCC config.

```bash
# Inside .\tools\
.\fix-ide.exe "C:\Users\Oscar\.vscode-insiders\" sdcc.model.json 
```

```bash
# Build using EIDE
1. Open Command Palette (Ctrl+Shift+P)
2. Select "EIDE: Build Project"


## Hardware Configuration

- MCU: AX8052
- Clock: XX MHz
- Power: 3.3V

## Project Structure

```
├── src/
│   ├── main.c
│   └── config.h
├── include/
└── build/
```

## License

MIT

## References

- [SDCC Manual](http://sdcc.sourceforge.net/doc/sdccman.pdf)
- [AX8052 Datasheet](https://www.axsem.com)