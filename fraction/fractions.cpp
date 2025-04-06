#include <bits/stdc++.h>
using namespace std;
namespace maths_
{
    constexpr int Ipow(int bs, int r)
    {
        int mt = 1;
        while (r-- > 0)
            mt *= bs;
        return mt;
    }
    class ZeroDivisionError : exception
    {
        constexpr const char *what() noexcept
        {
            return "Zero Division Error";
        }
    };
    class struction_error : exception
    {
    private:
        string errType;

    public:
        struction_error() : errType("Bad struction") {}
        struction_error(string errT) : errType(errT) {}
        const char *what()
        {
            return errType.c_str();
        }
    };
    class fraction
    {
    private:
        unsigned long long fz, fm;
        bool nagative = 0;

    public:
        fraction(long long fz = 1, long long fm = 1) : fz(abs<long long>(fz)), fm(abs<long long>(fm)), nagative((fz < 0) ^ (fm < 0))
        {
            normalize();
        }
        fraction(string s)
        {
            nagative = s.front() == '-';
            fz = stoll(s.substr(nagative, s.find('/')));
            fm = stoll(s.substr(s.find('/') + 1, s.size() - s.find('/') - 1));
            normalize();
        }

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
        operator string()
        {
            ostringstream oss;
            oss << *this;
            return oss.str();
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
        double value()
        {
            return (double)fz / (double)fm;
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
        friend fraction operator-(fraction a)
        {
            fraction tmp;
            tmp = a;
            tmp.nagative ^= 1;
            return tmp;
        }
        friend fraction operator~(fraction a)
        {
            fraction tmp;
            tmp.fz = a.fm;
            tmp.fm = a.fz;
            tmp.nagative = a.nagative;
            return tmp;
        }
        friend fraction operator+(fraction a, fraction b)
        {
            fraction tmp;
            if (a.nagative ^ b.nagative)
            {
                tmp.fz = max(a.fz * b.fm, a.fm * b.fz) - min(a.fz * b.fm, a.fm * b.fz);
                tmp.nagative = (a.fz * b.fm == a.fm * b.fz ? 0 : (a.fz * b.fm > a.fm * b.fz ? a.nagative : b.nagative));
            }
            else
            {
                tmp.fz = a.fz * b.fm + a.fm * b.fz;
                tmp.nagative = a.nagative;
            }
            tmp.fm = a.fm * b.fm;
            tmp.normalize();
            return tmp;
        }
        friend fraction operator-(fraction a, fraction b)
        {
            fraction tmp;
            tmp = a + (-b);
            tmp.normalize();
            return tmp;
        }
        friend fraction operator*(fraction a, fraction b)
        {
            fraction tmp;
            tmp.fz = a.fz * b.fz;
            tmp.fm = a.fm * b.fm;
            tmp.nagative = a.nagative ^ b.nagative;
            tmp.normalize();
            return tmp;
        }
        friend fraction operator/(fraction a, fraction b)
        {
            fraction tmp;
            tmp = a * (~b);
            return tmp;
        }
        fraction operator=(fraction b)
        {
            fz = b.fz;
            fm = b.fm;
            nagative = b.nagative;
            return *this;
        }
        friend fraction &operator+=(fraction &a, fraction b)
        {
            a = a + b;
            return a;
        }
        friend fraction &operator-=(fraction &a, fraction b)
        {
            a = a - b;
            return a;
        }
        friend fraction &operator*=(fraction &a, fraction b)
        {
            a = a * b;
            return a;
        }
        friend fraction &operator/=(fraction &a, fraction b)
        {
            a = a / b;
            return a;
        }
        friend fraction pow(fraction bs, int r)
        {
            fraction tmp;
            tmp.fz = Ipow(bs.fz, r);
            tmp.fm = Ipow(bs.fm, r);
            tmp.nagative = !(!bs.nagative || (bs.nagative && r % 2 == 0));
            return tmp;
        }
    };
}
