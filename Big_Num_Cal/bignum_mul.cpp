#include <iostream>
#include <string>
#include <algorithm>
#define MAXLEN 1000
using namespace std;

bool iszero(string s)
{
    int i;
    for (i = 0; i < s.length(); i++)
        if (s[i] != '0')
            break;
    return i == s.length();
}

void rmzero(string &s)
{
    int i = 0;
    while (s[0] == '0')
    {
        s = s.substr(1, s.length() - 1);
        i++;
    }
}

void addzero(string &s, int n, int flag)
{
    int i;
    if (flag == 0)
    {
        for (i = 0; i < n; i++)
            s = "0" + s;
    }
    else
    {
        for (i = 0; i < n; i++)
            s = s + "0";
    }
}

string add(string a, string b)
{
    if (iszero(a))
        return b;
    else if (iszero(b))
        return a;
    rmzero(a);
    rmzero(b);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int count = 0, in = 0, len, min_len;
    string res;
    len = max(a.length(), b.length());
    min_len = min(a.length(), b.length());
    while (count < len)
    {
        int tmp;
        if (count < min_len)
        {
            tmp = stoi(a.substr(count, 1)) + stoi(b.substr(count, 1)) + in;
        }
        else if (len == a.length())
        {
            tmp = in + stoi(a.substr(count, 1));
        }
        else
        {
            tmp = in + stoi(b.substr(count, 1));
        }
        res = to_string(tmp % 10) + res;
        in = tmp / 10;
        count++;
    }
    if (count == len && in == 1)
        res = "1" + res;
    return res;
}

//default a>b and commonly a.length() == b.length()
string sub(string a, string b)
{
    bool neg;
    if (iszero(b))
        return a;
    rmzero(a);
    rmzero(b);
    if (a.length() < b.length() || (a.length() == b.length() && stoi(a.substr(0, 1)) < stoi(b.substr(0, 1))))
    {
        string tmp;
        tmp = a;
        a = b;
        b = tmp;
        neg = true;
    }

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int count = 0, in = 0;
    string res;
    while (count < a.length())
    {
        int tmp;
        if (count < b.length())
        {
            tmp = stoi(a.substr(count, 1)) - stoi(b.substr(count, 1)) + in;
            in = 0;
            if (tmp < 0)
            {
                in = -1;
                tmp += 10;
            }
        }
        else
        {
            tmp = in + stoi(a.substr(count, 1));
            in = 0;
            if (tmp < 0)
            {
                in = -1;
                tmp += 10;
            }
        }
        res = to_string(tmp) + res;
        count++;
    }
    if (neg)
        res = "-" + res;
    return res;
}

string mul(string a, string b)
{
    string res;
    if (iszero(a) || iszero(b))
        return "0";
    int len_a, len_b, len, t;
    len_a = a.length();
    len_b = b.length();
    len = len_a > len_b ? len_a : len_b;
    t = 2;
    while (t < len)
        t *= 2;
    len = t;
    addzero(b, len - len_b, 0);
    addzero(a, len - len_a, 0);
    if (a.length() == 2)
    {
        return to_string(stoi(a) * stoi(b));
    }
    string tmp1, tmp2, tmp3, a1, a2, b1, b2;
    a1 = a.substr(0, a.length() / 2);
    a2 = a.substr(a.length() / 2, a.length() / 2);
    b1 = b.substr(0, b.length() / 2);
    b2 = b.substr(b.length() / 2, b.length() / 2);
    tmp1 = mul(a1, b1);
    //one more step after tmp3
    tmp2 = mul(a2, b2);

    tmp3 = sub(sub(mul(add(a1, a2), add(b1, b2)), tmp2), tmp1);

    addzero(tmp1, a.length(), 1);
    addzero(tmp3, a.length() / 2, 1);

    res = add(add(tmp1, tmp2), tmp3);
    return res;
}

int main()
{
    int i, n;
    freopen("in.dat","r",stdin);
    freopen("out.dat","w",stdout);
    cin >> n;
    for (i = 0; i < n; i++)
    {
        string a, b, res;
        int j, len;
        char op;
        bool neg_flag = false, af = false, bf = false;
        cin >> a;
        cin >> b;
        cin >> op;
        switch (op)
        {
        case '3':
            if (a.substr(0, 1) == "-")
            {
                a = a.substr(1, a.length() - 1);
                neg_flag = !neg_flag;
            }
            if (b.substr(0, 1) == "-")
            {
                b = b.substr(1, b.length() - 1);
                neg_flag = !neg_flag;
            }
            res = mul(a, b);
            break;
        case '2':
            if (a.substr(0, 1) == "-")
            {
                a = a.substr(1, a.length() - 1);
                af = true;
            }
            if (b.substr(0, 1) == "-")
            {
                b = b.substr(1, b.length() - 1);
                bf = true;
            }
            if (!af && !bf)
                res = sub(a, b);
            else if (af && !bf)
            {
                neg_flag = true;
                res = add(a, b);
            }
            else if (!af && bf)
            {

                res = add(a, b);
            }
            else
                res = sub(b, a);
            break;
        case '1':
            if (a.substr(0, 1) == "-")
            {
                a = a.substr(1, a.length() - 1);
                af = true;
            }
            if (b.substr(0, 1) == "-")
            {
                b = b.substr(1, b.length() - 1);
                bf = true;
            }
            if (!af && !bf)
                res = add(a, b);
            else if (af && !bf)
                res = sub(b, a);
            else if (!af && bf)
            {
                res = sub(a, b);
            }
            else
            {
                res = add(b, a);
                neg_flag = true;
            }
            break;
        default:
            break;
        }
        if (res.compare("0") != 0)
            rmzero(res);
        if (neg_flag)
            res = "-" + res;
        cout << res;
        if(i!=n-1)
            cout << endl;
    }
    return 0;
}