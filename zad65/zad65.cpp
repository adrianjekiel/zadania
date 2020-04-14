#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Ulamek
{
    int l;
    int m;
};

vector<Ulamek> wczytaj(const string& nazwa)
{
    vector<Ulamek> ulamki;
    int l_temp;
    int m_temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input>>l_temp and input>>m_temp)
        {
                ulamki.push_back({l_temp,m_temp});
        }
    }
    input.close();
    return ulamki;
}

void zapisz (const string& nazwa, const vector<string> odp)
{
    string temp;
    ofstream output(nazwa);
    if(output.is_open())
    {
        for(auto s: odp)
        {
            output << s <<endl;
        }
    }
    output.close();
}
bool operator < (const Ulamek& lhs, const Ulamek& rhs)
{
    return lhs.l*rhs.m < rhs.l*lhs.m;
}

bool operator == (const Ulamek& lhs, const Ulamek& rhs)
{
    return lhs.l*rhs.m == rhs.l*lhs.m;
}

string zad1 (const vector<Ulamek>& ulamki)
{
    Ulamek minim = ulamki[0];
    for(const auto& ulamek:ulamki)
    {
        if(ulamek<minim)
        {
            minim=ulamek;
        }
        else if(ulamek==minim and ulamek.m<minim.m)
        {
            minim=ulamek;
        }
    }
    return "zad1: " + to_string(minim.l) +"," + to_string(minim.m);
}
int nwd(int l,int m)
{
    if(m!=0)
        return nwd(m,l%m);
    return l;
}

string zad2 (const vector<Ulamek>& ulamki)
{
    int licznik=0;
    for(const auto& ulamek:ulamki)
    {
        if(nwd(ulamek.l,ulamek.m)==1)
            licznik++;
    }
    return "zad2: " + to_string(licznik);
}
string zad3 (const vector<Ulamek>& ulamki)
{
    int suma=0;
    for(const auto& ulamek:ulamki)
    {
        int dzielnik = nwd(ulamek.l,ulamek.m);
        suma=suma+ulamek.l/dzielnik;
    }
    return "zad3: " + to_string(suma);
}

string zad4 (const vector<Ulamek>& ulamki)
{
    long long suma=0;
    long long b=4*9*25*49*13;
    for(const auto& ulamek:ulamki)
    {
        long long a=ulamek.l;
        long long y=ulamek.m;
        long long licznik = a*b;
        suma=suma+((licznik)/y);
    }
    return "zad4: " + to_string(suma);
}

main()
{
    auto dane = wczytaj("dane_ulamki.txt");
    zapisz("wyniki.txt",{zad1(dane),zad2(dane),zad3(dane),zad4(dane)});
}
