# SrtToContinuityListConverter

A desktop tool that converts `.srt` subtitle files into `.docx` continuity lists — 
documents used in film/TV production to catalogue dialogue by character.

## Features
- Parses SRT subtitle files and extracts dialogue per character
- Detects pause intervals between lines (configurable thresholds)
- Lets you assign gender to each character (affects formatting in the output doc)
- Exports to `.docx` with customizable female-line styling (bold/italic/underline)

## Requirements
- Qt 6.x
- C++11

## Build (Linux)
```bash
sudo apt install qt6-base-dev qt6-tools-dev qt6-tools-dev-tools libqt6xml6
git clone https://github.com/kei91/SrtToContinuityListConverter.git
cd SrtToContinuityListConverter
qmake6 SrtToContinuityListConverter.pro
make
./SrtToContinuityListConverter
```

## Build (Windows)
Open `SrtToContinuityListConverter.pro` in Qt Creator and build with MSVC or MinGW.

## Usage
1. Open the app and browse for an `.srt` file
2. The character list is populated automatically — click the gender column to toggle M/F
3. Set the output `.docx` path and click Export

<img width="544" height="635" alt="preview" src="https://github.com/user-attachments/assets/4a0ec7ce-c5d0-414e-9ff5-e24455233d91" />

