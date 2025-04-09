#include <bits/stdc++.h>
using namespace std;

template <typename t>
class Multiplication;
template <typename t>
class evaluation;
template <typename t>
class differentiation;

class my_string // my_string class for string operations
{
public:
    string s;
    my_string() { s = ""; } // default constructor
    my_string(string s1)
    {
        s = s1;
    }
    my_string operator*(long long int n) // string multiplication
    {
        my_string temp;
        for (auto i = 0; i < n; ++i)
        {
            temp.s += s;
        }
        return temp;
    }
    my_string operator+(const my_string &s2) // string concat
    {
        my_string temp;
        temp.s = s + s2.s;
        return temp;
    }
    void print()
    {
        cout << s << endl;
    }
};
class Complex // complex class for complex numbers
{
public:
    long long int r, i; // realpart,imajinary part
    Complex()
    {
        r = 0;
        i = 0;
    }
    Complex(long long int a, long long int b)
    {
        r = a;
        i = b;
    }
    Complex operator*(Complex c2)
    {
        // overloading operator * for complex numbers multiplication
        long long int a = r * c2.r - i * c2.i;
        long long int b = r * c2.i + i * c2.r;
        Complex c(a, b);
        return c;
    }
    Complex operator+(Complex c2)
    {
        // overloading operator + for comples numbers addition
        Complex c(r + c2.r, i + c2.i);
        return c;
    }
    Complex operator-(Complex c2)
    {
        // overloading operator - for complex number subtraction
        Complex c(r - c2.r, i - c2.i);
        return c;
    }
    void print()
    {
        cout << r << " " << i << " ";
    }
    template <typename t>
    friend class Multiplication;
    template <typename t>
    friend class evaluation;
    template <typename t>
    friend class differentiation;
};

template <typename t>
class Multiplication // templetized multiplication class
{
private:
    vector<t> coeff; // coefficent vector
public:
    Multiplication(vector<t> &v)
    {
        coeff = v;
    }

    vector<t> operator*(vector<t> &v)
    {
        long long int deg = coeff.size() - 1;
        long long int result_length = 2 * deg + 1;
        vector<t> result(result_length, t{});
        if (deg == 0)
        {
            result[0] = result[0] + (coeff[0] * v[0]);
            return result;
        }
        long long int part_len, part_deg;
        if (deg % 2 == 0)
        {
            part_deg = deg / 2;
            part_len = part_deg + 1;
        }
        else
        {
            part_deg = (deg + 1) / 2;
            part_len = part_deg;
        }
        vector<t> A1_coeff(part_len, t{}), A2_coeff(part_len, t{});
        vector<t> B1_coeff(part_len, t{}), B2_coeff(part_len, t{});
        for (long long int i = 0; i < part_len; ++i)
        {
            A1_coeff[i] = coeff[i];
            B1_coeff[i] = v[i];
        }
        for (long long int i = part_len; i <= deg; i++)
        {
            A2_coeff[i - deg + part_len - 1] = coeff[i];
            B2_coeff[i - deg + part_len - 1] = v[i];
        }
        Multiplication<t> A1(A1_coeff), A2(A2_coeff);
        vector<t> a1b1 = A1 * B1_coeff;
        vector<t> a2b2 = A2 * B2_coeff;
        vector<t> a1b2 = A1 * B2_coeff;
        vector<t> a2b1 = A2 * B1_coeff;
        long long int len = a1b2.size();
        vector<t> a1b2_a2b1(len);
        for (long long int i = 0; i < len; ++i)
        {
            a1b2_a2b1[i] = a1b2[i] + a2b1[i];
        }

        for (long long int i = 0; i < len; ++i)
        {
            result[i] = result[i] + a1b1[i];
        }
        for (long long int i = 0; i < len; ++i)
        {
            result[part_deg + i] = result[part_deg + i] + a1b2_a2b1[i];
        }
        for (long long int i = 0; i < len; ++i)
        {
            result[2 * part_deg + i] = result[2 * part_deg + i] + a2b2[i];
        }
        return result;
    }
};

template <typename t>
class evaluation // templetized evalutaion class
{
private:
    vector<t> coeff; // coefficent vector
    bool is_string;  // bool variable true if templete is string type else false;
    bool is_float;   // bool true if templete is float else false;

public:
    evaluation(vector<t> &v, bool is_s, bool is_f)
    {
        coeff = v;
        is_string = is_s;
        is_float = is_f;
    }

    void poly_eval(long long int x, t &res)
    {
        // evaluate polynomial and print
        long long int n = coeff.size();
        long long int p = 1;
        for (long long int i = 0; i < n - 1; ++i) // compute power hardcoded since pow fn gives wrong values if x is negative
        {
            p *= x;
        }
        for (long long int i = n - 1; i >= 0; i--) // evaluate poluynomial from back to faciliate string operations
        {
            res = res + coeff[i] * p;
            p /= x;
        }
    }
};

template <typename t>
class differentiation // templetized differentiation class
{
private:
    vector<t> coeff; // coefficent vector
    bool is_float;

public:
    differentiation(vector<t> &v, bool is_f)
    {
        coeff = v;
        is_float = is_f;
    }

    void dif()
    {
        // differentiate and print result
        long long int n = coeff.size();
        vector<t> res(n);
        for (long long int i = 1; i < n; i++) // differnctiate and storre
        {
            res[i] = coeff[i] * i;
        }
        for (long long int i = 1; i < n; ++i)
        {
            if (is_float)
            {
                cout << fixed << setprecision(6) << res[i] << " ";
            }
            else
            {
                cout << res[i] << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    long long int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            string data_type;
            cin >> data_type;
            if (data_type == "integer")
            {
                long long int deg1;
                cin >> deg1;
                vector<long long int> coeff1;
                for (long long int i = 0; i < deg1; i++)
                {
                    long long int x;
                    cin >> x;
                    coeff1.push_back(x);
                }
                long long int deg2;
                cin >> deg2;
                vector<long long int> coeff2;
                for (long long int i = 0; i < deg2; i++)
                {
                    long long int x;
                    cin >> x;
                    coeff2.push_back(x);
                }
                if (deg2 <= deg1) // push extra 0s to match lengths
                {
                    for (long long int i = deg2; i < deg1; ++i)
                    {
                        coeff2.push_back(0);
                    }
                }
                else
                { // push extra 0s to match lengths
                    for (long long int i = deg1; i < deg2; ++i)
                    {
                        coeff1.push_back(0);
                    }
                }
                Multiplication<long long int> m(coeff1);
                vector<long long int> result = m * coeff2;
                for (long long int i = 0; i < deg1 + deg2 - 1; ++i)
                {
                    cout << result[i] << " ";
                }
                cout << endl;
            }
            else if (data_type == "float")
            {
                long long int deg1;
                cin >> deg1;
                vector<long double> coeff1;
                for (long long int i = 0; i < deg1; i++)
                {
                    long double x;
                    cin >> x;
                    coeff1.push_back(x);
                }
                long long int deg2;
                cin >> deg2;
                vector<long double> coeff2;
                for (long long int i = 0; i < deg2; i++)
                {
                    long double x;
                    cin >> x;
                    coeff2.push_back(x);
                }
                if (deg2 <= deg1) // push extra 0s to match lengths
                {
                    for (long long int i = deg2; i < deg1; ++i)
                    {
                        coeff2.push_back(0.0);
                    }
                }
                else
                { // push extra 0s to match lengths
                    for (long long int i = deg1; i < deg2; ++i)
                    {
                        coeff1.push_back(0.0);
                    }
                }
                Multiplication<long double> m(coeff1);
                vector<long double> result = m * coeff2;
                for (long long int i = 0; i < deg1 + deg2 - 1; ++i)
                {
                    cout << fixed << setprecision(6) << result[i] << " ";
                }
                cout << endl;
            }
            else if (data_type == "complex")
            {
                long long int deg1;
                cin >> deg1;
                vector<Complex> coeff1;
                for (long long int i = 0; i < deg1; i++)
                {
                    long long int a, b;
                    cin >> a >> b;
                    coeff1.push_back(Complex(a, b));
                }
                long long int deg2;
                cin >> deg2;
                vector<Complex> coeff2;
                for (long long int i = 0; i < deg2; i++)
                {
                    long long int a, b;
                    cin >> a >> b;
                    coeff2.push_back(Complex(a, b));
                }
                if (deg2 <= deg1) // push extra 0s to match lengths
                {
                    for (long long int i = deg2; i < deg1; ++i)
                    {
                        coeff2.push_back(Complex(0, 0));
                    }
                }
                else
                { // push extra 0s to match lengths
                    for (long long int i = deg1; i < deg2; ++i)
                    {
                        coeff1.push_back(Complex(0, 0));
                    }
                }
                Multiplication<Complex> m(coeff1);
                vector<Complex> result = m * coeff2;
                for (long long int i = 0; i < deg1 + deg2 - 1; ++i)
                {
                    result[i].print();
                }
                cout << endl;
            }
        }
        else if (type == 2)
        {
            string data_type;
            cin >> data_type;
            bool is_float = false, is_string = false;
            if (data_type == "float")
            {
                is_float = true;
            }
            else if (data_type == "string")
            {
                is_string = true;
            }
            long long int deg;
            cin >> deg;
            if (is_string)
            {
                vector<my_string> coeff(deg);
                for (int i = 0; i < deg; i++)
                {
                    cin >> coeff[i].s;
                }
                evaluation<my_string> e(coeff, is_string, is_float);
                long long int x;
                cin >> x;
                my_string res("");
                e.poly_eval(x, res);
                cout << res.s << endl;
            }
            else if (is_float)
            {
                vector<long double> coeff(deg);
                for (int i = 0; i < deg; i++)
                {
                    cin >> coeff[i];
                }
                evaluation<long double> e(coeff, is_string, is_float);
                long long int x;
                cin >> x;
                long double res = 0;
                e.poly_eval(x, res);
                cout << fixed << setprecision(6) << res << endl;
            }
            else
            {
                vector<long long int> coeff(deg);
                for (int i = 0; i < deg; i++)
                {
                    cin >> coeff[i];
                }
                evaluation<long long int> e(coeff, is_string, is_float);
                long long int x;
                cin >> x;
                long long int res = 0;
                e.poly_eval(x, res);
                cout << res << endl;
            }
        }
        else if (type == 3)
        {
            string data_type;
            cin >> data_type;
            bool is_float = false;
            if (data_type == "float")
            {
                is_float = true;
            }
            long long int deg;
            cin >> deg;
            if (data_type == "integer")
            {
                vector<long long int> coeff(deg);
                for (auto i = 0; i < deg; ++i)
                {
                    cin >> coeff[i];
                }
                differentiation<long long int> d(coeff, is_float);
                d.dif();
            }
            else if (data_type == "float")
            {
                vector<long double> coeff(deg);
                for (auto i = 0; i < deg; ++i)
                {
                    cin >> coeff[i];
                }
                differentiation<long double> d(coeff, is_float);
                d.dif();
            }
        }
    }
}
