#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

bool gameOver;
const int lebar = 50;
const int tinggi = 20;
int x, y, posisiBuahX, posisiBuahY, skor;
int posisiEkorX[100], posisiEkorY[100];
int panjangEkor;
enum eArah { BERHENTI = 0, KIRI, KANAN, ATAS, BAWAH };
eArah arah;

void loading(){
	system ("color 2");
	initscr();
mvprintw(15,46,"PRESS ANY KEY TO START");
	refresh();
	Sleep(100);
	getch();
	clear();
		
for (int y=0; y<3; y++){
	mvprintw(12,55,"LOADING");
	mvprintw(13,50, "-------------------");
	mvprintw(14,50, "|                 |");
	mvprintw(15,50, "-------------------");
}

for (int a=1; a<=2; a++){
	mvprintw(14,51,"                 ");
	for (int f=1;f<17;f++){
	mvprintw(14,50+f,">>");
	refresh();
	Sleep(100);
}

}
  clear();
  endwin();
  
for(int f=0; f<20; f++){	
    mvprintw(25-f,25," db   d8b   db d88888b db       .o88b.  .d88b.  .88b  d88. d88888b       ");
    mvprintw(26-f,25," 88   I8I   88 88'     88      d8P  Y8 .8P  Y8. 88'YbdP`88 88'           ");
    mvprintw(27-f,25," 88   I8I   88 88ooooo 88      8P      88    88 88  88  88 88ooooo       ");
    mvprintw(28-f,25," Y8   I8I   88 88~~~~~ 88      8b      88    88 88  88  88 88~~~~~       ");
    mvprintw(29-f,25," `8b d8'8b d8' 88.     88booo. Y8b  d8 `8b  d8' 88  88  88 88.           ");
    mvprintw(30-f,25,"  `8b8' `8d8'  Y88888P Y88888P  `Y88P'  `Y88P'  YP  YP  YP Y88888P       ");
	mvprintw(31-f,25,"                                                                          ");
refresh();
Sleep(100);
}
}
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
    erase();

    printw("\n ");
    for (int i = 0; i < lebar + 2; i++)
        printw("#");
    printw("\n");


    for (int i = 0; i < tinggi; i++)
    {
        for (int j = 0; j < lebar; j++)
        {
            if (j == 0)
                printw(" #");
            if (i == y && j == x)
                printw("O");
            else if (i == posisiBuahY && j == posisiBuahX)
                printw("$");
            else
            {
                bool print = false;
                for (int k = 0; k < panjangEkor; k++)
                {
                    if (posisiEkorX[k] == j && posisiEkorY[k] == i)
                    {
                        printw("o");
                        print = true;
                    }
                }
                if (!print)
                    printw(" ");
            }

            if (j == lebar - 1)
                printw("#");
        }
        printw("\n");
    }

    printw(" ");
    for (int i = 0; i < lebar + 2; i++)
        printw("#");
    printw("\n SCORE : %d\n", skor);

        mvprintw(16,57,"CONTROLS :");
        mvprintw(18,57,"W = UP");
        mvprintw(19,57,"A = LEFT");
        mvprintw(20,57,"S = DOWN");
        mvprintw(21,57,"D = RIGHT");
        
        mvprintw(2,57,".d8888. d8b   db  .d8b.  db   dD d88888b");
        mvprintw(3,57,"88'  YP 888o  88 d8' `8b 88 ,8P' 88'    ");
        mvprintw(4,57,"`8bo.   88V8o 88 88ooo88 88,8P   88ooooo");
        mvprintw(5,57,"  `Y8b. 88 V8o88 88~~~88 88`8b   88~~~~~");
        mvprintw(6,57,"db   8D 88  V888 88   88 88 `88. 88.    ");
        mvprintw(7,57,"`8888Y' VP   V8P YP   YP YP   YD Y88888P");
        
        mvprintw(9,57,"HOW TO PLAY :");
        mvprintw(11,57,"1. MOVE WITH WASD KEYS");
        mvprintw(12,57,"2. COLLECT THE $");
        mvprintw(13,57,"3. DON'T HIT THE WALL!");
        mvprintw(14,57,"3. DON'T HIT THE THE TAIL OF THE SNAKE!");
}

void Input()
{
    int ch = getch();

    switch (ch)
    {
    case 'a':
        if (arah != KANAN)  
            arah = KIRI;
        break;
    case 'd':
        if (arah != KIRI) 
            arah = KANAN;
        break;
    case 'w':
        if (arah != BAWAH) 
            arah = ATAS;
        break;
    case 's':
        if (arah != ATAS)  
            arah = BAWAH;
        break;
    default:
        break;
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
        srand(time(0));
        skor += 10;
        posisiBuahX = rand() % lebar;
        posisiBuahY = rand() % tinggi;
        panjangEkor++;
    }
}

int main()
{
	loading();
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    timeout(50);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }

    endwin();
 cout <<"        GGGGGGGGGGGGG                                                               "<<endl;
cout <<"     GGG::::::::::::G                                                               "<<endl;
cout <<"   GG:::::::::::::::G                                                               "<<endl;
cout <<"  G:::::GGGGGGGG::::G                                                               "<<endl;
cout <<" G:::::G       GGGGGG  aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee     "<<endl;
cout <<"G:::::G                a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee   "<<endl;
cout <<"G:::::G                aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee "<<endl;
cout <<"G:::::G    GGGGGGGGGG           a::::a m::::::::::::::::::::::me::::::e     e:::::e "<<endl;
cout <<"G:::::G    G::::::::G    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e "<<endl;
cout <<"G:::::G    GGGGG::::G  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e  "<<endl;
cout <<"G:::::G        G::::G a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee   "<<endl;
cout <<" G:::::G       G::::Ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e            "<<endl;
cout <<"  G:::::GGGGGGGG::::Ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e           "<<endl;
cout <<"   GG:::::::::::::::Ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee   "<<endl;
cout <<"     GGG::::::GGG:::G a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e   "<<endl;
cout <<"        GGGGGG   GGGG  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee             YOUR SCORE IS "<<skor<<endl;
cout <<"              																		"<<endl;
cout <<"   ooooooooooo vvvvvvv           vvvvvvv eeeeeeeeeeee    rrrrr   rrrrrrrrr          "<<endl;
cout <<" oo:::::::::::oov:::::v         v:::::vee::::::::::::ee  r::::rrr:::::::::r         "<<endl;
cout <<"o:::::::::::::::ov:::::v       v:::::ve::::::eeeee:::::eer:::::::::::::::::r        "<<endl;
cout <<"o:::::ooooo:::::o v:::::v     v:::::ve::::::e     e:::::err::::::rrrrr::::::r       "<<endl;
cout <<"o::::o     o::::o  v:::::v   v:::::v e:::::::eeeee::::::e r:::::r     r:::::r       "<<endl;
cout <<"o::::o     o::::o   v:::::v v:::::v  e:::::::::::::::::e  r:::::r     rrrrrrr       "<<endl;                                                                            
cout <<"o::::o     o::::o    v:::::v:::::v   e::::::eeeeeeeeeee   r:::::r                   "<<endl;                                                                           
cout <<"o::::o     o::::o     v:::::::::v    e:::::::e            r:::::r                   "<<endl;                                                                                
cout <<"o:::::ooooo:::::o      v:::::::v     e::::::::e           r:::::r                   "<<endl;                                                                              
cout <<"o:::::::::::::::o       v:::::v       e::::::::eeeeeeee   r:::::r                   "<<endl;   
cout <<" oo:::::::::::oo         v:::v         ee:::::::::::::e   r:::::r                   "<<endl;   
cout <<"   ooooooooooo            vvv            eeeeeeeeeeeeee   rrrrrrr                    "<<endl;   

    return 0;
}
