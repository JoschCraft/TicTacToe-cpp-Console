# 🎮 Tic-Tac-Toe Console Game

A sleek, lightweight, and interactive command-line Tic-Tac-Toe game written in modern C++. This project features a robust local 2-player mode as well as an engaging single-player mode driven by an intelligent, predictive AI opponent.

---

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B11%20%2F%20C%2B%2B14%20%2F%20C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++ Version" />
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-333333?style=for-the-badge&logo=platform" alt="Platforms" />
  <img src="https://img.shields.io/badge/License-MIT-4fc08d?style=for-the-badge" alt="License" />
</p>

---

## 📌 Table of Contents
* [Features](#-features)
* [Code Improvements (v2.0)](#%EF%B8%8F-code-improvements-v20)
* [Getting Started](#-getting-started)
* [How to Play](#-how-to-play)
* [Roadmap](#-roadmap)

---

## ✨ Features

* **🤖 Smart AI Opponent:** A custom lookahead logic designed to challenge the player. The AI evaluates the board state in real-time, prioritizes securing its own win, blocks your potential winning moves on the next turn, and falls back to a smart random distribution if no instant wins are available.
* **👥 Local Multiplayer:** Play locally with a friend on the same keyboard in classic turn-based "X" vs "O" action.
* **📊 Persistent Scoreboard:** Track total rounds played, individual player wins, and draws across game sessions.
* **🛡️ Input Validation:** Hardened user interface checking bounds and ensuring players cannot input illegal board coordinates.
* **⚡ Modern Pseudorandom Numbers:** Built using robust standard library `<random>` features (`std::mt19937` engine powered by hardware entropy `std::random_device`) rather than old, biased `rand()` implementations.


---

## 🚀 Getting Started

### Prerequisites
A compiler supporting modern C++ (C++11 or higher) such as `g++`, `clang`, or MSVC.

### Installation & Compilation

1. **Clone or Download:** Save `main.cpp` to your local machine.
2. **Compile using GCC/Clang:**
   * **Windows (MinGW):**
     ```bash
     g++ -std=c++11 main.cpp -o tictactoe.exe
     tictactoe.exe
     ```
   * **Linux / macOS:**
     ```bash
     g++ -std=c++11 main.cpp -o tictactoe
     ./tictactoe
     ```

*Note on Clear Screen:* The project utilizes native system commands to clear the console (`system("cls")`). If compiling on Unix-like operating systems (Linux/macOS), you can toggle the system command comment in `clearScreen()` to target `"clear"`.

---

## 🎮 How to Play

1. Run the application to launch the interactive main menu.
2. Input your selection: `1` for Single Player (vs AI), `2` for Multiplayer, or `3` to Exit.
3. The grid represents standard matrix coordinates mapping to a 3x3 array.
4. When prompted, type your desired move as `[row] [column]` (separated by a space) and hit **Enter**.

#### Coordinate Grid Mapping:
```text
         Column 1    Column 2    Column 3
Row 1  |  (1 1)   |   (1 2)  |   (1 3)  |
       ----------------------------------
Row 2  |  (2 1)   |   (2 2)  |   (2 3)  |
       ----------------------------------
Row 3  |  (3 1)   |   (3 2)  |   (3 3)  |
```

*Example:* To claim the top-right corner, enter `1 3`.

---

## 📈 Roadmap

Future enhancements planned to scale this project:
* **🏗️ Object-Oriented Refactoring (OOP):** Encapsulate variables into clean modular classes (e.g., `Board`, `Player`, `GameEngine`) to completely strip away global variables.
* **🛡️ Fail-Safe Stream Handling:** Intercept non-integer character entries (e.g., entering "abc" as coordinates) using `std::cin.clear()` and `std::cin.ignore()` to robustly avoid terminal stream loops.
* **🧠 Minimax AI:** Upgrade the decision tree to implement the standard recursive Minimax algorithm, crafting an unbeatable AI opponent.

---

*Happy Coding & Have Fun playing!* 🚀
