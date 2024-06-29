#include <iostream>
#include <stdlib.h> 
#include <conio.h>      // przyda się do getch()
#include <time.h>       // losowe liczby
#include <fstream>      // wczytanie tekstu
#include <string>       // wczytanie tekstu
using namespace std;

#define UNASSIGNED 0 // puste komórki
#define N 9 // wielkość planszy

// szuka wolnych komórek
bool FindUnassignedLocation(int grid[N][N],
    int& row, int& col);

bool isSafe(int grid[N][N], int row,
    int col, int num);

bool SolveSudoku(int grid[N][N])
{
    int row, col;

    if (!FindUnassignedLocation(grid, row, col))
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (SolveSudoku(grid))
                return true;
            grid[row][col] = UNASSIGNED;
        }
    }

    // włącza backtracking
    return false;
}


// czy puste
bool FindUnassignedLocation(int grid[N][N],
    int& row, int& col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

// czy było w rzędzie
bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// czy było w kolumnie
bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// czy było w polu 3x3
bool UsedInBox(int grid[N][N], int boxStartRow,
    int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                [col + boxStartCol] ==
                num)
                return true;
    return false;
}


// czy ok w rzędzie i kolumnie
bool isSafe(int grid[N][N], int row,
    int col, int num)
{
    return !UsedInRow(grid, row, num)  
        && !UsedInCol(grid, col, num)
        && !UsedInBox(grid, row - row % 3,
            col - col % 3, num)
        && grid[row][col] == UNASSIGNED;
}


void druplansza(int plansza[N][N]) { // drukowanie planszy
    int wiersz = 0;
    cout << "|1 2 3 |4 5 6 |7 8 9 |" << endl;
    for (int i = 0; i < 9; i++)
    {
        wiersz++;
        if (i % 3 == false)
        {
            cout << "+------+------+------+-" << endl;
        }
        for ( int j = 0; j < 9; j++)
        {
            
            if (j % 3 == false)
            {
                cout << "|";
            }
            cout << plansza[i][j] << ' ';
        }
        cout << "|";
        cout << wiersz << endl;
    }
    cout << "+------+------+------+- \n" << endl;
}

void planszalevel(int level, int planszacopy[N][N]) // generowanie pustych pól
{ 
    for (int k = 0; k < level; k++) {
        int ri = (rand() % 8) + 1;
        int rj = (rand() % 8) + 1;
        if (ri != 4 && rj != 4) {
            planszacopy[ri][rj] = 0;
            ri = 8 - ri;
            rj = 8 - rj;
            planszacopy[ri][rj] = 0;
        }
        else
        {
            planszacopy[4][4] = 0;
        }
    }
}

void generator(int plansza [N][N]) {
    int pierwsza = 0, i = 0, j = 0;
    srand((unsigned)time(0));
    pierwsza = rand() % 9 + 1;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (pierwsza >= 10) {
                pierwsza = pierwsza - 9;
            }
            plansza[i][j] = pierwsza;
            pierwsza++;
        }

        if (i < 2) {
            pierwsza = plansza[i][j - 3];
        }
        if (i == 2) {
            pierwsza = plansza[0][1];
        }
        if (i > 2 && i < 5) {
            pierwsza = plansza[i][j - 3];
        }
        if (i == 5) {
            pierwsza = plansza[1][2];
        }
        if (i > 5) {
            pierwsza = plansza[i][j - 3];
        }
    }
}

int gra(int level) { //gra 
    int i, j;
    int x = 0, y = 0, a = 0, b = 0, c = 0;
    int zera = 0;
    bool koniec = false;

    int plansza[N][N]; //tablica 9x9 i wszystko na 0
    int planszacopy[N][N];
    int planszamask[N][N];

    generator(plansza);
    std::copy(&plansza[0][0], &plansza[0][0] + 9 * 9, &planszacopy[0][0]);
    planszalevel(level, planszacopy);
    std::copy(&planszacopy[0][0], &planszacopy[0][0] + 9 * 9, &planszamask[0][0]);
    druplansza(planszacopy);
    for (i = 0; i < 9; i++)  // zliczanie pustych pól planszy, przyda się przy kończeniu sudoku
    {
        for (j = 0; j < 9; j++)
        {
            if (planszacopy[i][j] == 0) {
                zera = zera + 1;
            }
        }
    }
    koniec = false;

    while (koniec == false) {
        cout << "liczba pustych pol: " << zera << "\n" << endl; // debug
        cout << "wpisz wiersz" << endl;
        while (true) // walidacja danych
        {
            cin >> a;
            if (!cin && a <= 0 || a > 9)
            {
                cout << "niepoprawny znak" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else break;
        }
        a--;
        cout << "wpisz kolumne" << endl;
        while (true) // walidacja danych
        {
            cin >> b;
            if (!cin && b <= 0 || b > 9)
            {
                cout << "niepoprawny znak" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else break;
        }
        b--;
        cout << "wpisz wartosc" << endl;
        while (true) // walidacja danych
        {
            cin >> c;
            if (!cin && c <= 0 || c > 9)
            {
                cout << "niepoprawny znak" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else break;
        }

        if (planszamask[a][b] > 0) {
            cout << "zajete pole \n" << endl;
        }
        else {
            planszacopy[a][b] = c;
            druplansza(planszacopy);
            zera = 0;
            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)
                {
                    if (planszacopy[i][j] == 0) {
                        zera++;
                    }
                }
            }
            if (zera == 0) {
                koniec = true;
            }
        }
    }

    int errors = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (planszacopy[i][j] != plansza[i][j]) {
                errors++;
            }
        }
    }
    if (errors == 0) {
        cout << "Gratulacje ukonczyles gre! 0 bledow!" << endl;
        return 0;
    }
    else
    {
        cout << "Liczba bledow: " << errors << endl;
        cout << "Poprawny wynik: " << endl;
        druplansza(plansza);
        return 0;
    }

}



int main()
{
    int level, i, j;
    int x = 0, y = 0, a = 0, b = 0, c = 0;
    int zera = 0;
    bool koniec = false;

    int plansza[N][N]; //tablica 9x9 i wszystko na 0
    int planszacopy[N][N];
    int planszamask[N][N];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            plansza[i][j] = 0;
        }
    }
    // logo: bardzo ważne
    cout << " _____       _     _       " << endl;
    cout << "|   __|_ _ _| |___| |_ _ _ " << endl;
    cout << "|__   | | | . | . | '_| | |" << endl;
    cout << "|_____|___|___|___|_,_|___|" << endl;

    cout << "wpisz cyfre:" << endl;

    cout << "1 Nowa Gra" << endl;
    cout << "2 Rozwiazanie sudoku" << endl;
    cout << "3 Przykladowe rozwiazanie" << endl;

    while (true) // walidacja danych
    {
        cin >> x;
        if (!cin && x <= 0 || x >= 4)
        {
            cout << "niepoprawny znak" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else break;
    }

    // Gra
    if (x == 1) {
        cout << "Wybierz poziom : " << endl;
        cout << "0 Bardzo latwy (debug)" << endl;
        cout << "1 Latwy" << endl;
        cout << "2 Sredni" << endl;

        while (true) // walidacja danych
        {
            cin >> y;
            if (!cin && y <= 0 || y >= 3)
            {
                cout << "niepoprawny znak" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else break;
        }

        if (y == 0) {
            level = 3;
            gra(level);
        }
        if (y == 1) {
            level = 15;
            gra(level);
        }
        if (y == 2) {
            level = 30;
            gra(level);
        }
    }
        // rozwiazanie z pliku
        if (x == 2) {

            cout << "Rozwiazanie sudoku: w pliku sudoku.txt zamiesc cyfry do rozwiazania oddzielone spacja, 0 oznacza brak cyfry." << endl;
            cout << "Nacisnij dowolny klawisz aby kontynuowac." << endl;
            _getch();
            int arr[N][N];

            ifstream read_num;
            read_num.open("sudoku.txt");
            if (read_num.is_open())
            {
                for (int x = 0; x < 9; x++)
                {
                    for (int y = 0; y < 9; y++)
                    {
                        read_num >> arr[x][y];
                    }
                }
                read_num.close();
                cout << "odczytano:" << endl;
                druplansza(arr);
            }
            else {
                cout << "Problem z odczytem pliku" << endl;
                return 0;
            }


            if (SolveSudoku(arr) == true) {
                cout << "rozwiazanie:" << endl;
                druplansza(arr);

                ofstream out("rozwiazanie.txt");  // zapisz rozwiązanie do pliku

                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < 9; j++)
                        out << " " << arr[i][j];
                    out << "\n";
                }

            }
            else
                cout << "Sudoku nie ma rozwiazania";
        }
        // przykladowe rozwiazanie
        if (x == 3) {
            cout << "Program rozwiaze przykladowe sudoku ktore znajduje sie w kodzie zrodlowym gry" << endl;
            cout << "Nacisnij dowolny klawisz aby kontynuowac." << endl;
            _getch();
            int przyklad[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                                 { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                                 { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                                 { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                                 { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                                 { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                                 { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                                 { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                                 { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
            druplansza(przyklad);
            if (SolveSudoku(przyklad) == true) {
                cout << "rozwiazanie:" << endl;
                druplansza(przyklad);
            }
        }
        return 0;
    }