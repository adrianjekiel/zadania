#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> wczytaj(const string& nazwa)
{
    vector<int> wyrazy;
    vector<vector<int>> ciagi;
    int liczba;
    int ile_wyraz;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> ile_wyraz)
        {
            for(int i =0; i<ile_wyraz;i++)
            {
                input >> liczba;
                wyrazy.push_back(liczba);
            }
            ciagi.push_back(wyrazy);
            wyrazy.erase(wyrazy.begin(),wyrazy.end());
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

vector<string> zad1 (const vector<vector<int>>& ciagi)
{

    vector<string> odp;
    for(vector<int> wyrazy: ciagi)
    {
        for(int i=0;i<wyrazy.size();i++)
        {

        }
    }
}


int main ()
{

    vector<string> odp2;
    vector<string> odp3;
    vector<vector<int>> dane = wczytaj("ciagi.txt");
    vector<string> odp1 = zad1(dane);
    zapisz("wyniki1.txt",odp1);
    zapisz("wyniki2.txt",odp2);
    zapisz("wyniki3.txt",odp3);


}
