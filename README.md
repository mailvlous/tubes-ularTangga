# Ular Tangga (Snakes and Ladders) Game

This project is a C-based implementation of the classic board game "Ular Tangga" (Snakes and Ladders).

---

## Features

- **Classic Gameplay**: Implements the traditional rules of Snakes and Ladders.
- **High Score Tracking**: Records and displays the top players.
- **Save and Load Game**: Players can save progress and resume later.
- **Customizable Board**: Pre-defined board logic for gameplay.

---

## Table of Contents

1. [Features](#features)
2. [Getting Started](#getting-started)
    - [System Requirements](#system-requirements)
    - [Installing a C Compiler](#installing-a-c-compiler)
    - [Setting up Visual Studio Code](#setting-up-visual-studio-code)
3. [Installation](#installation)
4. [Running the Game](#running-the-game)
5. [Project Structure](#project-structure)
6. [Contributing](#contributing)
7. [License](#license)
8. [Acknowledgments](#acknowledgments)

---

## Getting Started

This guide will help you set up the project on your machine, including configuring your development environment to work with C in Visual Studio Code.

### System Requirements

- Operating System: Windows, macOS, or Linux
- A C compiler (e.g., GCC)
- Visual Studio Code (VS Code)

---

### Installing a C Compiler

#### Windows (MinGW):

1. Download MinGW from [MinGW-w64](https://sourceforge.net/projects/mingw/).
2. Install MinGW and include the `bin` directory in your system's PATH:
   - Open System Properties > Environment Variables.
   - Find `Path` under System Variables and click `Edit`.
   - Add the path to your MinGW `bin` folder (e.g., `C:\MinGW\bin`).
3. Verify installation by running the following in a terminal:
   ```bash
   gcc --version
   ```
   You should see the GCC version.

#### Linux:

Install GCC using your package manager:
```bash
sudo apt update
sudo apt install build-essential
```

#### macOS:

Install the Command Line Tools:
```bash
xcode-select --install
```

---

### Setting up Visual Studio Code

1. **Download and Install VS Code**:
   - Download VS Code from the official website: [https://code.visualstudio.com/](https://code.visualstudio.com/).

2. **Install Extensions**:
   - Open VS Code.
   - Go to Extensions (Ctrl+Shift+X or Cmd+Shift+X).
   - Search for and install:
     - `C/C++` (by Microsoft) for syntax highlighting and IntelliSense.
     - `Code Runner` (optional) for running code directly in VS Code.

3. **Set Up C Compiler**:
   Follow these steps to configure VS Code to compile and run C programs:
   
   - **Step 1: Install a Compiler**
     - Ensure you have a compiler installed as described above.
   
   - **Step 2: Configure Build Task**
     - Open your project in VS Code.
     - Create a `.vscode` folder in the root directory (if it doesn't already exist).
     - Inside `.vscode`, create or update `tasks.json` with the following:
       ```json
       {
         "version": "2.0.0",
         "tasks": [
           {
             "label": "Build C Program",
             "type": "shell",
             "command": "gcc",
             "args": [
               "-g",
               "-o",
               "ularTangga",
               "main.c",
               "board.c",
               "game.c",
               "highscore.c",
               "saveFile.c",
               "-I."
             ],
             "group": {
               "kind": "build",
               "isDefault": true
             }
           }
         ]
       }
       ```

   - **Step 3: Configure Debugging**
     - Inside the `.vscode` folder, create or update `launch.json` with the following:
       ```json
       {
         "version": "0.2.0",
         "configurations": [
           {
             "name": "Debug C Program",
             "type": "cppdbg",
             "request": "launch",
             "program": "${workspaceFolder}/ularTangga",
             "args": [],
             "stopAtEntry": false,
             "cwd": "${workspaceFolder}",
             "environment": [],
             "externalConsole": true,
             "MIMode": "gdb",
             "setupCommands": [
               {
                 "description": "Enable pretty-printing for gdb",
                 "text": "-enable-pretty-printing",
                 "ignoreFailures": true
               }
             ],
             "preLaunchTask": "Build C Program"
           }
         ]
       }
       ```

   - **Step 4: Run and Debug**
     - Use `Ctrl+Shift+B` (Windows/Linux) or `Cmd+Shift+B` (macOS) to build the project.
     - Press `F5` to start debugging.

---

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/mailvlous/tubes-ularTangga.git
   ```
2. **Navigate to the Project Directory**:
   ```bash
   cd tubes-ularTangga
   ```
3. **Open in VS Code**:
   ```bash
   code .
   ```

---

## Running the Game

### Using Visual Studio Code

1. **Build the Project**:
   - Press `Ctrl+Shift+B` (Windows/Linux) or `Cmd+Shift+B` (macOS) to run the build task.
2. **Run the Game**:
   - Open a terminal in VS Code and execute:
     ```bash
     ./ularTangga
     ```

### Using Command Line

1. Compile the project manually:
   ```bash
   gcc -g -o ularTangga main.c board.c game.c highscore.c saveFile.c -I.
   ```
2. Run the game:
   ```bash
   ./ularTangga
   ```

---

## Project Structure

- `main.c`: Entry point of the game.
- `board.c`: Handles board logic, including snakes and ladders placement.
- `game.c`: Controls game mechanics like dice rolls and player turns.
- `highscore.c`: Manages high score recording and retrieval.
- `saveFile.c`: Implements save and load functionality.
- `types.h`: Contains type definitions and shared data structures.

---

## Contributing

We welcome contributions! If you have suggestions for improvements or new features:

1. Fork the repository.
2. Create a feature branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add feature-name"
   ```
4. Push to your fork:
   ```bash
   git push origin feature-name
   ```
5. Submit a pull request.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

## Acknowledgments

- Inspired by the traditional board game "Ular Tangga" (Snakes and Ladders).
- Developed as part of a learning exercise in C programming.

