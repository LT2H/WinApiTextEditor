# WinApi Text Editor
A basic text editor built with the Windows API and C++20.
![test](https://github.com/user-attachments/assets/afe02826-8b85-43fe-835b-66580c0285dc)
# Features
**File Operations**
- Create New Window
- Create New File
- Open Existing File
- Save
- Save As
- Prompt to Save Before Exiting

**Edit Operations**
- Cut, Copy, and Paste
- Undo and Redo
- Select All
- Find
  - Match Whole Word
  - Match Case
  - Direction (Up/Down)
- Replace/Replace All
  - Match Whole Word
  - Match Case

**Hotkeys**
  - Displayed Next to Controls

## Technical Details
  - Language: C++
  - Standard: C++20
  - Dependencies: WinApi
  - Build System: [Premake5](https://premake.github.io)
  - Template: This project is based on [TheCherno/ProjectTemplate](https://github.com/TheCherno/ProjectTemplate)

## Getting Started
1. Clone this repository:
    ```sh
    git clone https://github.com/LT2H/WinApiTextEditor.git
   
2. Open the `Scripts` directory and run `Setup-Window.bat`. This script uses Premake5 inside the `Vendor/Binaries/Premake` directory to generate a `.sln` file. By default, it is configured for Visual Studio 2022 on Windows.
   ```sh
   cd WinApiTextEditor/Scripts && Vendor/Binaries/Premake/Setup-Window.bat

## License
- This repository is licensed under UNLICENSE (see UNLICENSE.txt for details).
- Premake is licensed under BSD 3-Clause (see included LICENSE.txt file for more details)
