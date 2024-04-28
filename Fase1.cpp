#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int CONSOLE_WIDTH = 120;
const int CONSOLE_HEIGHT = 30;


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    int x = CONSOLE_WIDTH / 2;
    int y = CONSOLE_HEIGHT / 2;

    cout << "Use W, A, S, D para moverse de posicion" << endl;
    cout << "Presione F12 para seleccionar la posicion" << endl;

    bool positionSelected = false;

    while (true) {
        if (!positionSelected) {
            if (_kbhit()) {
                char key = _getch();

                if (key == -32) {
                    key = _getch();
                    if (key == -122) {
                        positionSelected = true;
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
                    }

                    gotoxy(x, y);
                }
            }
        } else {

            gotoxy(0, 26);

            cout << "Seleccione una figura:" << endl;
            cout << "1. Triangulo" << endl;
            cout << "2. Cuadrado" << endl;
            cout << "3. Rectangulo" << endl;
            cout << "4. Circulo" << endl;
            cout << "0. Salir" << endl;
            cout << "Opcion: ";

            int opcion;
            cin >> opcion;

            switch (opcion) {
                case 1: {
                    int base;
                    cout << "Ingrese el tamaño de la base del triangulo: ";
                    cin >> base;

                    for (int i = 0; i < base; ++i) {
                        gotoxy(x + i * 2, y + base - 1);
                        cout << "* ";
                    }

                    for (int i = 0; i < base; ++i) {
                        gotoxy(x, y + i);
                        cout << "* ";

                        gotoxy(x + i * 2, y + i);
                        cout << "* ";
                    }
                    break;
                }
                case 2: {
                    int lado;
                    cout << "Ingrese el tamaño de un lado del cuadrado: ";
                    cin >> lado;

                    for (int i = 0; i < lado; ++i) {
                        gotoxy(x + i * 2, y);
                        cout << "* ";

                        gotoxy(x + i * 2, y + lado - 1);
                        cout << "* ";
                    }

                    for (int i = 1; i < lado - 1; ++i) {
                        gotoxy(x, y + i);
                        cout << "* ";

                        gotoxy(x + (lado - 1) * 2, y + i);
                        cout << "* ";
                    }
                    break;
                }
                case 3: {
                    int base, altura;
                    cout << "Ingrese el tamaño de la base del rectangulo: ";
                    cin >> base;
                    cout << "Ingrese la altura del rectangulo: ";
                    cin >> altura;

                    for (int i = 0; i < base; ++i) {
                        gotoxy(x + i * 2, y);
                        cout << "* ";

                        gotoxy(x + i * 2, y + altura - 1);
                        cout << "* ";
                    }

                    for (int i = 1; i < altura - 1; ++i) {
                        gotoxy(x, y + i);
                        cout << "* ";

                        gotoxy(x + (base - 1) * 2, y + i);
                        cout << "* ";
                    }
                    break;
                }
                case 4: {
                    int radio;
                    cout << "Ingrese el radio del circulo: ";
                    cin >> radio;

                    for (int i = -radio; i <= radio; ++i) {
                        for (int j = -radio; j <= radio; ++j) {
                            if (i * i + j * j <= radio * radio && i * i + (j - 1) * (j - 1) > radio * radio) {
                                gotoxy(x + j * 2, y + i);
                                cout << "* ";
                            }
                        }
                    }
                    break;
                }
                case 0:
                    cout << "Gracias por usar el programa                       " << endl;
                    exit(0);
                default:
                    cout << "Opción no válida." << endl;
                    break;
            }

            positionSelected = false;
        }
    }

    return 0;
}
