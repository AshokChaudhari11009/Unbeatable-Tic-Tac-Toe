#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <limits>

const int SIZE = 3;
const int WINDOW_SIZE = 600;
const int CELL_SIZE = WINDOW_SIZE / SIZE;

enum Player { NONE, HUMAN, COMPUTER };

struct Move {
    int row, col;
};

Player board[SIZE][SIZE];

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = NONE;
        }
    }
}

bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == NONE) return true;
        }
    }
    return false;
}

int evaluate() {
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTER) return +10;
            else if (board[row][0] == HUMAN) return -10;
        }
    }
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTER) return +10;
            else if (board[0][col] == HUMAN) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER) return +10;
        else if (board[0][0] == HUMAN) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER) return +10;
        else if (board[0][2] == HUMAN) return -10;
    }
    return 0;
}

int minimax(int depth, bool isMax, int alpha, int beta) {
    int score = evaluate();
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = std::numeric_limits<int>::min();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == NONE) {
                    board[i][j] = COMPUTER;
                    best = std::max(best, minimax(depth + 1, !isMax, alpha, beta));
                    board[i][j] = NONE;
                    alpha = std::max(alpha, best);
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == NONE) {
                    board[i][j] = HUMAN;
                    best = std::min(best, minimax(depth + 1, !isMax, alpha, beta));
                    board[i][j] = NONE;
                    beta = std::min(beta, best);
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }
}

Move findBestMove() {
    int bestVal = std::numeric_limits<int>::min();
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == NONE) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                board[i][j] = NONE;
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void drawBoard(sf::RenderWindow &window, sf::Font &font) {
    sf::Color lineColor = sf::Color::White;

    for (int i = 1; i < SIZE; i++) {
        sf::Vertex verticalLine[] = {
            sf::Vertex(sf::Vector2f(i * CELL_SIZE, 0), lineColor),
            sf::Vertex(sf::Vector2f(i * CELL_SIZE, WINDOW_SIZE), lineColor)
        };
        window.draw(verticalLine, 2, sf::Lines);

        sf::Vertex horizontalLine[] = {
            sf::Vertex(sf::Vector2f(0, i * CELL_SIZE), lineColor),
            sf::Vertex(sf::Vector2f(WINDOW_SIZE, i * CELL_SIZE), lineColor)
        };
        window.draw(horizontalLine, 2, sf::Lines);
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == HUMAN) {
                sf::Text text("O", font, CELL_SIZE / 3);
                text.setFillColor(sf::Color::White);
                text.setPosition(j * CELL_SIZE + (CELL_SIZE / 3), i * CELL_SIZE + (CELL_SIZE / 5));
                window.draw(text);
            } else if (board[i][j] == COMPUTER) {
                sf::Text text("X", font, CELL_SIZE / 3);
                text.setFillColor(sf::Color::White);
                text.setPosition(j * CELL_SIZE + (CELL_SIZE / 3), i * CELL_SIZE + (CELL_SIZE / 5));
                window.draw(text);
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Tic Tac Toe");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    initializeBoard();
    bool playerTurn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && playerTurn) {
                int x = event.mouseButton.x / CELL_SIZE;
                int y = event.mouseButton.y / CELL_SIZE;

                if (board[y][x] == NONE) {
                    board[y][x] = HUMAN;
                    playerTurn = false;

                    if (evaluate() == 0 && isMovesLeft()) {
                        Move bestMove = findBestMove();
                        board[bestMove.row][bestMove.col] = COMPUTER;
                        playerTurn = true;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        drawBoard(window, font);
        window.display();

        if (evaluate() == 10) {
            std::cout << "Computer wins!" << std::endl;
            break;
        } else if (evaluate() == -10) {
            std::cout << "Player wins!" << std::endl;
            break;
        } else if (!isMovesLeft()) {
            std::cout << "It's a draw!" << std::endl;
            break;
        }
    }
    sf::sleep(sf::seconds(2)); // Pause for 2 seconds before closing

    return 0;
}
