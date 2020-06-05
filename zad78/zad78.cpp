#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

struct Wiad_podpis
{
    string wiad;
    vector<int> podpis;
};

vector<Wiad_podpis> wczytaj(const string& wiadomosci,const string& podpisy)
{
    ifstream wiad(wiadomosci);
    ifstream podp(podpisy);
    string wiadomosc;
    vector<Wiad_podpis> wiad_podpis;
    if(wiad.is_open() and podp.is_open())
    {
        for(int i=0;i<11;i++)
        {
            int temp_int;
            vector<int> podpis;
            std::getline(wiad,wiadomosc);
            for(int j=0;j<8;j++)
            {
                podp >> temp_int;
                podpis.push_back(temp_int);
            }
            wiad_podpis.push_back(Wiad_podpis{wiadomosc,podpis});
        }
    }
    wiad.close();
    podp.close();
    return wiad_podpis;
}
string skrot(string wiadomosc)
{
    string S = "ALGORYTM";
    int wielokrotnosc = wiadomosc.size()%8;
    for(int i=0;i<wielokrotnosc;i++)
    {
        wiadomosc.push_back('.');
    }

    int i=0;
    while(i<wiadomosc.size())
    {
        int j=0;
        while(j<8)
        {
            S[j]=S[j]+(wiadomosc[i]%128);
            j++;
            if(i>=wiadomosc.size())
                break;
            i++;
        }
    }
    cout<<S;
    for(char& znak:S)
    {
        znak = 65+znak%26;
    }
    cout<<S;
    return S;
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
    vector<Wiad_podpis> dane = wczytaj("wiadomosci.txt","podpisy.txt");
    zapisz("wyniki.txt",{skrot(dane[0].wiad)});
}
