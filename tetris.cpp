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
    {1, 3, 5, 7}, // I
    {2, 4, 5, 7}, // S
    {3, 5, 4, 6}, // Z
    {3, 5, 4, 7}, // T
    {2, 3, 5, 7}, // L
    {3, 5, 7, 6}, // J
    {2, 3, 4, 5}  // O
};

int tetrominoColors[7] = {9, 10, 12, 13, 14, 11, 15};
class userGuide {
    public:
        static void showGuideMenu() {
            system("cls");
        
            cout << "\033[1;34m===== RULES =====\033[0m\n";
            cout << "- Blocks (Tetrominoes) fall from the top.\n";
            cout << "- Arrange them to form complete horizontal lines.\n";
            cout << "- A complete line clears and earns points.\n";
            cout << "- The game ends when blocks stack to the top.\n\n";
        
            cout << "\033[1;32m===== CONTROLS =====\033[0m\n";
            cout << "Left Arrow  : Move Left\n";
            cout << "Right Arrow : Move Right\n";
            cout << "Up Arrow    : Rotate\n";
            cout << "Down Arrow  : Soft Drop\n";
            cout << "Space bar   : Hard Drop\n";
            cout << "ESC         : Pause\n\n";
        
            cout << "\033[1;33m===== SCORING METHODS =====\033[0m\n";
            cout << "- Clearing 1 line  : 100 points\n";
            cout << "- Clearing 2 lines : 300 points\n";
            cout << "- Clearing 3 lines : 500 points\n";
            cout << "- Clearing 4 lines (Tetris) : 800 points\n";
        
            cout << "Press any key to start...";
            _getch();
            system("cls");
        }
        
    };

struct Point {
    int x, y;
} a[4], b[4];

bool gameOver = false;
int currentPiece, color;
int score = 0;
int highScore = 0;

void loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        highScore = 0;
    }
}

void saveHighScore() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, false};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoXY(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool check() {
    for (int i = 0; i < 4; i++) {
        if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT || board[a[i].y][a[i].x] != ' ')
            return false;
    }
    return true;
}

void drawBoard() {
    gotoXY(0, 0);
    for (int i = 0; i < HEIGHT; i++) {
        cout << "💠,";
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
                    setColor(0);
                    cout << "⬛";
                    setColor(7);
                } else {
                    setColor(board[i][j] - '0');
                    cout << "██";
                    setColor(7);
                }
            }
        }
        
        cout << "💠,\n";
    }
    cout << " ═══════════════════════════  \n";
    if(score>=highScore){
        cout<< "🥳🥳🥳🥳🥳 𝓦 𝓞 𝓞 𝓗 𝓞 𝓞 🥳🥳🥳🥳 "<< endl;
        cout<<"You have break your highscore"<<"\n" <<  endl;
        cout<<" 👹👹👹 🆃 🅴 🆁 🆁 🅸 🅵 🅸 🅲   🅿 🅻 🅰 🆈 🅴 🆁 👹👹👹"<< endl;
    }
    cout << "Score: " << score << "  High Score: " << highScore << endl;
    cout << "Controls: ← Move | → Move | ↑ Rotate | ↓ Soft Drop | SPACE Hard Drop | ESC Exit\n";
}

void clearLines() {
    int linesCleared = 0;

    for (int i = HEIGHT - 1; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] != ' ') count++;
        }

        if (count == WIDTH) {  
            linesCleared++;

          
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }

           
            for (int j = 0; j < WIDTH; j++) {
                board[0][j] = ' ';
            }

            i++; 
        }
    }

    if (linesCleared == 1) {
        score += 100;
    } else if (linesCleared == 2) {
        score += 300;
    } else if (linesCleared == 3) {
        score += 500;
    } else if (linesCleared == 4) {
        score += 800;
        cout << "\n🎉 TETRIS! 4 LINES CLEARED! 🎉\n";
    }

    if (score > highScore) {
        highScore = score;
        saveHighScore();
    }
}


void newPiece() {
    currentPiece = rand() % 7;
    color = tetrominoColors[currentPiece];
    for (int i = 0; i < 4; i++) {
        a[i].x = (tetrominoes[currentPiece][i] % 2) + WIDTH / 2 - 1;
        a[i].y = tetrominoes[currentPiece][i] / 2;
    }
    if (!check()) gameOver = true;
}
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
void hardDrop() {
    while (check()) {
        for (int i = 0; i < 4; i++) a[i].y += 1;
    }
    for (int i = 0; i < 4; i++) a[i].y -= 1;
}

void dropPiece() {
    for (int i = 0; i < 4; i++) b[i] = a[i];
    for (int i = 0; i < 4; i++) a[i].y += 1;
    if (!check()) {
        for (int i = 0; i < 4; i++) board[b[i].y][b[i].x] = color + '0';
        clearLines();
        newPiece();
    }
}

void handleInput() {
    if (_kbhit()) {
        int key = _getch();
        if (key == 27) {  
            gameOver = true;
        } else if (key == 224) { 
            key = _getch();
            if (key == 75) movePiece(-1, false);  
            if (key == 77) movePiece(1, false);   
            if (key == 72) movePiece(0, true);    
            if (key == 80) dropPiece();           
        } else if (key == 32) {  
            hardDrop();
        }
    }
}

void gameLoop() {
    system("chcp 65001 > nul");
    hideCursor();
    srand(time(0));
    loadHighScore();
    userGuide::showGuideMenu();
    while (true) {
        score = 0;
        gameOver = false;
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

        cout << "\n 💀💀💀💀 🅶 🅰 🅼 🅴  🅾 🆅 🅴 🆁 💀💀💀💀"<<"\n"<<" Final Score: " <<  score << endl;
        cout << "Play Again? (Y/N): ";
        char choice;
        cin >> choice;
        if (choice != 'Y' && choice != 'y') break;
    }

    cout << "\nThanks for playing!\n";
}

int main() {
    gameLoop();
    return 0;
}
