# ♟ Chess — CLI Chess Engine

A fully functional two-player chess game that runs entirely in the terminal, written from scratch in **C++20**.

## Features

- Two-player hot-seat gameplay (shared keyboard)
- ASCII board rendering with rank/file labels
- Move input via UCI-style algebraic notation (`e2e4`, `g1f3`)
- Full move validation for all piece types
- Special moves: castling, en passant, pawn promotion
- Check, checkmate, and stalemate detection

## Getting Started

### Prerequisites

- **g++** with C++20 support (GCC 10+ recommended)
- **make** (`mingw32-make` on Windows)

### Build & Run

```bash
# Clone the repo
git clone https://github.com/CosmicIon/Chess.git
cd Chess

# Build
make            # Linux / macOS
mingw32-make    # Windows (MinGW)

# Run
./chess         # Linux / macOS
.\chess.exe     # Windows
```

### Clean

```bash
make clean          # Linux / macOS
mingw32-make clean  # Windows
```

### Troubleshooting: `unrecognized command line option '-std=c++20'`

This error means your `g++` is too old (typically GCC 6.x or earlier). You need **GCC 10+** for C++20 support.

**Windows fix — Install a modern g++ via MSYS2:**

1. Install MSYS2:
   ```powershell
   winget install --id MSYS2.MSYS2
   ```
2. Install the latest GCC toolchain:
   ```powershell
   C:\msys64\usr\bin\bash.exe -lc "pacman -S --noconfirm mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make"
   ```
3. Add `C:\msys64\ucrt64\bin` to the **front** of your system PATH:
   ```powershell
   [System.Environment]::SetEnvironmentVariable("Path", "C:\msys64\ucrt64\bin;" + [System.Environment]::GetEnvironmentVariable("Path", "User"), "User")
   ```
4. **Restart your terminal / VS Code** so the new PATH takes effect.
5. Verify:
   ```powershell
   g++ --version   # Should show GCC 10+ (e.g., 15.2.0)
   ```

> **Note:** If you still see the old version after updating PATH, ensure the old MinGW directory (e.g., `C:\MinGW\bin`) is either removed from your PATH or placed **after** `C:\msys64\ucrt64\bin`.

**Linux fix:**
```bash
sudo apt update && sudo apt install g++    # Ubuntu/Debian
sudo dnf install gcc-c++                   # Fedora
sudo pacman -S gcc                         # Arch Linux
```

**macOS fix:**
```bash
brew install gcc
```

## How to Play

1. The board is displayed after each move with White at the bottom.
2. Enter moves in UCI format — source square + destination square:
   - `e2e4` — move piece from e2 to e4
   - `g1f3` — move knight from g1 to f3
   - `e7e8q` — promote pawn to queen
3. The game alternates turns between White and Black.
4. Invalid or illegal moves are rejected with an error message.

### Piece Symbols

| Piece  | White | Black |
|--------|:-----:|:-----:|
| King   |  `K`  |  `k`  |
| Queen  |  `Q`  |  `q`  |
| Rook   |  `R`  |  `r`  |
| Bishop |  `B`  |  `b`  |
| Knight |  `N`  |  `n`  |
| Pawn   |  `P`  |  `p`  |

## Project Structure

```
Chess/
├── src/            # Source files (.cpp)
├── include/        # Header files (.h)
├── build/          # Compiled object files (generated)
├── Makefile        # Build configuration
├── todo.md         # Development checklist
└── README.md
```

## Tech Stack

- **Language:** C++20
- **Compiler:** g++ (GCC 15.2.0 / MSYS2 UCRT64)
- **Build System:** GNU Make

## License

This project is for educational purposes.