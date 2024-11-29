// #include <iostream>
// #include <time.h>
// #include <iomanip>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
// 2048
/*
############  2048  #################
w --> up
s --> down
a --> left
d --> right

*/

// ******** to do ***********
// write end game code

#define delay 1
#define type 2
#define Z 3
struct State
{
    int board[4][4];
    int score;
    int cnt;

    State(int a[4][4], int s, int c)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                board[i][j] = a[i][j];
        score = s;
        cnt = c;
    }
};
deque<State> undo, redo;
int board[4][4] = {0};
int score = 0;
int cnt = 0;
int move_merge = 0;

void print(int n);
void genrate();
void merge_temp(int temp[]);
void up();
void down();
void right();
void left();
void play();
int check();

int main()
{
    system("color F0");
    genrate();
    print(type);
    while (cnt < 16 || check())
    {
        play();
    }
    cout << "*****GAME OVER*****" << endl;
    cout << "Your Score: " << score << endl
         << endl;
    system("pause");
    return 0;
}

int check()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1])
                return 1;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == board[i + 1][j])
                return 1;
        }
    }
    return 0;
}
void play()
{
    fflush(stdin);
    char c = getchar();

    if (c == 'w')
        up();
    else if (c == 's')
        down();
    else if (c == 'd')
        right();
    else if (c == 'a')
        left();
    else if (c == 'u')
    {
        State old = undo.back();
        State curr(board , score , cnt);
        undo.pop_back();
        redo.push_back(curr);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                board[i][j] = old.board[i][j];
        score = old.score;
        cnt = old.cnt;
        print(type);
    }
    else if (c == 'r')
    {
        State old = redo.back();
        State curr(board , score , cnt);
        redo.pop_back();
        undo.push_back(curr);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                board[i][j] = old.board[i][j];
        score = old.score;
        cnt = old.cnt;
        print(type);
    }
    else
        return;
    if (move_merge)
    {

        State curr(board, score, cnt);
        undo.push_back(curr);
        while (undo.size() > Z)
            undo.pop_front();
        while (!redo.empty())
            redo.pop_back();
        genrate();
        print(type);
        move_merge = 0;
    }
}
void merge_temp(int temp[])
{
    for (int i = 0; i < 3; i++)
    {
        if (temp[i] != 0 && temp[i] == temp[i + 1])
        {
            cnt--;
            move_merge++;
            score += 2 * temp[i];
            temp[i] *= 2;
            for (int j = i + 1; j < 3; j++)
            {
                temp[j] = temp[j + 1];
            }
            temp[3] = 0;
        }
    }
}
void right()
{
    for (int i = 0; i < 4; i++)
    {
        int temp[4] = {0};
        int x = 0;
        for (int j = 3; j >= 0; j--)
        {
            if (board[i][j])
                temp[x++] = board[i][j];
        }
        if (board[i][0] != temp[3] ||
            board[i][1] != temp[2] ||
            board[i][2] != temp[1] ||
            board[i][3] != temp[0])
            move_merge++;
        merge_temp(temp);
        if (move_merge)
        {
            board[i][0] = temp[3];
            board[i][1] = temp[2];
            board[i][2] = temp[1];
            board[i][3] = temp[0];
        }
    }
}
void left()
{
    for (int i = 0; i < 4; i++)
    {
        int temp[4] = {0};
        int x = 0;
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j])
                temp[x++] = board[i][j];
        }
        if (board[i][0] != temp[0] ||
            board[i][1] != temp[1] ||
            board[i][2] != temp[2] ||
            board[i][3] != temp[3])
            move_merge++;
        merge_temp(temp);
        if (move_merge)
        {
            board[i][0] = temp[0];
            board[i][1] = temp[1];
            board[i][2] = temp[2];
            board[i][3] = temp[3];
        }
    }
}
void up()
{
    for (int j = 0; j < 4; j++)
    {
        int temp[4] = {0};
        int x = 0;
        for (int i = 0; i < 4; i++)
        {
            if (board[i][j])
                temp[x++] = board[i][j];
        }
        if (board[0][j] != temp[0] ||
            board[1][j] != temp[1] ||
            board[2][j] != temp[2] ||
            board[3][j] != temp[3])
            move_merge++;
        merge_temp(temp);
        if (move_merge)
        {
            board[0][j] = temp[0];
            board[1][j] = temp[1];
            board[2][j] = temp[2];
            board[3][j] = temp[3];
        }
    }
}
void down()
{
    for (int j = 0; j < 4; j++)
    {
        int temp[4] = {0};
        int x = 0;
        for (int i = 3; i >= 0; i--)
        {
            if (board[i][j])
                temp[x++] = board[i][j];
        }
        if (board[0][j] != temp[3] ||
            board[1][j] != temp[2] ||
            board[2][j] != temp[1] ||
            board[3][j] != temp[0])
            move_merge++;
        merge_temp(temp);
        if (move_merge)
        {
            board[0][j] = temp[3];
            board[1][j] = temp[2];
            board[2][j] = temp[1];
            board[3][j] = temp[0];
        }
    }
}
void genrate()
{
    int numretor_prob = 3, den_prob = 4; // porb of getting 2
    cnt++;
    srand(time(NULL));
    int n = rand() % 16;
    srand(2 * time(NULL));
    int x = rand() % den_prob;

    int cnt = 0;
    int i = 0;
    while (true)
    {
        if (board[i / 4][i % 4] == 0)
        {
            if (cnt == n)
            {
                board[i / 4][i % 4] = (x <= numretor_prob - 1) ? 2 : 4;
                break;
            }
            cnt++;
        }
        i++;
        i = i % 16;
    }
    cout << endl;
}
void print(int n)
{
    system("cls");
    if (n == 1)
    {
        cout << "\n\n\t\tScore: " << score << endl
             << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << "\t";
            for (int j = 0; j < 21; j++)
            {
                cout << '-';
            }
            cout << endl;
            cout << "\t|";
            for (int j = 0; j < 4; j++)
            {
                printf("%4d|", board[i][j]);
                Sleep(delay);
            }
            cout << endl;
        }
        cout << "\t";
        for (int j = 0; j < 21; j++)
        {
            cout << '-';
        }
        cout << endl;
    }
    else if (n == 2)
    {
        cout << "\n\n\t\tScore: " << score << endl
             << endl;

        for (int i = 0; i < 4; i++)
        {
            printf("\t");
            for (int j = 0; j < 4; j++)
            {
                printf("%4d ", board[i][j]);
                Sleep(delay);
            }
            cout << endl;
        }
        cout << endl;
    }
}
