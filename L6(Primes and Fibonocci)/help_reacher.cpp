#include <bits/stdc++.h>
using namespace std;
long long int m = 1e9 + 7;

// partitions the array and returns index of pivot
long long int partition(vector<long long int> &v, long long int l, long long int r, long long int pivot)
{
    swap(v[r - 1], v[pivot]);
    long long int index = l - 1;
    for (long long int i = l; i < r; ++i)
    {
        if (v[i] < v[r - 1])
        {
            index++;
            swap(v[i], v[index]);
        }
    }
    swap(v[r - 1], v[index + 1]);
    return index + 1;
}
void quicksort(vector<long long int> &v, long long int l, long long int r)
{
    if (r - l <= 1) // base case
    {
        return;
    }
    long long int pivot = l; // 1st element as pivot
    long long int p = partition(v, l, r, pivot);
    quicksort(v, l, p);
    quicksort(v, p + 1, r);
}

class CurrencySorter
{
public:
    void operator()(vector<long long int> &v) // sorts v using quicksort
    {
        quicksort(v, 0, v.size());
    }
};

class FibonacciGenerator
{
public:
    long long int operator()(long long int n) // returns nth fibonacci number mod 10^9 +7 using functor
    {
        if (n == 1)
            return 0;
        if (n == 2)
            return 1;

        long long int a[2][2] = {{1, 1}, {1, 0}};   // find a^n-1
        long long int res[2][2] = {{1, 0}, {0, 1}}; // initializing to I
        long long int ex = n - 1;
        while (ex > 0)
        {
            if (ex % 2 == 1)
            {
                mult(res, a);
            }
            mult(a, a); // a^ex=a^2^ex/2
            ex /= 2;
        }
        return res[0][0];
    }

    void mult(long long int m1[2][2], long long int m2[2][2]) // multiplies two 2x2 matrices
    {
        long long int result[2][2] = {{0, 0}, {0, 0}};
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int k = 0; k < 2; ++k)
                {
                    result[i][j] = ((result[i][j]) + (((m1[i][k]) * (m2[k][j])) % m)) % m;
                }
            }
        }
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                m1[i][j] = result[i][j];
            }
        }
    }
};

class PrimeCalculator
{
private:
    vector<bool> v;
    vector<int> primes;

public:
    PrimeCalculator()
    {
        long long int s = 1000001;
        v.resize(s, true);
        v[1] = false;
        long long int p = 2;
        while (p < s)
        {
            primes.push_back(p); // push primes into primes
            for (long long int i = 2; (i)*p < s; i++)
            {
                v[i * p] = false; // all prime multiples are composite
            }
            p++;
            while (!v[p] && p < s) // compute next prime p
            {
                p++;
            }
        }
    }
    void printPrimes(long long int l, long long int r) // prints all the primes present in [l,r]
    {
        vector<bool> v(r - l + 1, true);
        for (int i = 0; i < (int)primes.size(); i++)
        {
            long long int p = primes[i];
            if (r < p)
                break;
            long long int start;
            if (l < p)
            {
                start = 2 * p;
            }
            else
            {
                // start=1st p multiple starting from l
                if (l % p == 0 && l != p)
                {
                    start = l;
                }
                else
                {
                    start = ((l / p) + 1) * p;
                }
            }
            for (long long int j = start; j <= r; j += p)
            {
                v[j - l] = false;
            }
        }
        for (int i = 0; i < (int)v.size(); i++)
        {
            if (v[i])
            {
                if (l + i != 1)
                {
                    cout << l + i << " ";
                }
            }
        }
        cout << endl;
    }
    long long int printPrimeSum(long long int l, long long int r) // returns sum of all primes in [l,r]
    {
        long long int sum = 0;
        vector<bool> v(r - l + 1, true);
        for (int i = 0; i < (int)primes.size(); i++)
        {
            long long int p = primes[i];
            if (p > r)
                break;
            long long int start;
            if (l < p)
            {
                start = 2 * p;
            }
            else
            {
                if (l % p == 0)
                {
                    start = l;
                }
                else
                {
                    start = ((l / p) + 1) * p;
                }
            }
            for (long long int j = start; j <= r; j += p)
            {
                v[j - l] = false;
            }
        }
        for (long long int i = 0; i < (long long int)v.size(); i++)
        {
            if (v[i])
            {
                if (l + i != 1)
                {
                    sum += (l + i);
                }
            }
        }
        return sum;
    }
};

class NumberAnalyzer
{
public:
    NumberAnalyzer() {}                // constructor
    bool isSquareFree(long long int n) // checks n is squarefree or not?
    {
        if (n % 2 == 0)
        {
            n /= 2;
            if (n % 2 == 0)
            {
                return false; // multiple of 4
            }
        }
        // now n is odd
        for (int i = 3; i * i <= n; i += 2)
        {
            if (n % i == 0)
            {
                n /= i;
                if (n % i == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
    long long int countDivisors(long long int n) // returns no of divisors of n
    {
        long long int cnt = 0;
        for (long long int i = 1; i * i <= n; ++i)
        {
            if (n % i == 0)
            {
                cnt += 1;
                if (i * i != n)
                {
                    cnt += 1;
                }
            }
        }
        return cnt;
    }
    long long int sumOfDivisors(long long int n) // returns sum of divisors of n
    {
        long long int sum = 0;
        for (long long int i = 1; i * i <= n; ++i)
        {
            if (n % i == 0)
            {
                sum += i;
                if (i * i != n)
                    sum += n / i;
            }
        }
        return sum;
    }
};

int main()
{
    int type;
    cin >> type;
    if (type == 1)
    {
        // assert(0);
        CurrencySorter cs;
        long long int t;
        cin >> t;
        while (t--)
        {
            // assert(0);
            long long int n;
            cin >> n;
            vector<long long int> v(n);
            for (auto i = 0; i < n; ++i)
            {
                cin >> v[i];
            }
            cs(v);
            for (auto i = 0; i < n; ++i)
            {
                cout << v[i] << " ";
            }
            cout << endl;
        }
    }
    else if (type == 2)
    {
        // assert(0);
        long long int t;
        cin >> t;
        FibonacciGenerator f;
        while (t--)
        {
            long long int n;
            cin >> n;
            cout << f(n) << endl;
        }
    }
    else if (type == 3)
    {
        // assert(0);
        PrimeCalculator pc;
        long long int t;
        cin >> t;
        while (t--)
        {
            string cmd;
            cin >> cmd;
            if (cmd == "printPrimes")
            {
                long long int l, r;
                cin >> l >> r;
                pc.printPrimes(l, r);
            }
            else if (cmd == "printPrimeSum")
            {
                long long int l, r;
                cin >> l >> r;
                cout << pc.printPrimeSum(l, r) << endl;
            }
        }
    }
    else if (type == 4)
    {
        // assert(0);
        NumberAnalyzer na;
        long long int t;
        cin >> t;
        while (t--)
        {
            string cmd;
            cin >> cmd;
            if (cmd == "isSquareFree")
            {
                long long int n;
                cin >> n;
                if (na.isSquareFree(n))
                {
                    cout << "yes" << endl;
                }
                else
                {
                    cout << "no" << endl;
                }
            }
            else if (cmd == "countDivisors")
            {
                long long int n;
                cin >> n;
                cout << na.countDivisors(n) << endl;
            }
            else if (cmd == "sumOfDivisors")
            {
                long long int n;
                cin >> n;
                cout << na.sumOfDivisors(n) << endl;
            }
        }
    }
}