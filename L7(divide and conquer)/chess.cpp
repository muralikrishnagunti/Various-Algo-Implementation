#include <bits/stdc++.h>
using namespace std;
struct point // struct for point
{
    long long int x, y, index;
};

long long int dist(point a, point b) // returns sq of distance between two points
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

class comparator // comparator class for sorting
{
public:
    bool operator()(long long int a, long long int b, string s)
    {
        if (s == "ascending")
        {
            return a < b;
        }
        else
        {
            return a > b;
        }
    }
};

class y_comp // comparator for sorting acc to y coordinate
{
public:
    bool operator()(point a, point b)
    {
        return a.y < b.y;
    }
};

class x_comp // comparator for sorting acc to x coordinate
{
public:
    bool operator()(point a, point b)
    {
        return a.x < b.x;
    }
};

void m_sort(vector<long long int> &v, long long int l, long long int r, string s) // sort function similar to merge sort
{
    if (r - l + 1 == 1)
    {
        return;
    }
    if (r - l + 1 == 2)
    {
        comparator com;
        if (!com(v[l], v[r], s))
        {
            swap(v[l], v[r]);
            return;
        }
    }
    else
    {
        long long int mid = (r + l) / 2;
        m_sort(v, l, mid, s);       // rec call
        m_sort(v, mid + 1, r, s);   // rec call
        vector<long long int> temp; // vector to store sorted elements
        long long int i = l, j = mid + 1;
        comparator com;
        while (i <= mid && j <= r)
        {
            if (com(v[i], v[j], s))
            {
                temp.push_back(v[i]);
                i++;
            }
            else
            {
                temp.push_back(v[j]);
                j++;
            }
        }
        while (i <= mid) // push remaining elements
        {
            temp.push_back(v[i]);
            i++;
        }
        while (j <= r) // push remaining elements
        {
            temp.push_back(v[j]);
            j++;
        }
        for (auto i = l; i <= r; ++i) // update original vector
        {
            v[i] = temp[i - l];
        }
        return;
    }
}

class chess
{
private:
    long long int n;
    vector<vector<long long int>> qv; // chess board
public:
    chess() {}

    void input() // take input
    {
        long long int n1;
        cin >> n1;
        n = n1;
        qv.resize(n, vector<long long int>(n));
        for (auto i = 0; i < n; ++i)
        {
            for (auto j = 0; j < n; ++j)
            {
                cin >> qv[i][j];
            }
        }
    }

    void sortRows(string s) // sort rows according to string s using
    {
        for (auto i = 0; i < n; ++i)
        {
            m_sort(qv[i], 0, n - 1, s);
        }
    }

    void countInversions() // prints no. of inversions
    {
        vector<long long int> v(n * n);
        for (auto i = 0; i < n; ++i)
        {
            for (auto j = 0; j < n; ++j)
            {
                v[n * i + j] = qv[i][j];
            }
        }
        cout << cnt_inv(v, 0, (n * n) - 1) << endl;
    }

    long long int cnt_inv(vector<long long int> &v, long long int l, long long int r) // counts no. of inversions using recursive call for 1st half, 2nd half and across both halves
    {
        if (r == l)
            return 0;
        long long int mid = (l + r) / 2;
        long long int l_cnt = cnt_inv(v, l, mid);
        long long int r_cnt = cnt_inv(v, mid + 1, r);
        long long int m_cnt = 0;
        vector<long long int> sv(r - l + 1);
        long long int i = l, j = mid + 1;
        long long int k = 0;
        while (i <= mid && j <= r)
        {
            if (v[i] > v[j])
            {
                m_cnt += (mid - i + 1); // add remaining no. of elements in i to cnt
                sv[k++] = v[j];
                j++;
            }
            else
            {
                sv[k++] = v[i];
                i++;
            }
        }
        while (i <= mid) // pushback remaining elements
        {
            sv[k++] = v[i];
            i++;
        }
        while (j <= r) // pushback remaining elements
        {
            sv[k++] = v[j];
            j++;
        }
        for (auto i = l; i <= r; ++i) // modify v to make it sorted
        {
            v[i] = sv[i - l];
        }
        return l_cnt + r_cnt + m_cnt;
    }

    void display() // print chess board
    {
        for (auto i = 0; i < n; ++i)
        {
            for (auto j = 0; j < n; ++j)
            {
                cout << qv[i][j] << " ";
            }
            cout << endl;
        }
    }

    void closestPair() // returns closest pair of points
    {
        long long int t;
        cin >> t;
        vector<point> v(t);
        for (auto i = 0; i < t; ++i)
        {
            cin >> v[i].x >> v[i].y;
            v[i].index = i;
        }

        x_comp xcm;
        sort(v.begin(), v.end(), xcm);

        pair<point, point> res = cp(v, 0, t - 1);
        cout << res.first.x << " " << res.first.y << " " << res.second.x << " " << res.second.y << endl;
    }

    pair<point, point> cp(vector<point> &v, long long int l, long long int r) // sort points according to x cord and recersively compute closest pair in 1st half,2nd half,find cross pairs also
    {
        if (r - l + 1 == 2) // base case for 2 points
        {
            if (v[l].index < v[r].index)
            {
                return make_pair(v[l], v[r]);
            }
            else
            {
                return make_pair(v[r], v[l]);
            }
        }
        if (r - l + 1 == 3) // base case for 3 points
        {
            long long int d1 = dist(v[l], v[l + 1]);     // distance btw point 1 and 2
            long long int d2 = dist(v[l + 1], v[l + 2]); // distance btw points 2 and 3
            long long int d3 = dist(v[l], v[l + 2]);     // distance btw points 1 and 3
            if (d1 <= d2 && d1 <= d3)                    // d1 is min
            {
                if (v[l].index < v[l + 1].index) // return acc to index
                {
                    return make_pair(v[l], v[l + 1]);
                }
                else
                {
                    return make_pair(v[l + 1], v[l]);
                }
            }
            else if (d2 <= d1 && d2 <= d3) // d2 is min
            {
                if (v[l + 1].index < v[l + 2].index) // return acc to index
                {
                    return make_pair(v[l + 1], v[l + 2]);
                }
                else
                {
                    return make_pair(v[l + 2], v[l + 1]);
                }
            }
            else if (d3 <= d1 && d3 <= d1) // d3 is min
            {
                if (v[l].index < v[l + 2].index) // return acc to index
                {
                    return make_pair(v[l], v[l + 2]);
                }
                else
                {
                    return make_pair(v[l + 2], v[l]);
                }
            }
        }

        long long int mid = (r + l) / 2;
        pair<point, point> left_pair = cp(v, l, mid);      // reccursive call
        pair<point, point> right_pair = cp(v, mid + 1, r); // recursive call

        long long int ld = dist(left_pair.first, left_pair.second);
        long long int rd = dist(right_pair.first, right_pair.second);

        long long int min_dist = min(ld, rd);

        long long int x_max_left = INT_MIN;
        for (auto i = l; i <= mid; ++i)
        {
            x_max_left = max(x_max_left, v[i].x);
        }

        vector<point> strip; // store elements within min_dist from x_max_left line
        for (auto i = l; i <= r; ++i)
        {
            if (abs(v[i].x - x_max_left) <= min_dist)
            {
                strip.push_back(v[i]);
            }
        }

        y_comp com;
        sort(strip.begin(), strip.end(), com); // sort acc to y cord

        pair<point, point> ans;
        if (ld < rd)
        {
            ans = left_pair;
        }
        else if (rd < ld)
        {
            ans = right_pair;
        }
        else
        {
            if (min(left_pair.first.x, left_pair.second.x) < min(right_pair.first.x, right_pair.second.x))
            {
                ans = left_pair;
            }
            else if (min(left_pair.first.x, left_pair.second.x) > min(right_pair.first.x, right_pair.second.x))
            {
                ans = right_pair;
            }
            else if (min(left_pair.first.y, left_pair.second.y) < min(right_pair.first.y, right_pair.second.y))
            {
                ans = left_pair;
            }
            else
            {
                ans = right_pair;
            }
        }

        long long int min_dist_cross = min_dist;
        for (auto i = 0; i < (long long int)strip.size(); ++i)
        {
            if (strip.size() == 1)
            {
                break;
            }
            long long int q = min(16ll, (long long int)strip.size() - i - 1);

            for (auto j = i; j < i + q; ++j)
            {
                for (auto k = j + 1; k <= i + q; ++k)
                {
                    long long int d = dist(strip[j], strip[k]);
                    if (d < min_dist_cross)
                    {
                        min_dist_cross = d;
                        if (strip[j].index < strip[k].index)
                        {
                            ans = make_pair(strip[j], strip[k]);
                        }
                        else
                        {
                            ans = make_pair(strip[k], strip[j]);
                        }
                    }
                    else if (d == min_dist_cross)
                    {
                        if (min(ans.first.x, ans.second.x) > min(strip[j].x, strip[k].x))
                        {
                            if (strip[j].index < strip[k].index)
                            {
                                ans = make_pair(strip[j], strip[k]);
                            }
                            else
                            {
                                ans = make_pair(strip[k], strip[j]);
                            }
                        }
                        else if (min(ans.first.x, ans.second.x) == min(strip[j].x, strip[k].x))
                        {
                            if (min(ans.first.y, ans.second.y) > min(strip[j].y, strip[k].y))
                            {
                                if (strip[j].index < strip[k].index)
                                {
                                    ans = make_pair(strip[j], strip[k]);
                                }
                                else
                                {
                                    ans = make_pair(strip[k], strip[j]);
                                }
                            }
                        }
                    }
                }
            }
        }

        if (min_dist_cross <= min(ld, rd))
        {
            return ans;
        }
        else if (ld < min(min_dist_cross, rd))
        {
            return left_pair;
        }
        else if (rd < min(min_dist_cross, ld))
        {
            return right_pair;
        }

        return ans;
    }
};
int main()
{
    chess c;
    while (1)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "CREATE_2D")
        {
            c.input();
        }
        if (cmd == "DISPLAY_2D")
        {
            c.display();
        }
        else if (cmd == "SORT_2D")
        {
            string order;
            cin >> order;
            c.sortRows(order);
        }
        else if (cmd == "INVERSION_2D")
        {
            c.countInversions();
        }
        else if (cmd == "CLOSEST_2D")
        {
            // assert(0);
            c.closestPair();
        }
        else if (cmd == "END")
        {
            return 0;
        }
    }
}