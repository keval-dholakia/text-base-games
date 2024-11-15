#include <iostream>
using namespace std;

int score[] = {0, 0};
int player = 1;

void PrintBoard(int Board[]);
bool DrawCheck(int BoardStatus[]);
bool WinCheck(int B[], int p);
bool AvoidRepetation(int BoardStatus[], int palce);
void EditBoard(int Board[], int BoardStatus[], int place, int turn);
void DisplayResult(int a);

int main()
{

    while (true)
    {
        int Board[9] = {0};
        int BoardStatus[9] = {0};
        int place;
        cout << "****LET`S START****" << endl;
        cout << "Player 1 Score(O) : " << score[0] << endl;
        cout << "Player 2 Score(#) : " << score[1] << endl;

        while (true)
        {
            PrintBoard(Board);
        again:
            cout << "Player " << player << " :";
            cin >> place;
            if (place < 1 || place > 9)
                goto again;
            if (!AvoidRepetation(BoardStatus, place))
                goto again;

            EditBoard(Board, BoardStatus, place, player);
            if (WinCheck(Board, player))
            {
                PrintBoard(Board);
                score[player - 1]++;
                DisplayResult(player);
                break;
            }
            if (DrawCheck(BoardStatus))
            {
                PrintBoard(Board);
                DisplayResult(0);
                player = (player == 1) ? 2 : 1;
                break;
            }
            player = (player == 1) ? 2 : 1;
        }
    }

    return 0;
}

void DisplayResult(int a)
{
    if (a == 1)
        cout << "****Player 1 Wins!!****" << endl;
    else if (a == 2)
        cout << "****Player 2 Wins!!****" << endl;
    else
        cout << "****Draw!!****" << endl;
    cout << "Player 1 Score(O) : " << score[0] << endl;
    cout << "Player 2 Score(#) : " << score[1] << endl;
}
void PrintBoard(int Board[])
{
    for (int i = 0; i < 9; i++)
    {
        switch (Board[i])
        {
        case 0:
            printf("\t-");
            break;
        case 1:
            printf("\tO");
            break;
        case 2:
            printf("\t#");
            break;
        }
        if (i == 2 || i == 5 || i == 8)
            cout << endl;
    }
}
bool DrawCheck(int BoardStatus[])
{
    for (int i = 0; i < 9; i++)
    {
        if (!BoardStatus[i])
            return false;
    }
    return true;
}
bool WinCheck(int B[], int p)
{
    if (B[0] == p)
    {
        if ((B[0] == B[1] && B[1] == B[2]) ||
            (B[0] == B[3] && B[3] == B[6]))
            return true;
    }
    if (B[4] == p)
    {
        if ((B[0] == B[4] && B[4] == B[8]) ||
            (B[2] == B[4] && B[4] == B[6]) ||
            (B[1] == B[4] && B[4] == B[7]) ||
            (B[3] == B[4] && B[4] == B[5]))
            return true;
    }
    if (B[8] == p)
    {
        if ((B[6] == B[7] && B[7] == B[8]) ||
            (B[2] == B[5] && B[5] == B[8]))
            return true;
    }
    return false;
}
bool AvoidRepetation(int BoardStatus[], int palce)
{
    if (BoardStatus[palce - 1])
        return false;
    return true;
}
void EditBoard(int Board[], int BoardStatus[], int place, int turn)
{
    Board[place - 1] = turn;
    BoardStatus[place - 1]++;
}