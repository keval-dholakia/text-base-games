#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
// minesweeper
void DisplayBoard(int Board[10][10], int StatusBoard[10][10], int BombCount, int Flag); // done
void DisplayFullBoard(int Board[10][10]);                                               // done
void GenerateBomb(int Board[10][10], int TotalBomb);                                    // done
void CountSurroundingBomb(int Board[10][10]);                                           // done
void dignull(int Board[10][10], int StatusBoard[10][10], int &DigConunt, int x, int y); // done

int main()
{

    while (true)
    {
        system("color f0");
        system("cls");
        int TotalBomb;
        int Flag = 0;
        int DigCount = 0;
        int Board[10][10] = {0};
        int StatusBoard[10][10] = {0};
        cout << "Enter The Total Number Of Bomb : ";
        cin >> TotalBomb;
        if (TotalBomb < 1 || TotalBomb > 100)
        {
            cout << "Invalid!!" << endl;
            continue;
        }
        GenerateBomb(Board, TotalBomb);
        CountSurroundingBomb(Board);
        while (true)
        {
            DisplayBoard(Board, StatusBoard, TotalBomb, Flag);
        p1:
            int x, y;
            cout << "Enter A Palce : ";
            cin >> x >> y;
            if (x < 1 || x > 10 || y < 1 || y > 10 || StatusBoard[x - 1][y - 1] == 1)
            {
                cout << "INVALID!!" << endl;
                goto p1;
            }
        p2:
            int choice;
            cout << "1 To Dig." << endl;
            cout << "2 To put/remove flag." << endl;
            cout << "3 To Return." << endl;
            cout << "Enter A choice for (" << x << "," << y << ") :";
            cin >> choice;
            if (choice == 3) // return
            {
                goto p1;
            }
            else if (choice == 1) // dig
            {
                if (Board[x - 1][y - 1] == -1) // bomb end game
                {
                    cout << "OOPS!!...Bomb Exploed" << endl
                         << endl;
                    DisplayFullBoard(Board);
                    system("pause");
                    break;
                }
                else // show number
                {
                    if (StatusBoard[x - 1][y - 1] == -1)
                        Flag--;
                    StatusBoard[x - 1][y - 1] = 1;
                    if (Board[x - 1][y - 1] == 0)
                        dignull(Board, StatusBoard, DigCount, x, y);
                    DigCount++;
                }
            }
            else if (choice == 2) // flag
            {
                StatusBoard[x - 1][y - 1] = (StatusBoard[x - 1][y - 1] == 0) ? -1 : 0;
                (StatusBoard[x - 1][y - 1] == 0) ? Flag-- : Flag++;
            }
            else
            {
                cout << "INVALID" << endl;
                goto p2;
            }
            if (DigCount == 100 - TotalBomb)
            {
                cout << "Completed!!" << endl;
                DisplayFullBoard(Board);
                char x;
                cout << "Want to play again (y/n)?....";
                cin >> x;
                if (x == 'n' || x == 'N')
                    return 0;
                break;
            }
        }
    }
    return 0;
}

void dignull(int Board[10][10], int StatusBoard[10][10], int &DigConunt, int x, int y)
{
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            if (x - 1 - i >= 0 && x - 1 - i < 10 && y - 1 - j >= 0 && y - 1 - j < 10 && StatusBoard[x - 1 - i][y - 1 - j] == 0)
            {
                DigConunt++;
                StatusBoard[x - 1 - i][y - 1 - j] = 1;
                if (Board[x - 1 - i][y - 1 - j] == 0)
                    dignull(Board, StatusBoard, DigConunt, x - i, y - j);
            }
        }
}

void DisplayBoard(int Board[10][10], int StatusBoard[10][10], int BombCount, int Flag)
{

    system("cls");

    cout << "\tTotal BOMB : " << BombCount << endl
         << "\tFlag : " << Flag << endl;
    cout << "   1 2 3 4 5 6 7 8 9 10" << endl
         << "_______________________" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i + 1;
        if (i == 9)
            cout << "|";
        else
            cout << " |";
        for (int j = 0; j < 10; j++)
        {
            if (StatusBoard[i][j] == 1)
            {
                cout << Board[i][j] << " ";
            }
            else if (StatusBoard[i][j] == -1)
            {
                cout << "@ ";
            }
            else
            {
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
void DisplayFullBoard(int Board[10][10])
{
    cout << "   1 2 3 4 5 6 7 8 9 10" << endl
         << "_______________________" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i + 1;
        if (i == 9)
            cout << "|";
        else
            cout << " |";
        for (int j = 0; j < 10; j++)
        {
            if (Board[i][j] == -1)
            {
                cout << "# ";
            }
            else
            {
                cout << Board[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
void GenerateBomb(int Board[10][10], int TotalBomb)
{
    srand(time(NULL));
    int count = 0;
    while (count < TotalBomb)
    {
        int n = rand() % 100;
        int i = n / 10;
        int j = n % 10;
        if (Board[i][j] != -1)
        {
            Board[i][j] = -1;
            count++;
        }
    }
}
void CountSurroundingBomb(int Board[10][10])
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (Board[i][j] == -1)
                for (int x = -1; x < 2; x++)
                    for (int y = -1; y < 2; y++)
                        if (Board[i + x][j + y] >= 0 && i + x >= 0 && j + y >= 0 && i + x <= 9 && j + y <= 9)
                            Board[i + x][j + y]++;
}
