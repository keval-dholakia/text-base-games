/*
    this use complete backtracking to find solution

*/

#include <bits/stdc++.h>
using namespace std;

const int N = 9;
int a[N][N];
int r[N][N + 1]; // 1 -- ith row contain jth number
int c[N][N + 1];
int b[N][N + 1];

int BoxNumber(int x, int y)
{
    int qq = y / 3 + x / 3;
    return y / 3 + 3 * (x / 3);
}

void initialize()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i][j])
            {
                if (r[i][a[i][j]] || c[j][a[i][j]] || b[BoxNumber(i, j)][a[i][j]])
                {
                    cout << i << " " << j << endl;
                    cerr << "Error : " << a[i][j] << " is repeated!!" << endl;
                    exit(1);
                }
                r[i][a[i][j]] = 1;
                c[j][a[i][j]] = 1;
                b[BoxNumber(i, j)][a[i][j]] = 1;
            }
}
void print()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cout << a[i][j] << " \n"[j == 8];
}

bool call(int id)
{
    if (id == N * N)
        return true;
    int x = id / N, y = id % N;
    if (a[x][y])
        return call(id + 1);
    else
    {
        for (int i = 1; i <= N; i++)
        {
            if (!r[x][i] && !c[y][i] && !b[BoxNumber(x, y)][i])
            {

                r[x][i] = 1;
                c[y][i] = 1;
                b[BoxNumber(x, y)][i] = 1;

                a[x][y] = i;

                if (call(id + 1))
                    return true;

                r[x][i] = c[y][i] = b[BoxNumber(x, y)][i] = a[x][y] = 0;
            }
        }
    }
    return false;
}


int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    //     return 1;
    // }

    // string filename = argv[1];
    string filename = "read.txt";

    // open for reading
    ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    // read the file
    for (int i = 0; i < N; i++)
    {
        string s;
        if (!getline(file, s) || s.size() < 2 * N - 1)
        {
            cerr << "Error : Invalid Input" << endl;
            return 1;
        }

        for (int j = 0; j < 2 * N - 1; j += 2)
        {
            if (s[j] == '_')
                a[i][j / 2] = 0;
            else if (s[j] >= '1' && s[j] <= '9')
            {
                a[i][j / 2] = s[j] - '0';
            }
            else
            {
                cerr << "Error : Invalid Input" << endl;
                return 1;
            }
        }
    }
    file.close();
    initialize();
    if (!call(0))
        cout << "No Solution" << endl;
    else
        print();
    return 0;
}