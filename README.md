# Unbeatable Tic-Tac-Toe:

Welcome to the Unbeatable Tic-Tac-Toe game, where you can test your skills against an AI opponent that never loses!

## Prerequisites

- SFML library

# Usage

### Start the game
Run the executable file.

### Human turn
Click on an empty cell to place your move (O).

### Computer turn
The computer will automatically place its move (X).

### End game
The game ends when either the human or computer wins, or if the board is full (draw).

## The Unbeatable AI: Minimax Algorithm with Alpha-Beta Pruning

### Minimax Algorithm

The Minimax algorithm is a decision-making algorithm used in turn-based games. It simulates all possible moves in a game, creates a game tree, and determines the best move for a player assuming the opponent is also playing optimally. The goal is to minimize the possible loss for a worst-case scenario. Hence, the algorithm minimizes the possible loss for the maximum possible gain.

In our Tic-Tac-Toe game, the AI uses the Minimax algorithm to evaluate all possible game states and choose the move that leads to the highest chance of winning.

### Alpha-Beta Pruning

To make the Minimax algorithm more efficient, we use a technique called alpha-beta pruning. This technique eliminates branches in the game tree that don't need to be explored because they won't influence the final decision. It keeps track of two values, alpha and beta:

- **Alpha**: The best value that the maximizer (AI) can guarantee.
- **Beta**: The best value that the minimizer (human) can guarantee.

As the algorithm searches through the game tree, it updates alpha and beta values and prunes branches where:

- The current move is worse than previously examined moves for the maximizer.
- The current move is worse than previously examined moves for the minimizer.

This significantly reduces the number of nodes evaluated by the Minimax algorithm, making it more efficient without compromising the outcome.

## Code Structure

- **main.cpp**: Contains the main game logic, including initialization, rendering, and event handling.
- **Minimax Algorithm**: Implemented within the `minimax` and `findBestMove` functions to determine the best move for the computer.
- **SFML Rendering**: Utilizes SFML for drawing the game board and handling user input.

