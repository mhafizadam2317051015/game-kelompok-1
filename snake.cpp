#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h> // Untuk membuat nilai spawn lebih acak
using namespace std;




bool gameOver;
const int lebar = 20;
const int tinggi = 20;
int x, y, posisiBuahX, posisiBuahY, skor;
int posisiEkorX[100], posisiEkorY[100];
int panjangEkor;
enum eArah { BERHENTI = 0, KIRI, KANAN, ATAS, BAWAH };
eArah arah;
void Setup()
{
    gameOver = false;
    arah = BERHENTI;
    x = lebar / 2;
    y = tinggi / 2;
    posisiBuahX = rand() % lebar;
    posisiBuahY = rand() % tinggi;
    skor = 0;
}
void Draw()
{
    system("cls"); // system("clear");
    cout << endl;
    cout << " ";
    for (int i = 0; i < lebar + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < tinggi; i++)
    {
        for (int j = 0; j < lebar; j++)
        {
            if (j == 0)
                cout << " #";
            if (i == y && j == x)
                cout << "O";
            else if (i == posisiBuahY && j == posisiBuahX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < panjangEkor; k++)
                {
                    if (posisiEkorX[k] == j && posisiEkorY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == lebar - 1)
                cout << "#";
        }
        cout << endl;
    }

    cout << " ";
    for (int i = 0; i < lebar + 2; i++)
        cout << "#";
    cout << endl;
    cout << " Skor:" << skor << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            arah = KIRI;
            break;
        case 'd':
            arah = KANAN;
            break;
        case 'w':
            arah = ATAS;
            break;
        case 's':
            arah = BAWAH;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}
void Logic()
{
    int prevX = posisiEkorX[0];
    int prevY = posisiEkorY[0];
    int prev2X, prev2Y;
    posisiEkorX[0] = x;
    posisiEkorY[0] = y;
    for (int i = 1; i < panjangEkor; i++)
    {
        prev2X = posisiEkorX[i];
        prev2Y = posisiEkorY[i];
        posisiEkorX[i] = prevX;
        posisiEkorY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (arah)
    {
    case KIRI:
        x--;
        break;
    case KANAN:
        x++;
        break;
    case ATAS:
        y--;
        break;
    case BAWAH:
        y++;
        break;
    default:
        break;
    }
    if (x > lebar || x < 0 || y > tinggi || y < 0)
        gameOver = true;

    for (int i = 0; i < panjangEkor; i++)
        if (posisiEkorX[i] == x && posisiEkorY[i] == y)
            gameOver = true;

    if (x == posisiBuahX && y == posisiBuahY)
    {
        srand(time(0)); // Nilai seed acak untuk rand berdasarkan waktu
        skor += 10;
        posisiBuahX = rand() % lebar;
        posisiBuahY = rand() % tinggi;
        panjangEkor++;
    }
}
int main()
{
    // Akan membuat cout lebih cepat
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    system("MODE con cols=24 lines=25");
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50); // sleep(10);
    }
    return 0;
}
