#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Obraz
{
    vector<int> b_wiersz;
    vector<int> b_kolumna;
    vector<vector<int>> obraz;
};

vector<Obraz> wczytaj (const string& nazwa)
{
    vector<Obraz> obrazy;

    ifstream input(nazwa);
    if(input.is_open())
    {
       for(int i = 0; i<200 ;i++) //200 obrazków
       {
           vector<int> b_wiersz;
           vector<int> b_kolumna;
           vector<vector<int>> obraz;
           for(int w = 0; w<21 ;w++)//kontekst obrazka wiersze
           {
               vector<int> wiersz;
               for(int k = 0; k<21;k++)//kontekst obrazka kolumny
               {

                   int temp;
                   input >> temp;
                   if(w==20)
                   {
                        b_wiersz.push_back(temp);
                   }
                   else
                   {
                       if(k<20)
                       {
                            wiersz.push_back(temp);
                       }
                       else
                       {
                           b_kolumna.push_back(temp);
                       }
                   }
               }
               obraz.push_back(wiersz);
           }
           obrazy.push_back(Obraz{b_wiersz,b_kolumna,obraz});
       }
        input.close();
    }
    return obrazy;
}
string zad1(const& vector<Obraz> obrazy)
{
    int licznik_rev=0;
    for(const auto& obraz :obrazy)
    {
        int czarne=0;
        int biale=0;
        for(const vector<int>& wiersz: obraz.obraz)
        {
            for(const int& piksel : wiersz)
            {
                if(piksel==0)
                {
                    czarne++;
                }
                else
                {
                    biale++;
                }
            }
        }
        if(czarne>biale)
            licznik_rev++;
    }
    return "zad1: ilosc rewersow:" + to_string(licznik_rev);
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

int main ()
{
    vector<Obraz> dane = wczytaj("dane_obrazki.txt");
    vector<string> odp;
    odp.push_back(zad1(dane));
    zapisz("wyniki.txt",odp);
}
