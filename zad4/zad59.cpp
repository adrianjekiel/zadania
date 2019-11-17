
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <map>

using namespace std;


vector<int> wczytaj (const string& nazwa)
{
    vector<int> liczby;
    int temp_liczba;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> temp_liczba)
        {
            liczby.push_back(temp_liczba);
        }
        input.close();
    }
    return liczby;
}

void zapisz (const string& nazwa, const vector<string>& string_vec)
{
    ofstream output(nazwa);
    if(output.is_open())
    {
        for(auto s : string_vec)
        {
            output << s <<endl;
        }
        output.close();
    }

}

vector<int> czynniki (int liczba)
{
    vector<int> vec_czynniki;
    int aktualny_czynnik = 2;
    while(liczba!=1)
    {
        if(liczba%aktualny_czynnik == 0)
        {
            vec_czynniki.push_back(aktualny_czynnik);
            liczba = liczba/aktualny_czynnik;
        }
        else
        {
            aktualny_czynnik++;
        }
    }
    return vec_czynniki;
}

bool trzy_roz_nieparz (vector<int> czynniki)
{
    czynniki.erase(std::unique(czynniki.begin(),czynniki.end()),czynniki.end());
    if(czynniki.size() == 3)
    {
        for(int i : czynniki)
        {
            if(i%2 == 0)
                return false;
        }
        return true;
    }
    return false;
}

string zad1(const vector<int> liczby)
{
    int licznik=0;
    for(auto liczba: liczby)
    {
        if(trzy_roz_nieparz(czynniki(liczba)))
        {
            licznik++;
        }
    }
    return "zad1: " + to_string(licznik);
}

int rev_suma(int liczba)
{
    string s_liczba = to_string(liczba);
    string rs_liczba {s_liczba.rbegin(),s_liczba.rend()};
    return stoi(rs_liczba)+liczba;
}

bool czypalindrom (int n)
{
    string suma = to_string(n);
    for(int i=0; i<suma.size()/2;i++)
    {
        if(suma[i]!=suma[(suma.size()-i)-1])
        {
            return false;
        }
    }
    return true;
}

string zad2 (const vector<int> liczby)
{
    int licznik=0;
    for(auto liczba: liczby)
    {
        if(czypalindrom(rev_suma(liczba)))
        {
            licznik++;
        }
    }
    return "zad2: " + to_string(licznik);
}
int oblicz_moc (int liczba)
{
    int wynik = liczba;//zeby minimum raz wykona³a sie petla while
    int moc = 0;
    while(wynik>9)
    {
        string s_liczba = to_string(wynik);
        int iloczyn = 1;
        for(auto cyfra : s_liczba)
        {
            iloczyn = (cyfra-48)*iloczyn;
        }
        moc++;
        wynik=iloczyn;
    }
    return moc;
}

vector<string> zad3 (const vector<int> liczby)
{
    vector<string> odp;
    map<int,vector<int>> mapaliczb;
    for(auto liczba :liczby)
    {
        int moc = oblicz_moc(liczba);
        if(moc>0 and moc<9)
        {
            mapaliczb[moc].push_back(liczba);
        }
    }
    mapaliczb[7];
    //odp.push_back("moc 1: " + to_string(mapaliczb[1].size()));//
    for(auto elem : mapaliczb) //mapa std::pair<int, vector<int>>
    {
        odp.push_back("moc "+to_string(elem.first) + " " + to_string(elem.second.size()));
    }
    int maks = mapaliczb[1][0];
    int mini = mapaliczb[1][0];
    for(auto liczba : mapaliczb[1])
    {
        if(liczba>maks)
            maks=liczba;
        if(liczba<mini)
            mini=liczba;
    }
    odp.push_back("minimalna liczba o mocy 1 :" + to_string(mini));
    odp.push_back("maksymalna liczba o mocy 1 :" + to_string(maks));
    return odp;
}

int main()
{
    vector<int> dane = wczytaj("Liczby.txt");
    string odp1 = zad1(dane);
    string odp2 = zad2(dane);
    vector<string> odp3 = zad3(dane);

    vector<string> wyniki;
    wyniki.push_back(odp1);
    wyniki.push_back(odp2);
    wyniki.insert(wyniki.end(),odp3.begin(),odp3.end());
    zapisz("wyniki_liczby.txt",wyniki);
}
