#include <stdio.h>
#include <stdlib.h>
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   // For Sleep()

// Define game board size
#define WIDTH 40
#define HEIGHT 20

// Global variables
int x, y;               // Snake head position
int fruitX, fruitY;     // Fruit position
int score;              // Player score
int tailX[100], tailY[100]; // Tail coordinates
int nTail;              // Tail length

// Directions
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

// Function to set up the initial game state
void Setup() {
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    dir = STOP;
    nTail = 0;
}

// Function to draw the game board
void Draw() {
    system("cls"); // Clear the screen (Windows only)

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O"); // Snake head
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruit
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Snake tail
                        print = 1;
                        break;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\nScore: %d\n", score);
}

// Function to handle user input
void Input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 0 || ch == 224) {
            // Arrow keys
            switch (_getch()) {
            case 72: dir = UP; break;    // Up arrow
            case 80: dir = DOWN; break;  // Down arrow
            case 75: dir = LEFT; break;  // Left arrow
            case 77: dir = RIGHT; break; // Right arrow
            }
        } else {
            // WASD keys
            switch (ch) {
            case 'w': case 'W': dir = UP; break;
            case 's': case 'S': dir = DOWN; break;
            case 'a': case 'A': dir = LEFT; break;
            case 'd': case 'D': dir = RIGHT; break;
            case 'x': case 'X': exit(0); break;
            }
        }
    }
}

// Function to update game logic
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    }

    // Collision with wall
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        printf("\nGame Over! You hit a wall.\n");
        system("pause");
        exit(0);
    }

    // Collision with tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            printf("\nGame Over! You hit your tail.\n");
            system("pause");
            exit(0);
        }
    }

    // Eat fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

// Main function
int main() {
    Setup();
    while (1) {
        Draw();
        Input();
        Logic();
        Sleep(100); // 100ms delay
    }
    return 0;
}
