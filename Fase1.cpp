#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

const int CONSOLE_WIDTH = 120;
const int CONSOLE_HEIGHT = 30;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

 /* void saveToFile(const string& filename, const string& data) {
   // ofstream file(filename);
    if (file.is_open()) {
        file << data;
        file.close();
        cout << "Figura guardada en '" << filename << "'" << endl;
    } else {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }
}

 string loadFromFile(const string& filename) {
    string content;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo para leer." << endl;
    }
    return content;
} */

void clearLine(int line) {
    gotoxy(0, line);
    cout << string(CONSOLE_WIDTH, ' ');
}

void clearInputPrompt() {
    clearLine(28);
    gotoxy(0, 28);
}

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printMenu() {
    gotoxy(0, 1);
    cout << "wasd para moverse | F12: para seleccionar posicion | F8: Nuevo Caracter | F9: Reset | F10: Color | G: guardar | 0: Salir";
    gotoxy(0, 2);
}

void clearMenu() {
    clearLine(0);
    clearLine(30);
}

int main() {
    int x = CONSOLE_WIDTH / 2;
    int y = CONSOLE_HEIGHT / 2;
    char drawChar = '.';
    int color = 7;

    printMenu();

    bool positionSelected = false;

    while (true) {
        if (!positionSelected) {
            if (_kbhit()) {
                char key = _getch();

                if (key == 0 || key == -32) {
                    key = _getch();
                    if (key == -122) {
                        positionSelected = true;
                    } else if (key == 66) {
                        gotoxy(0, 28);
                        cout << "Ingrese nuevo caracter: ";
                        cin >> drawChar;
                        clearInputPrompt();
                        gotoxy(x, y);
                    } else if (key == 67) {
                        system("cls");
                        printMenu();
                        gotoxy(x, y);
                    } else if (key == 68) {
                        gotoxy(0, 28);
                        cout << "Ingrese el nuevo color (1: Azul | 2: Verde | 4: Rojo | 6: Amarillo | 7: Blanco | 8: Gris | 5: Morado): ";
                        cin >> color;
                        setConsoleColor(color);
                        clearInputPrompt();
                        gotoxy(x, y);
                    }
                } else {
                    switch (key) {
                        case 'w':
                            y = (y - 1 + CONSOLE_HEIGHT) % CONSOLE_HEIGHT;
                            break;
                        case 's':
                            y = (y + 1) % CONSOLE_HEIGHT;
                            break;
                        case 'a':
                            x = (x - 2 + CONSOLE_WIDTH) % CONSOLE_WIDTH;
                            break;
                        case 'd':
                            x = (x + 2) % CONSOLE_WIDTH;
                            break;
                        case '0':
                            cout << "Goodbye" << endl;
                            return 0;
                    }
                    gotoxy(x, y);
                }
            }
        } else {
            gotoxy(0, 30);
            cout << "F1: Triangulo | F2: Cuadrado | F3: Rectangulo | F4: Circulo | F5: Linea | F6: Rombo | F7: Hexagono";
            clearInputPrompt();
            if (_kbhit()) {
                int key = _getch();
                if (key == 0 || key == 224) {
                    key = _getch();
                    clearMenu();
                    switch (key) {
                        case 59: {
                            int base;
                            clearInputPrompt();
                            cout << "Ingrese el tamaño de la base del triangulo: ";
                            cin >> base;
                            clearInputPrompt();
                            cout << "Orientacion: (1: Arriba | 2: Abajo | 3: Derecha | 4: Izquierda): ";
                            int orientation;
                            cin >> orientation;
                            clearInputPrompt();

                            switch (orientation) {
                                case 1:
                                    for (int i = 0; i < base; ++i) {
                                        gotoxy(x - i, y - i);
                                        cout << drawChar << ' ';
                                        gotoxy(x + i, y - i);
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i <= base * 2; ++i) {
                                        gotoxy(x - base + i, y - base);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 2:
                                    for (int i = 0; i < base; ++i) {
                                        gotoxy(x - i, y + i);
                                        cout << drawChar << ' ';
                                        gotoxy(x + i, y + i);
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i <= base * 2; ++i) {
                                        gotoxy(x - base + i, y + base);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 3:
                                    for (int i = 0; i < base; ++i) {
                                        gotoxy(x + i, y - i);
                                        cout << drawChar << ' ';
                                        gotoxy(x + i, y + i);
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i <= base * 2; ++i) {
                                        gotoxy(x + base, y - base + i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 4:
                                    for (int i = 0; i < base; ++i) {
                                        gotoxy(x - i, y - i);
                                        cout << drawChar << ' ';
                                        gotoxy(x - i, y + i);
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i <= base * 2; ++i) {
                                        gotoxy(x - base, y - base + i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                default:
                                    cout << "Orientacion no valida." << endl;
                                    break;
                            }
                            break;
                        }
                        case 60: {
                            int lado;
                            clearInputPrompt();
                            cout << "Ingrese el tamaño del cuadrado: ";
                            cin >> lado;
                            clearInputPrompt();
                            cout << "Orientacion: (1: Arriba | 2: Abajo | 3: Derecha | 4: Izquierda): ";
                            int orientation;
                            cin >> orientation;
                            clearInputPrompt();

                            switch (orientation) {
                                case 1:
                                case 2:
                                    for (int i = 0; i < lado; ++i) {
                                        gotoxy(x, y + (orientation == 1 ? -i : i));
                                        cout << drawChar << ' ';
                                        gotoxy(x + (lado - 1) * 2, y + (orientation == 1 ? -i : i));
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i < lado; ++i) {
                                        gotoxy(x + i * 2, y + (orientation == 1 ? -lado + 1 : lado - 1));
                                        cout << drawChar << ' ';
                                        gotoxy(x + i * 2, y);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 3:
                                case 4:
                                    for (int i = 0; i < lado; ++i) {
                                        gotoxy(x + (orientation == 3 ? i : -i) * 2, y);
                                        cout << drawChar << ' ';
                                        gotoxy(x + (orientation == 3 ? i : -i) * 2, y - (lado - 1));
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i < lado; ++i) {
                                        gotoxy(x + (orientation == 3 ? lado - 1 : -lado + 1) * 2, y - i);
                                        cout << drawChar << ' ';
                                        gotoxy(x, y - i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                default:
                                    cout << "Orientacion no valida." << endl;
                                    break;
                            }
                            break;
                        }
                        case 61: {
                            int base, altura;
                            clearInputPrompt();
                            cout << "Ingrese el tamaño de la base del rectangulo: ";
                            cin >> base;
                            clearInputPrompt();
                            cout << "Ingrese la altura del rectangulo: ";
                            cin >> altura;
                            clearInputPrompt();
                            cout << "Seleccione la orientación (1: Arriba | 2: Abajo): ";
                            int orientation;
                            cin >> orientation;
                            clearInputPrompt();

                            switch (orientation) {
                                case 1:
                                    for (int i = 0; i < altura; ++i) {
                                        gotoxy(x, y - i);
                                        cout << drawChar << ' ';
                                        gotoxy(x + (base - 1) * 2, y - i);
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i < base; ++i) {
                                        gotoxy(x + i * 2, y);
                                        cout << drawChar << ' ';
                                        gotoxy(x + i * 2, y - (altura - 1));
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 2:
                                    for (int i = 0; i < altura; ++i) {
                                        gotoxy(x, y + i);
                                        cout << drawChar << ' ';
                                        gotoxy(x + (base - 1) * 2, y + i);
                                        cout << drawChar << ' ';
                                    }
                                    for (int i = 0; i < base; ++i) {
                                        gotoxy(x + i * 2, y);
                                        cout << drawChar << ' ';
                                        gotoxy(x + i * 2, y + (altura - 1));
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                default:
                                    cout << "Orientacion no valida." << endl;
                                    break;
                            }
                            break;
                        }
                        case 62: {
                            int radio;
                            clearInputPrompt();
                            cout << "Ingrese el radio del círculo: ";
                            cin >> radio;
                            clearInputPrompt();

                            for (int i = -radio; i <= radio; ++i) {
                                for (int j = -radio; j <= radio; ++j) {
                                    if (i * i + j * j <= radio * radio && i * i + j * j >= (radio - 1) * (radio - 1)) {
                                        gotoxy(x + j * 2, y + i);
                                        cout << drawChar << ' ';
                                    }
                                }
                            }
                            break;
                        }
                        case 63: {
                            int length;
                            clearInputPrompt();
                            cout << "Ingrese la longitud de la linea: ";
                            cin >> length;
                            clearInputPrompt();
                            cout << "Orientacion (1: Arriba | 2: Diagonal Derecha Arriba | 3: Abajo | 4: Diagonal Derecha Abajo | 5: Derecha | 6: Diagonal Izquierda Arriba | 7: Izquierda | 8: Diagonal Izquierda Abajo): ";
                            int orientation;
                            cin >> orientation;
                            clearInputPrompt();

                            switch (orientation) {
                                case 1:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x, y - i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 2:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x + i * 2, y - i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 3:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x, y + i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 4:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x + i * 2, y + i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 5:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x + i * 2, y);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 6:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x - i * 2, y - i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 7:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x - i * 2, y);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                case 8:
                                    for (int i = 0; i < length; ++i) {
                                        gotoxy(x - i * 2, y + i);
                                        cout << drawChar << ' ';
                                    }
                                    break;
                                default:
                                    cout << "Orientacion no valida." << endl;
                                    break;
                            }
                            break;
                        }
                        case 64: {
                            int diagonal;
                            clearInputPrompt();
                            cout << "Ingrese la longitud de la diagonal del rombo: ";
                            cin >> diagonal;
                            clearInputPrompt();
                            cout << "Orientacion: (1: Arriba | 2: Abajo): ";
                            int orientation;
                            cin >> orientation;
                            clearInputPrompt();

                            int half = diagonal / 2;
                            if (orientation == 1) {
                                for (int i = 0; i <= half; ++i) {
                                    gotoxy(x + i * 2, y - half + i);
                                    cout << drawChar << ' ';
                                    gotoxy(x - i * 2, y - half + i);
                                    cout << drawChar << ' ';
                                    gotoxy(x + i * 2, y + half - i);
                                    cout << drawChar << ' ';
                                    gotoxy(x - i * 2, y + half - i);
                                    cout << drawChar << ' ';
                                }
                            } else if (orientation == 2) {
                                for (int i = 0; i <= half; ++i) {
                                    gotoxy(x + i * 2, y + half - i);
                                    cout << drawChar << ' ';
                                    gotoxy(x - i * 2, y + half - i);
                                    cout << drawChar << ' ';
                                    gotoxy(x + i * 2, y - half + i);
                                    cout << drawChar << ' ';
                                    gotoxy(x - i * 2, y - half + i);
                                    cout << drawChar << ' ';
                                }
                            } else {
                                cout << "Orientacion no valida." << endl;
                            }
                            break;
                        }
                        case 65: {
                            int radio;
                            clearInputPrompt();
                            cout << "Ingrese el tamaño del hexagono: ";
                            cin >> radio;
                            clearInputPrompt();

                            int centerX = x;
                            int centerY = y;

                            for (int i = -radio; i <= radio; ++i) {
                                for (int j = -radio; j <= radio; ++j) {
                                    if (abs(2 * i + j) <= radio && abs(2 * j + i) <= radio && abs(2 * j - i) <= radio) {
                                        gotoxy(centerX + j, centerY + i);
                                        cout << drawChar;
                                    }
                                }
                            }
                            break;
                        }
                        default:
                            cout << "Opcion no valida." << endl;
                            break;
                    }

                    positionSelected = false;
                } else if (key == '0') {
                    cout << "Goodbye" << endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}

