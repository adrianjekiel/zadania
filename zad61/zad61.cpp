#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<vector<int>> wczytaj(const string& nazwa)
{
    vector<vector<int>> ciagi;
    int liczba;
    int ile_wyraz;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> ile_wyraz)
        {
            vector<int> wyrazy;
            for(int i =0; i<ile_wyraz;i++)
            {
                input >> liczba;
                wyrazy.push_back(liczba);
            }
            ciagi.push_back(wyrazy);
        }
    }
    input.close();
    return ciagi;
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
bool czy_arytm (const vector<int> wyrazy)
{
    int r = wyrazy[1]-wyrazy[0];
    for(int i=0;i<wyrazy.size()-1;i++)
    {
        if(r!=wyrazy[i+1]-wyrazy[i])
        {
            return false;
        }
    }
    return true;
}

vector<string> zad1 (const vector<vector<int>>& ciagi)
{
    vector<string> odp;
    int licznik=0;
    int rmax=0;
    int r=0;
    for(vector<int> wyrazy: ciagi)
    {
        if(czy_arytm(wyrazy))
        {
            licznik++;
            r=wyrazy[1]-wyrazy[0];
            if(rmax<r)
            {
                rmax=r;
            }
        }
    }
    odp.push_back("ilosc ciagow arytmetycznych: "+ to_string(licznik));
    odp.push_back("najwieksza roznica: "+to_string(rmax));
    return odp;
}
bool czy_szescian(const int& liczba)
{
    double epsilon = 0.0000001;
    double stopien = 1.0/3.0;
    double i = pow(liczba,stopien);
    if(abs(i-round(i))<epsilon)
    {
        return true;
    }
    else
    {
        return false;
    }
}
vector<string> zad2 (const vector<vector<int>>& ciagi)
{

    vector<string> odp;
    for(const vector<int>& wyrazy: ciagi)
    {
        int maxwyraz=0;
        for(int i=0;i<wyrazy.size();i++)
        {
            if(czy_szescian(wyrazy[i]))
            {
                if(maxwyraz<wyrazy[i])
                {
                    maxwyraz=wyrazy[i];
                }
            }
        }
        if(maxwyraz!=0)
        {
          odp.push_back(to_string(maxwyraz));
        }
    }
    return odp;
}

int wyznacz_r(const vector<int>& wyrazy)
{
    map<int,int> roznice;
    int r;
    for(int i=0;i<wyrazy.size()-1;i++)
    {
        r=wyrazy[i+1]-wyrazy[i];
        roznice[r]++;
    }
    for(const auto& para:roznice)
    {
        if(para.second>1)
        {
            return para.first;
        }
    }
    return 0;
}

int id_bledny (const vector<int>& wyrazy)
{
    int id;
    int r = wyznacz_r(wyrazy);
    for(int i=0;i<wyrazy.size()-1;i++)
    {
        if(r!=wyrazy[i+1]-wyrazy[i])
        {
            if(r!=wyrazy[i+2]-wyrazy[i+1])
            {
              id=i+1;
            }
            else
            {
              id=i;
            }
            break;
        }
    }
    return id;
}

vector<string> zad3 (const vector<vector<int>>& ciagi)
{
    vector<string> odp;
    for(const vector<int>& wyrazy: ciagi)
    {
        odp.push_back(to_string(wyrazy[id_bledny(wyrazy)]));
    }
    return odp;
}

int main ()
{

    vector<vector<int>> dane = wczytaj("ciagi.txt");
    vector<vector<int>> bledne_dane = wczytaj("bledne.txt");
    vector<string> odp1 = zad1(dane);
    vector<string> odp2 = zad2(dane);
    vector<string> odp3 = zad3(bledne_dane);
    zapisz("wyniki1.txt",odp1);
    zapisz("wyniki2.txt",odp2);
    zapisz("wyniki3.txt",odp3);


}
