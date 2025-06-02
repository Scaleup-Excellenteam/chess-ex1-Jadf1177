# Chess Move Evaluator

## Overview
This project implements a chess move evaluator using a depth-based evaluation algorithm.  
In this version (Part 3), the evaluator also uses **multithreading** to speed up move calculations by running them in parallel.

## Algorithm Explanation
The move evaluator uses a depth-first search approach to explore potential moves up to a specified depth:

- **Depth 0:** Evaluates only the immediate moves.
- **Depth 1:** Considers the opponent's responses to each immediate move.
- **Depth 2:** Looks ahead to the player's responses to the opponent's responses.

### Move Evaluation Criteria
- **Piece Values:** Each chess piece is assigned a value (e.g., Pawns = 1, Knights = 3).
- **Board Control:** Extra points for controlling center squares.
- **Threats and Safety:** Dangerous moves are penalized.
- **Check and Checkmate:** Moves that lead to checkmate are rewarded.

### Complexity
As the depth increases, the number of move combinations grows quickly:
- Depth 0: `O(n)`
- Depth 1: `O(n^2)`
- Depth 2: `O(n^3)`

Where `n` is the number of possible moves on the board.

---

## Multithreading (Part 3)

To improve performance, this version adds a thread pool that splits the work between multiple threads.

- Each thread takes a piece (usually white, if it’s white’s turn) and evaluates its possible moves.
- All the results go into a shared `PriorityQueue`.
- A mutex protects the queue so that only one thread can write to it at a time (to avoid race conditions).
- This allows move evaluation to happen in parallel and reduces total runtime.

---

## Performance Benchmark

We tested the program with different thread counts and measured the time it takes to evaluate moves:

| Threads | Example Time |
|---------|---------------|
| 1       | ~2000 ms      |
| 2       | ~1200 ms      |
| 4       | ~800 ms       |
| 8       | ~700 ms       |

> The numbers above are rough and may vary based on the machine and game state.

---

## Bonus (Not Implemented)

The code could be further improved by stopping all threads early if one finds a move with a very high score (above a certain threshold).  
This is not implemented in this version.

---

## Build Instructions

To compile and run:

```bash
mkdir build
cd build
cmake ..
ninja
./Chess
