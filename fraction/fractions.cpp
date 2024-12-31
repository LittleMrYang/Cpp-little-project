#include <bits/stdc++.h>
using namespace std;
namespace fracs
{
    constexpr int Ipow(int bs, int r)
    {
        int mt = 1;
        while (r--)
            mt *= bs;
        return mt;
    }
    class ZeroDivisionError : exception
    {
        constexpr const char *what()
        {
            return "Zero Division Error";
        }
    };
    class fraction
    {
    private:
        unsigned fz, fm;
        bool nagative = 0;

    public:
        fraction(int fz = 1, int fm = 1) : fz(abs(fz)), fm(abs(fm)), nagative((fz < 0) ^ (fm < 0))
        {
            normalize();
        }
        fraction(string s)
        {
            nagative = s.front() == '-';
            fz = stoi(s.substr(nagative, s.find('/')));
            fm = stoi(s.substr(s.find('/') + 1, s.size() - s.find('/') - 1));
            normalize();
        }

        // void print()
        // {
        //     normalize();
        //     if (nagative)
        //         cout << "-";
        //     if (fm == 1)
        //         cout << fz;
        //     else
        //         cout << fz << "/" << fm;
        // }

        friend ostream &operator<<(ostream &os, fraction slf)
        {
            slf.normalize();
            if (slf.nagative)
                os << "-";
            if (slf.fm == 1)
                os << slf.fz;
            else
                os << slf.fz << "/" << slf.fm;
            return os;
        }
        void normalize()
        {
            if (fm == 0)
                throw ZeroDivisionError();
            int gdc = gcd(fz, fm);
            fz /= gdc;
            fm /= gdc;
            // nagative ^= (fz < 0) ^ (fm < 0);
            // fz = abs(fz), fm = abs(fm);
        }
        bool operator==(fraction b) const
        {
            if (nagative ^ b.nagative)
                return 0;
            return fz * b.fm == b.fz * fm;
        }
        bool operator!=(fraction b) const
        {
            return !(*this == b);
        }
        bool operator<(fraction b) const
        {
            if (nagative ^ b.nagative)
                return nagative > b.nagative;
            else
                return fz * b.fm < b.fz * fm;
        }
        bool operator>(fraction b) const
        {
            if (nagative ^ b.nagative)
                return nagative < b.nagative;
            else
                return fz * b.fm > b.fz * fm;
        }
        bool operator<=(fraction b) const
        {
            return !(*this > b);
        }
        bool operator>=(fraction b) const
        {
            return !(*this < b);
        }
        fraction operator-()
        {
            fraction tmp;
            tmp = *this;
            tmp.nagative ^= 1;
            return tmp;
        }
        fraction operator~()
        {
            fraction tmp;
            tmp.fz = fm;
            tmp.fm = fz;
            tmp.nagative = nagative;
            return tmp;
        }
        fraction operator+(fraction b)
        {
            fraction tmp;
            if (nagative ^ b.nagative)
            {
                tmp.fz = max(fz * b.fm, fm * b.fz) - min(fz * b.fm, fm * b.fz);
                tmp.nagative = (fz * b.fm == fm * b.fz ? 0 : (fz * b.fm > fm * b.fz ? nagative : b.nagative));
            }
            else
            {
                tmp.fz = fz * b.fm + fm * b.fz;
                tmp.nagative = nagative;
            }
            tmp.fm = fm * b.fm;
            tmp.normalize();
            return tmp;
        }
        fraction operator-(fraction b)
        {
            fraction tmp;
            tmp = *this + (-b);
            tmp.normalize();
            return tmp;
        }
        fraction operator*(fraction b)
        {
            fraction tmp;
            tmp.fz = fz * b.fz;
            tmp.fm = fm * b.fm;
            tmp.nagative = nagative ^ b.nagative;
            tmp.normalize();
            return tmp;
        }
        fraction operator/(fraction b)
        {
            fraction tmp;
            tmp.fz = fz * b.fm;
            tmp.fm = fm * b.fz;
            tmp.nagative = nagative ^ b.nagative;
            return tmp;
        }
        fraction operator=(fraction b)
        {
            fz = b.fz;
            fm = b.fm;
            nagative = b.nagative;
            return *this;
        }
        fraction operator+=(fraction b)
        {
            *this = *this + b;
            return *this;
        }
        fraction operator-=(fraction b)
        {
            *this = *this - b;
            return *this;
        }
        fraction operator*=(fraction b)
        {
            *this = *this * b;
            return *this;
        }
        fraction operator/=(fraction b)
        {
            *this = *this / b;
            pow(*this, 1);
            return *this;
        }
        friend constexpr fraction pow(fraction bs, int r)
        {
            fraction tmp;
            tmp.fz = Ipow(bs.fz, r);
            tmp.fm = Ipow(bs.fm, r);
            tmp.nagative = !(!bs.nagative || (bs.nagative && r % 2 == 0));
            return tmp;
        }
    };
}

using namespace fracs;

int main()
{
    return 0;
}
