#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

enum Tryb
{
    szyfruj,
    odszyfruj
};

vector<string> wczytaj2(const string& nazwa)
{
    ifstream input(nazwa);
    string temp;
    vector<string> vec_s;
    if(input.is_open())
    {
        std::getline(input,temp);
        vec_s.push_back(temp);
        std::getline(input,temp);
        vec_s.push_back(temp);
    }
    input.close();
    return vec_s;
}
string wczytaj(const string& nazwa)
{
    ifstream input(nazwa);
    string temp;
    if(input.is_open())
    {
        std::getline(input,temp);
    }
    input.close();
    return temp;
}

string szyfruj_s (string dane,string klucz,Tryb tryb)
{
    int i=0;
    cout<<dane.size();
    while(i<dane.size()-1)
    {
        int j=0;
        while(j<klucz.size())
        {
            if(dane[i]>='A' and dane[i]<='Z')
            {
                if(tryb ==Tryb::szyfruj)//szyfruj
                {
                    int roznica = klucz[j]-'A';
                    int dana_i = dane[i]-'A';
                    dane[i]=((roznica+dana_i)%26)+'A';

                }
                if(tryb ==Tryb::odszyfruj)
                {
                    int dana_i = dane[i]-'A';
                    int roznica = klucz[j]-'A';
                    int wynik = dana_i - roznica;
                    cout<<dana_i<<" "<<roznica<<" "<<wynik<<endl;
                    if(wynik<0)
                    {
                        dane[i]=wynik+'Z'+1;
                    }
                    else
                    {
                        dane[i]=dane[i]-roznica;
                    }
                }
            cout<<dane[i]<<" "<<i<<" "<<j<<endl;
            j++;
            }
            i++;
        }
    }
    cout<<dane;
    return dane;
}

string zad1 (const string& dane)
{
    stringstream odp;
    odp<<"zad1: ";
    string klucz = "LUBIMYCZYTAC";
    int licznik=0;
    for(const char& litera:dane)
    {
        if(litera>= 'A' and litera<='Z')
        {
            licznik++;
        }
    }
    double l = licznik;
    double k = klucz.size();
    int wynik = std::ceil(l/k);
    odp<<wynik<<endl;
    odp<<szyfruj_s(dane,klucz,Tryb::szyfruj);
    return odp.str();
}
string zad2 (const vector<string>& dane)
{
    string szyfr = dane[0];
    string klucz = dane[1];
    stringstream odp;
    odp << "zad2: "<<endl;
    odp<<szyfruj_s(szyfr,klucz,Tryb::odszyfruj);
    return odp.str();
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
main()
{
    string dane = wczytaj("dokad.txt");
    vector<string> dane2 = wczytaj2("szyfr.txt");
    zapisz("wyniki.txt",{zad1(dane),zad2(dane2)});
}
