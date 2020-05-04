#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
//zmienne globalne

struct Napisy
{
    string s_1;
    string s_2;
};

vector<Napisy> wczytaj(const string& nazwa)
{
    vector<Napisy> napisy;
    string temp1,temp2;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input>>temp1 and input>>temp2)
        {
            napisy.push_back({temp1,temp2});
        }
    }
    input.close();
    return napisy;
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

bool czy_wsz_l_takie_same (const string& napis)
{
    for (const char& znak: napis)
    {
        if(znak != napis[0])
            return false;
    }
    return true;
}

string zad1 (const vector<Napisy>& napisy)
{
    int licznik=0;
    for(auto const& para:napisy)
    {
        if(czy_wsz_l_takie_same(para.s_1) and para.s_1==para.s_2)
            licznik++;
    }
    return "Zad1: " + to_string(licznik);
}

string zad2 (const vector<Napisy>& napisy)
{
    int licznik=0;
    for(auto para:napisy)
    {
        sort(para.s_1.begin(),para.s_1.end());
        sort(para.s_2.begin(),para.s_2.end());
        if(para.s_1==para.s_2)
            licznik++;
    }
    return "Zad2: " + to_string(licznik);

}

string zad3(vector<Napisy> napisy)
{
    for(auto& para:napisy)
    {
        sort(para.s_1.begin(),para.s_1.end());
        sort(para.s_2.begin(),para.s_2.end());
    }
    int licznik_maks=0;
    for(int i=0;i<napisy.size()-1;i++)
    {
        int licznik=1;
        int licznik2=1;
        if(napisy[i].s_1==napisy[i].s_2)
        {
            licznik++;
            licznik2++;
        }

        for(int j=i+1;j<napisy.size();j++)
        {
            if(napisy[i].s_1==napisy[j].s_1)
                licznik++;
            if(napisy[i].s_1==napisy[j].s_2)
                licznik++;
            if(napisy[i].s_2==napisy[j].s_1)
                licznik2++;
            if(napisy[i].s_2==napisy[j].s_2)
                licznik2++;
        }
        if(licznik>licznik_maks)
            licznik_maks=licznik;
        if(licznik2>licznik_maks)
            licznik_maks=licznik2;
    }
    return "zad3: " + to_string(licznik_maks);

}
main()
{
    auto dane = wczytaj("dane_napisy.txt");
    zapisz("wyniki.txt",{zad1(dane),zad2(dane),zad3(dane)});
}
