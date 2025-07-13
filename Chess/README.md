# Chess Project – Part 4

## Overview

This project is a command-line chess engine implemented in C++. It includes support for all core gameplay mechanics, including:

- Standard chess rules
- Player vs Player mode
- Player vs Computer mode with multithreaded move evaluation
- Check, checkmate, and stalemate detection
- Castling for both sides
- Draw handling (50-move rule, insufficient material)
- Pawn promotion

## Features Implemented in Part 4

- ✅ Checkmate detection
- ✅ Castling (kingside and queenside)
- ✅ Draw conditions
- ✅ Working computer opponent using multi-threaded evaluation
- ✅ Full game loop with move parsing and legality checks

## How to Run

1. Open terminal and navigate to the `Chess/` directory.
2. Create the build directory if not already:
   ```bash
   mkdir build
   cd build
   cmake ..
   ninja
