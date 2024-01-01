#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Point
{
    int index;
    int x, y;
};


static int n;
static Point point[1000000];
static int index_a, index_b;

void input(const char* filename)
{
    ifstream f(filename);
    f >> n;
    for (int i = 0; i < n; i++)
    {
        f >> point[i].x >> point[i].y;
        point[i].index = i;
    }
    f.close();
}

void output(const char* filename)
{
    ofstream f(filename);
    f << index_a << " " << index_b;
    f.close();
}

bool abc_is_clockwise(Point a, Point b, Point c)
{
    int vector_area = (b.x - a.x) * (b.y - a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y);
    return vector_area > 0;
}

bool compare(Point a, Point b)
{
    return abc_is_clockwise(point[0], a, b);
}


void solve()
{
    sort(point + 1, point + n, compare);
    for (int i = 1 ; i < n; i++)
    {
        cout << point[i].index << " " << point[i].x << " " << point[i].y << endl;
    }
    index_a = 0;
    index_b = point[n / 2].index;
}

int main()
{
    input("input.txt");
    for (int i = 0; i < n; i++)
    {
        cout << point[i].index << " " << point[i].x << " " << point[i].y << endl;
    }
    solve();
    output("output.txt");
    return 0;
}