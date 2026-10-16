# 🎮 Tic-Tac-Toe Console Game

A lightweight, interactive Tic-Tac-Toe game written in C++. Play against a custom rule-based AI, challenge a friend locally, or let two AI players compete in automated simulations.

The AI combines tactical rules with weighted random move selection. It aims to recognize immediate wins, block immediate threats, and create or prevent forks while keeping games varied rather than relying on a perfect-play algorithm.

---

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B11%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++11 or newer" />
  <img src="https://img.shields.io/badge/Interface-Console-333333?style=for-the-badge" alt="Console interface" />
  <img src="https://img.shields.io/badge/Game%20Modes-3-7C3AED?style=for-the-badge" alt="Three game modes" />
</p>

---

## 📌 Table of Contents

- [Features](#-features)
- [How the AI Works](#-how-the-ai-works)
- [Game Modes](#-game-modes)
- [Getting Started](#-getting-started)
- [How to Play](#-how-to-play)
- [Scoreboard and Simulations](#-scoreboard-and-simulations)
- [Roadmap](#-roadmap)

---

## ✨ Features

- **🤖 Custom AI Opponent:** A self-developed, rule-based AI that checks for immediate wins, blocks immediate opponent wins, and looks for opportunities to create or prevent forks.
- **🎲 Varied Move Selection:** When no higher-priority tactical rule selects a move, the AI uses weighted random selection to favor the center, corners, and edges.
- **👥 Local Multiplayer:** Play with another person on the same computer.
- **🔄 AI vs. AI Simulation:** Run a chosen number of games and observe the results of the AI playing against itself.
- **📊 In-Session Scoreboard:** Tracks the total number of games, wins for X and O, draws, and the AI's fork-related counters during the current program session.
- **✅ Basic Move Validation:** Checks that entered coordinates are within the 3×3 board and that the selected square is empty.
- **🎲 Standard C++ Randomization:** Uses `<random>`, `std::mt19937`, and `std::uniform_int_distribution` for random-number generation.

---

## 🧠 How the AI Works

The AI uses a priority-based decision system. It evaluates tactical opportunities before falling back to a strategic random move.

1. **Win immediately** — Take a move that completes a winning line.
2. **Block an immediate win** — Prevent the opponent from completing a winning line on the next move.
3. **Create a fork** — Look for a move that creates multiple potential winning moves.
4. **Prevent a fork** — Check candidate moves that may stop the opponent from creating a fork.
5. **Choose a weighted random move** — If no previous rule selects a move, favor strategically important positions while retaining variety.

### Weighted Random Moves

When all nine squares are available, the fallback move selection uses these probabilities:

| Position | Probability |
| --- | ---: |
| Center | 44.4% |
| Corners (combined) | 33.3% |
| Edges (combined) | 22.2% |

These percentages describe the initial selection when all board positions are free. As squares become occupied, the actual distribution changes because the AI only selects available positions.

The AI is **not designed to guarantee perfect play**. The goal is to combine useful tactical rules with variation, rather than making every game follow the same sequence of moves. Fork recognition and prevention are heuristic rules and are not guaranteed to handle every possible board position correctly.

---

## 🎮 Game Modes

Choose a mode from the main menu:

1. **Single Player (You vs. AI)** — The AI plays as **X** and starts; the human player uses **O**.
2. **Multiplayer (X vs. O)** — Two human players take turns, with **X** starting.
3. **Simulate AI (AI vs. AI)** — Enter the number of rounds to simulate. The program records wins and draws across the simulated games.
4. **Exit** — Close the game.

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler that supports C++11 or newer, such as GCC, Clang, or MSVC.
- A terminal or console.

### Compile

Save the source code as `main.cpp` and compile it with GCC or MinGW:

**Windows (MinGW):**

```bash
g++ -std=c++11 main.cpp -o tictactoe.exe
```

**Linux / macOS:**

```bash
g++ -std=c++11 main.cpp -o tictactoe
```

### Run

**Windows:**

```powershell
.\tictactoe.exe
```

**Linux / macOS:**

```bash
./tictactoe
```

### Console clearing

The current `clearScreen()` implementation uses `system("cls")`, which is intended for Windows. To use the program on Linux or macOS, change the command to `system("clear")` in `clearScreen()`.

---

## 🎯 How to Play

1. Start the program to open the main menu.
2. Select a game mode by entering its number.
3. When prompted for a move, enter the row and column separated by a space, for example `1 3`.
4. Rows and columns are numbered from **1 to 3**.
5. The first player to complete a horizontal, vertical, or diagonal line wins. If the board fills without a winner, the game is a draw.

### Coordinate Grid

```text
          Column 1    Column 2    Column 3
Row 1  |   (1 1)   |   (1 2)   |   (1 3)   |
       -------------------------------------
Row 2  |   (2 1)   |   (2 2)   |   (2 3)   |
       -------------------------------------
Row 3  |   (3 1)   |   (3 2)   |   (3 3)   |
```

Example: To select the top-right square, enter `1 3`.

---

## 📈 Scoreboard and Simulations

The scoreboard displays:

- Total rounds played during the current program session
- Wins by player X
- Wins by player O
- Draws
- Forks prevented by the AI (counter)
- Forks created by the AI (counter)

AI-vs-AI simulations can help compare changes to the decision-making rules over many games. Results depend on the random move selection and the order in which the AI players take turns. The counters provide useful observations, but they are not by themselves a formal measure of AI strength.

---

## 🛠️ Roadmap

Possible future improvements include:

- **🧪 More Automated Testing:** Test tactical situations such as immediate wins, forced blocks, forks, and multiple threats.
- **🛡️ Stronger Input Handling:** Handle non-numeric input safely and prevent input-stream errors from causing repeated prompts.
- **🧠 Improved Fork Handling:** Make fork detection and prevention more reliable across different board positions.
- **🎯 More Strategic Choices:** Compare several safe moves before selecting one, while preserving variation between good options.
- **🖥️ Cross-Platform Console Support:** Improve console-clearing behavior for Windows, Linux, and macOS.

---

*Built as a personal C++ learning project. Happy coding and have fun playing!* 🚀
