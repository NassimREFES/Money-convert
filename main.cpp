//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
//------------------------------------------------------------------------
//----------------------------
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
//----------------------------
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::exception;
using std::runtime_error;
using std::string;
using std::ostream;
using std::istream;
using std::vector;

//----------------------------
//------------------------------------------------------------------------

void error(string s)
{
    throw runtime_error(s);
}

void keep_win_open(string s)
{
    cin.clear();
    string l;
    while(cin>>l && l!=s){}
    return;
}
//------------------------------------------------------------------------
class Money{
public:
        Money(string,long,int);
        Money(string,double);
        Money();
        long get_d() const {return dollar;}
        int get_c() const {return cent;}
        string get_k() const {return currency;}
protected:
    long dollar;
    int cent;
    string currency;
};

//------------------------------------------------------------------------

vector<string> crr;
vector<double> val;

//------------------------------------------------------------------------



//------------------------------------------------------------------------

long make_d(double d)
{
    return long(d);
}

//------------------------------------------------------------------------

int abs(int a)
{
    return (a<0)?-a:a;
}
double abs(double a)
{
    return (a<0)?-a:a;
}


int make_c(double d)
{
    d-=make_d(d);
    d*=1000;
    int round = int(d)%10;
    int cent = int(d)/10;
    return (round>=5) ?cent+1:cent;

}

//------------------------------------------------------------------------

double make_double(Money m)
{
    double a = m.get_d();
    double b = (double) m.get_c()/100;
    return a+b;

}

//------------------------------------------------------------------------

Money::Money(string s,long d,int c)
    : currency(s),dollar(d),cent(c) {}

//------------------------------------------------------------------------

Money::Money(string s,double m)
    : currency(s),dollar((m<0)? make_d(-abs(m)):make_d(abs(m))),cent(abs(make_c(m))) { }

//------------------------------------------------------------------------

Money::Money()
    : dollar(0),cent(0) {}

//------------------------------------------------------------------------

ostream& operator<<(ostream& os,const Money& m)
{
    return os << m.get_k() << ' ' << m.get_d() << '.' << m.get_c() << '\n';
}

//------------------------------------------------------------------------

istream& operator>>(istream& is,Money& m)
{
    string s;
    long d=0;
    char p=' ';
    int c=0;
    is >> s >> d >> p >> c;
    if (s.size()>3 || p!='.' || d<0) error("invalid money");
    m=Money(s,d,c);
    return is;
}

//------------------------------------------------------------------------

Money convert(const Money& m)
{
    for(int i = 0 ; i < crr.size() ; ++i)
        if(m.get_k()==crr[i]) return Money("USD",make_double(m)*val[i]);
    error("No such concurecy!");
}

//------------------------------------------------------------------------

Money operator+(const Money& m1,const Money m2)
{
    return Money("USD",make_double(convert(m1))+make_double(convert(m2)));
}

//------------------------------------------------------------------------

Money operator-(const Money& m1,const Money m2)
{
    double l = make_double(convert(m1))-make_double(convert(m2));
    if(l<0 && abs(l)<1)  return Money("USD -",l);
    return Money("USD",l);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void fill(vector<string>& v,vector<double>& d)
{
    v.push_back("USD");
    v.push_back("SAR");
    v.push_back("AUD");
    v.push_back("CAD");
    v.push_back("GBP");
    v.push_back("JPY");
    v.push_back("EUR");
    v.push_back("RUB");

    d.push_back(1.0);
    d.push_back(0.267008);
    d.push_back(1.0421);
    d.push_back(1.01076);
    d.push_back(1.56995);
    d.push_back(0.0125699);
    d.push_back(1.23343);
    d.push_back(0.0311935);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------


//------------------------------------------------------------------------

int main()
try{
    fill(crr,val);
    Money m("USD",15.19);
    Money m2("USD",10.33);
    Money k=m2-m;
    cout << k;
}
catch(exception& err)
{
    cerr << "Error : " << err.what() << endl;
    return 1;
}
catch(...)
{
    cerr << "Unknown error!" << endl;
    return 2;
}
//------------------------------------------------------------------------
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
// exo 16 - 17
// a rational number is an exact value whereas Money is an aproximation
// acheived by the rounding rule ,and double is also an aproximation which
// is relatively more accurate than Money ex : Pi = 22/7 = 3.14159...
