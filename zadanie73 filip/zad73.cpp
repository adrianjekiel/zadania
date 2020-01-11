#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>


using namespace std;

vector<string> wczytaj (const string& nazwa)
{
    vector<string> slowa;
    string temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> temp)
        {
            slowa.push_back(temp);
        }
        input.close();
    }
    return slowa;
}

void zapisz (const string& nazwa, const vector<string>& odpowiedz)
{
    ofstream output(nazwa);
    if(output.is_open())
    {
        for(auto s : odpowiedz)
        {
            output << s << endl;
        }
        output.close();
    }
}

string zad1 (const vector<string> slowa)
{
    int licznik=0;
    for(string s:slowa)
    {
        for(int i=1; i<s.size();i++)
        {
            if(s[i]==s[i-1])
            {
                licznik++;
                break;
            }
        }
    }
    return  "zad1: " + to_string(licznik);
}
vector<string> zad2 (const vector<string> slowa)
{
    int wszystkie=0;
    vector<string> odp;
    std::map<char,int> litera_ilosc;
    for(int i = 0; i<26; i++)
    {

        litera_ilosc['A'+ i] = 0;
    }
    for(string s:slowa)
    {
        for(char a:s)
        {
            litera_ilosc[a]++;
            wszystkie++;
        }

    }
    for(auto elem : litera_ilosc) //mapa std::pair<char,int>
    {
        double precision = 0.01;
        double procent = (double(elem.second)/double(wszystkie))*100.0;
        double wart = round(procent/precision)*precision;
        stringstream ss;
        ss << elem.first <<": " <<elem.second << " (" << wart <<"%)";
        odp.push_back(ss.str()); //ss.str() wyluskuje stringa ze streama.
    }
    return odp;
}
int dlugosc_podslowa(string slowo)
{
    int dl_podslowa=0;
    int licznik=0;
    for(int i=0;i<slowo.size();i++)
    {
        if(slowo[i]!='A' and slowo[i]!='E' and slowo[i]!='I' and slowo[i]!='O' and slowo[i]!='U' and slowo[i]!='Y')
        {
            licznik++;
        }
        else
        {
            licznik=0;
        }
        if(licznik>dl_podslowa)
            {
                dl_podslowa=licznik;
            }
    }
    return dl_podslowa;
}

string zad3 (const vector<string>& dane)
{
    string maks_slowo;
    int licznik_maks_podslow=0;
    int maks_podslowo=0;
    for(string slowo: dane)
    {
        int dl_slowa = dlugosc_podslowa(slowo);
        if(dl_slowa>maks_podslowo)
        {
            maks_slowo=slowo;
            maks_podslowo=dl_slowa;
            licznik_maks_podslow=1;
        }
        else if(dl_slowa==maks_podslowo)
        {
            licznik_maks_podslow +=1;
        }
    }
    return "dlugosc najdluzszego slowa: " + to_string(maks_podslowo) + "ilosc slow o takiej dlugosci podslowa: " + to_string(licznik_maks_podslow)
        + "pierwsze najdluzsze podslowo: " + maks_slowo;
}



int main()
{
    vector<string> dane = wczytaj("tekst.txt");
    string odp_zad1 = zad1(dane);
    vector<string> odp_zad2 = zad2(dane);
    vector<string> odp;
    string odp_zad3 = zad3(dane);
    odp.push_back(odp_zad1);
    odp.insert(odp.end(),odp_zad2.begin(),odp_zad2.end());
    odp.push_back(odp_zad3);

    zapisz("wyniki.txt",odp);



}
