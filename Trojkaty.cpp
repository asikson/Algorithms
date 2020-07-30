// Joanna Mielniczuk

#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct Point
{
    int x;
    int y;
};

struct Triangle
{
    Point a;
    Point b;
    Point c;
};

double dist(Point a, Point b)
{
    return sqrt((long long)(a.x - b.x)*(long long)(a.x - b.x) 
    + (long long)(a.y - b.y)*(long long)(a.y - b.y));
}

double circuit(Triangle t)
{
    return dist(t.a, t.b) + dist(t.b, t.c) + dist(t.c, t.a);
}

bool compare_x(Point a, Point b) { return a.x < b.x; }
bool compare_y(Point a, Point b) { return a.y < b.y; }

vector<Point> sort_x(vector<Point> v)
{
    vector<Point> result = v;
    sort(result.begin(), result.end(), compare_x);

    return result;
} 

vector<Point> sort_y(vector<Point> v)
{
    vector<Point> result = v;
    sort(result.begin(), result.end(), compare_y);

    return result;
}

Triangle find_triangle(vector<Point> Y, double dist_from_center)
{

    Triangle min_triangle = {Y[0], Y[1], Y[2]};
    double min_circ = circuit(min_triangle);

    for (int i=0; i < Y.size() - 2; i++)
    {
        for (int j=i+1; j < Y.size() - 1 && Y[j].y - Y[i].y <= dist_from_center; j++)
            for (int k=j+1; k < Y.size() && Y[k].y - Y[i].y <= dist_from_center; k++) 
            {
                Triangle current_triangle = {Y[i], Y[j], Y[k]};
                double current_circ = circuit(current_triangle);
                if (current_circ < min_circ)
                {
                    min_circ = current_circ;
                    min_triangle = current_triangle;
                } 
            }
    }
        
    return min_triangle;
}

Triangle recurrence(vector<Point> X, vector<Point> Y)
{
    // przy liczbie punktów mniejszej niż 6 sprawdzamy obwody ,,ręcznie"
    if (X.size() < 6)
    {
        if (X.size() == 3)
        {
            Triangle min_triangle = {X[0], X[1], X[2]};
            return min_triangle;
        }
        else 
        {
            double max_d = Y.back().y - Y.front().y;
            return find_triangle(Y, max_d);
        }
    }

    // podział danych na dwie części
    vector<Point> PL_X;
    vector<Point> PR_X;

    int k=0;
    while (k < X.size()/2)
    {
        PL_X.push_back(X[k]);
        k++;
    }
    while (k < X.size())
    {
        PR_X.push_back(X[k]);
        k++;
    }

    vector<Point> PL_Y = sort_y(PL_X);
    vector<Point> PR_Y = sort_y(PR_X);

    double middle = (PL_X.back().x + PR_X.front().x) / 2;

    Triangle t_left = recurrence(PL_X, PL_Y);
    Triangle t_right = recurrence(PR_X, PR_Y);
    Triangle t; // trójkąt o mniejszym obwodzie

    // scalenie wyniku
    if (circuit(t_left) < circuit(t_right)) t = t_left;
    else t = t_right;
    double min_circ = circuit(t);

    // sprawdzenie trójkątów stworzonych przez punkty z obu grup
    vector<Point> Y_prim;
    double dist_from_center = min_circ/2;

    for (int i=0; i < Y.size(); i++)
        if (abs(middle - Y[i].x) <= dist_from_center) Y_prim.push_back(Y[i]);

    // liczymy najmniejszy obwód, jeśli w wyznaczonym obszarze 
    // znajdą się przynajmniej 3 punkty
    if (Y_prim.size() > 2) 
    {
        Triangle found = find_triangle(Y_prim, dist_from_center);
        double min_found = circuit(found);
        if (min_found < min_circ) return found;
    }

    return t;
}


int main()
{
    // wczytanie liczby punktów
    int n;
    scanf("%d", &n);

    // wczytanie współrzędnych punktów
    vector<Point> points;
    int x;
    int y;
    for (int i=0; i<n; i++) 
    {
        scanf("%d %d", &x, &y);
        Point current = {x, y};
        points.push_back(current);
    }
    
    vector<Point> X = sort_x(points); // wektor wczytanych punktów posortowany po współrzędnej x
    vector<Point> Y = sort_y(points); // ... posortowany po współrzędnej y

    // wywołanie funkcji rekurencyjnej na wektorze z wszystkimi punktami
    Triangle found = recurrence(X, Y);

    // wypisanie wyniku
    printf("%d %d %d %d %d %d\n", found.a.x, found.a.y, found.b.x, found.b.y, found.c.x, found.c.y);
    
    return 0;
}
