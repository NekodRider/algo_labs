#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAXN 10000
#define INF 999999
using namespace std;
struct Point
{
    int x, y;

  public:
    double getDist(Point &b) const
    {
        return sqrt(pow(x - b.x, 2) + pow(y - b.y, 2));
    }
    bool operator==(Point b)
    {
        return x == b.x && y == b.y;
    }
};
struct Pair
{
    Point a, b;
    double dist;
};
struct Pairs
{
    int count;
    Pair p[100];
    double dist;
    Pairs()
    {
        count = 0;
        dist = INF;
    }
};
bool cmpx(Point a, Point b)
{
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
bool cmpy(Point a, Point b)
{
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}
Pairs getClosestPair(int begin, int end, Point p[])
{
    int i, j;
    Pairs res;
    Pair s;
    s.a = p[begin];
    s.b = p[begin];
    s.dist = INF;
    res.count = 0;
    for (i = begin; i < end; i++)
    {
        for (j = i + 1; j < end; j++)
        {
            double dist = p[i].getDist(p[j]);
            if (dist <= s.dist)
            {
                if (dist < s.dist)
                {
                    res.count = 0;
                    res.dist = dist;
                }
                s.dist = dist;
                s.a = p[i];
                s.b = p[j];
                res.p[res.count] = s;
                res.count++;
            }
        }
    }
    return res;
}
Pairs getAreaPair(int begin, int end, Point p[])
{
    Pairs left, right, mid, res;
    Point tmp[100];
    bool l_flag = 0;
    int i, divide = (end + begin) / 2, count;
    double dist;
    if (begin + 1 == end)
    {
        Pair rr;
        Pairs r;
        r.count = 1;
        rr.a = p[begin];
        rr.b = p[end];
        r.dist = rr.dist = p[begin].getDist(p[end]);
        r.p[0] = rr;
        return r;
    }
    left = getAreaPair(begin, divide, p);
    right = getAreaPair(divide, end, p);
    if (left.dist < right.dist)
    {
        dist = left.dist;
        l_flag = true;
        res = left;
    }
    else if (left.dist > right.dist)
    {
        dist = right.dist;
        res = right;
    }
    else
    {
        dist = left.dist;
        res = left;
        for (i = 0; i < right.count; i++)
        {
            int flag = 0, j;
            for (j = 0; j < res.count; j++)
            {
                if ((res.p[j].a == right.p[i].a && res.p[j].b == right.p[i].b) || (res.p[j].a == right.p[i].b && res.p[j].b == right.p[i].a))
                {
                    flag = 1;
                    res.count--;
                    break;
                }
            }
            if (flag != 1)
                res.p[res.count + i] = right.p[i];
        }
        res.count += right.count;
    }

    count = 0;
    for (i = divide; i >= begin && p[divide].x - p[i].x < dist; i--)
        tmp[count++] = p[i];
    for (i = divide + 1; i < end && p[divide].x - p[i].x < dist; i++)
        tmp[count++] = p[i];
    sort(tmp, tmp + count, cmpy);
    mid = getClosestPair(0, count - 1, tmp);

    if (mid.dist < dist)
        res = mid;
    else if (mid.dist == dist)
    {
        for (i = 0; i < mid.count; i++)
        {
            int flag = 0, j;
            for (j = 0; j < res.count; j++)
            {
                if ((res.p[j].a == mid.p[i].a && res.p[j].b == mid.p[i].b) || (res.p[j].a == mid.p[i].b && res.p[j].b == mid.p[i].a))
                {
                    flag = 1;
                    res.count--;
                    break;
                }
            }
            if (flag != 1)
                res.p[res.count + i] = mid.p[i];
        }
        res.count += mid.count;
    }
    int j,k;
    for (i = 0; i < res.count; i++)
    {
        for (j = i+1; j < res.count; j++)
        {
            if ((res.p[j].a == res.p[i].a && res.p[j].b == res.p[i].b) || (res.p[j].a == res.p[i].b && res.p[j].b == res.p[i].a))
            {
                for(k=j;k<res.count-1;k++){
                    res.p[k]=res.p[k+1];
                }
                res.count--;
                break;
            }
        }
    }
    return res;
}

int main()
{
    int i, n, x, y, N, j;
    Point p[MAXN];
    Pairs res;
    freopen("in.dat", "r", stdin);
    freopen("out.dat", "w", stdout);
    scanf("%d", &N);
    for (j = 0; j < N; j++)
    {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            scanf("%d%d", &x, &y);
            p[i].x = x;
            p[i].y = y;
        }
        sort(p, p + n, cmpx);
        res = getAreaPair(0, n - 1, p);
        for (i = 0; i < res.count; i++)
            printf("%d %d %d %d\n", res.p[i].a.x, res.p[i].a.y, res.p[i].b.x, res.p[i].b.y);
    }
    return 0;
}