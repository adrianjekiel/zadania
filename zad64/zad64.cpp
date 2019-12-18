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

string zad1(const vector<Obraz>& obrazki)
{
    int licznik_rev=0;
    for(const auto& obraz :obrazki)
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
        {
            licznik_rev++;
        }
    }
    return "zad1: ilosc rewersow:" + to_string(licznik_rev);
}
string zad2 (const vector<Obraz>& obrazy)
{
    string odp;
    vector<Obraz> rekurencyjne;
    int licznik=0;
    for(const auto& obraz:obrazy)
    {
        bool czy_rekurencja = true;//flaga
        for(int w=0; w<10 ;w++)
        {
            for(int p=0;p<10;p++)
            {
                if(obraz.obraz[w][p]!=obraz.obraz[w][p+10] or obraz.obraz[w][p]!=obraz.obraz[w+10][p]
                   or obraz.obraz[w][p]!=obraz.obraz[w+10][p+10])
                {
                    czy_rekurencja=false;
                }
            }
        }
        if(czy_rekurencja)
        {
            licznik++;
            rekurencyjne.push_back(obraz);//robie wektor tylko z rekurencyjnymi
        }
    }
    vector<string> obrazek;
    string t;
    for(const auto& wiersz:rekurencyjne[0].obraz)
    {
        for(const auto& piksel: wiersz)
        {
            t.push_back(piksel);
        }
        obrazek.push_back(t);
    }
    return "zad2: ilosc rekurencyjnych: " + to_string(licznik);

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
    odp.push_back(zad2(dane));

    zapisz("wyniki.txt",odp);
}
