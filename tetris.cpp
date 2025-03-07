#include <iostream>
#include <fstream>  
#include <conio.h>  
#include <windows.h>  
#include <ctime>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

char board[HEIGHT][WIDTH];  

int tetrominoes[7][4] = {  
    1,3,5,7,  
    2,4,5,7,  
    3,5,4,6,  
    3,5,4,7,  
    2,3,5,7,  
    3,5,7,6,  
    2,3,4,5   
};

struct Point {
    int x, y;
} a[4], b[4];

bool gameOver = false;
int currentPiece, color = 1;
int score = 0;
int highScore = 0;

// Function to read high score from file
void loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        if (file.peek() == EOF) {  // Check if file is empty
            highScore = 0;
        } else {
            file >> highScore;
            if (file.fail()) highScore = 0;  // If invalid data, reset to 0
        }
        file.close();
    } else {
        highScore = 0;  // If file doesn't exist, set high score to 0
    }
}

// Function to save high score
void saveHighScore() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

// Prevents flickering by hiding cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Moves the console cursor without clearing the screen
void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Sets color for blocks
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Checks if a move is valid
bool check() {
    for (int i = 0; i < 4; i++) {
        if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT || board[a[i].y][a[i].x] != ' ')
            return false;
    }
    return true;
}

// Draws the board without flickering
void drawBoard() {
    gotoXY(0, 0);
    cout << "🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱\n";
    for (int i = 0; i < HEIGHT; i++) {
        cout << "🧱";
        for (int j = 0; j < WIDTH; j++) {
            bool isPiece = false;
            for (int k = 0; k < 4; k++) {
                if (a[k].x == j && a[k].y == i) {
                    setColor(color);
                    cout << "██";  
                    setColor(7);
                    isPiece = true;
                    break;
                }
            }
            if (!isPiece) {
                if (board[i][j] == ' ') {
                    cout << "  ";  
                } else {
                    setColor(board[i][j] - '0');
                    cout << "██";  
                    setColor(7);
                }
            }
        }
        cout << "🧱\n";
    }
    cout << "🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱\n";
    cout << "Score: " << score << "  High Score: " << highScore << endl;
}

// Removes full lines
void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] != ' ') count++;
        }
        if (count == WIDTH) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 0; j < WIDTH; j++) board[0][j] = ' ';
            score += 10;
            if (score > highScore) {
                highScore = score;
                saveHighScore();
            }
            i++;
        }
    }
}

// Spawns a new piece
void newPiece() {
    currentPiece = rand() % 7;
    color = 1 + rand() % 6;
    for (int i = 0; i < 4; i++) {
        a[i].x = tetrominoes[currentPiece][i] % 2 + WIDTH / 2 - 1;
        a[i].y = tetrominoes[currentPiece][i] / 2;
    }
    if (!check()) gameOver = true;
}

// Moves the piece
void movePiece(int dx, bool rotate) {
    for (int i = 0; i < 4; i++) b[i] = a[i];

    for (int i = 0; i < 4; i++) a[i].x += dx;
    if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

    if (rotate) {
        Point p = a[1];
        for (int i = 0; i < 4; i++) {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
    }
}

// Drops the piece down one step
void dropPiece() {
    for (int i = 0; i < 4; i++) b[i] = a[i];

    for (int i = 0; i < 4; i++) a[i].y += 1;
    if (!check()) {
        for (int i = 0; i < 4; i++) board[b[i].y][b[i].x] = color + '0';
        clearLines();
        newPiece();
    }
}

// Hard drop (instantly drops piece)
void hardDrop() {
    while (check()) {
        for (int i = 0; i < 4; i++) a[i].y += 1;
    }
    for (int i = 0; i < 4; i++) a[i] = b[i]; 
    dropPiece();
}

// Handles user input
void handleInput() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 27) gameOver = true;
        if (key == 'a') movePiece(-1, false);
        if (key == 'd') movePiece(1, false);
        if (key == 'w') movePiece(0, true);
        if (key == 's') dropPiece();
        if (key == ' ') hardDrop();
    }
}

// Game loop
void gameLoop() {
    system("chcp 65001 > nul");  
    hideCursor();
    srand(time(0));

    loadHighScore();
    system("cls");  

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            board[i][j] = ' ';

    newPiece();

    while (!gameOver) {
        drawBoard();
        handleInput();
        dropPiece();
        Sleep(300);
    }

    cout << "\nGame Over! Final Score: " << score << endl;
}

int main() {
    gameLoop();
    return 0;
}