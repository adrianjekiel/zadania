#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


vector<string> wczytaj (const string& nazwa)
{
    vector<string> temp_vec;
    string temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> temp)
        {
            temp_vec.push_back(temp);
        }
        input.close();
    }
    return temp_vec;
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

bool czypierwsza (const int& liczba)
{
    if(liczba<2)
        return false;
    for(int i=2; i<=sqrt(liczba);i++)
    {
        if(liczba%i==0)
            return false;
    }
    return true;
}

int summujznaki (const string& napis)
{
    int suma =0;
    for( auto znak : napis)
    {
        suma+=int(znak);
    }
    return suma;
}

bool czyrosnie (const string& napis)
{
    for(int i=1; i<napis.size() ;i++)
    {
        if(napis[i-1]>=napis[i])
            return false;
    }
    return true;
}

string zad1 (const vector<string> dane)
{
    int licznik = 0;
    for(auto napis : dane)
    {
        if(czypierwsza(summujznaki(napis)))
            licznik++;
    }
    return "zad a: \n" + to_string(licznik);
}

vector<string> zad2 (const vector<string> dane)
{
    vector<string> odp;
    odp.push_back("zad2:");
    for(auto napis : dane)
    {
        if(czyrosnie(napis))
        {
            odp.push_back(napis);
        }
    }
    return odp;

}
vector<string> zad3 (const vector<string> dane)
{
    vector<string> odp;
    odp.push_back("zad3:");
    for(auto napis : dane)
    {
        if(std::count(dane.begin(),dane.end(),napis)>1)
        {
	    if (std::find(odp.begin(), odp.end(), napis) == odp.end())
                odp.push_back(napis);
        }
    }
    return odp;
}


int main()
{
    vector<string> dane = wczytaj("NAPIS.TXT");
    //string wynik_zad1 = zad1(dane);
    vector<string> wyniki; //{wynik_zad1,zad2(dane),zad3(dane)};
    wyniki.push_back(zad1(dane));
    for(auto line : zad2(dane))
    {
        wyniki.push_back(line);
    }

    for(auto line : zad3(dane))
    {
        wyniki.push_back(line);
    }

    zapisz("Wyniki2.txt",wyniki);
}
