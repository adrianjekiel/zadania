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
                string temp;
                input >> temp;
               for(int k = 0; k<21;k++)//kontekst obrazka kolumny
               {


                   if(w==20)
                   {
                        if(k!=20)
                        {
                            b_wiersz.push_back(temp[k]-48);
                        }
                   }
                   else
                   {
                       if(k<20)
                       {
                            wiersz.push_back(temp[k]-48);//-48 z char na int wzgledem kodow ASCII
                       }
                       else
                       {
                           b_kolumna.push_back(temp[k]-48);
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
    int maks_czarne=0;
    int licznik_rev=0;
    for(const auto& obraz :obrazki)
    {
        int czarne=0;
        int biale=0;
        for(const vector<int>& wiersz: obraz.obraz)
        {
            for(const int& piksel : wiersz)
            {
                if(piksel==1)
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
        if(czarne>maks_czarne)
        {
            maks_czarne=czarne;
        }
    }
    return "zad1: ilosc rewersow:" + to_string(licznik_rev) +"\nmaksymalna liczba czarnych: " + to_string(maks_czarne);
}
vector<string> zad2 (const vector<Obraz>& obrazy)
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
    vector<string> obrazek_odp;
    obrazek_odp.push_back("zad2: ilosc rekurencyjnych: " + to_string(licznik));
    obrazek_odp.push_back("opis obrazka: ");
    for(const auto& wiersz:rekurencyjne[0].obraz)
    {
        string t;
        for(const auto& piksel: wiersz)
        {
            t.push_back(piksel+48); //z int na char wzgledem ASCII
        }
        obrazek_odp.push_back(t);
    }
    return obrazek_odp;

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



vector<string> zad3 (const vector<Obraz>& obrazy)
{
    vector<string> odp;
    int naprawialny=0;
    int poprawny=0;
    int nienaprawialny=0;
    for(const auto& obraz: obrazy)
    {
        int zle_w=0;
        int zle_k=0;
        for(int w=0; w<20 ;w++)//wiersz
        {
            int czarne=0;
            for(int k=0;k<20;k++)
            {
                if(obraz.obraz[w][k])
                {
                    czarne++;
                }
            }
            if(czarne%2==0 and obraz.b_kolumna[w]==1 or czarne%2!=0 and obraz.b_kolumna[w]==0)
            {
                zle_w++;
            }
        }
         for(int k=0; k<20 ;k++)//wiersz
        {
            int czarne=0;
            for(int w=0;w<20;w++)
            {
                if(obraz.obraz[w][k])
                {
                    czarne++;
                }
            }

            if(czarne%2==0 and obraz.b_wiersz[k]==1 or czarne%2!=0 and obraz.b_wiersz[k]==0)
            {
                zle_k++;
            }

        }
        if(zle_w>1 or zle_k>1)
        {
            nienaprawialny++;
        }
        if((zle_w==0 and zle_k==1)or(zle_w==1 and(zle_k==1 or zle_k==0)))
        {
            naprawialny++;
        }
        if(zle_w==0 and zle_k==0)
        {
            poprawny++;
        }

    }
    odp.push_back("zad3: ");
    odp.push_back("liczba obrazow poprawnych: " + to_string(poprawny));
    odp.push_back("liczba obrazow naprawialnych: " + to_string(naprawialny));
    odp.push_back("liczba obrazow nienaprawialnych: " + to_string(nienaprawialny));
    return odp;

}
int ile_zlych_bitow_wiersz(const Obraz& obraz)
{
        int zle_w=0;
        for(int w=0; w<20 ;w++)//wiersz
        {
            int czarne=0;
            for(int k=0;k<20;k++)
            {
                if(obraz.obraz[w][k])
                {
                    czarne++;
                }
            }
            if(czarne%2==0 and obraz.b_kolumna[w]==1 or czarne%2!=0 and obraz.b_kolumna[w]==0)
            {
                zle_w++;
            }
        }
        return zle_w;
}
int ile_zlych_bitow_kolumna(const Obraz& obraz)
{
    int zle_k=0;
    for(int k=0; k<20 ;k++)//wiersz
    {
        int czarne=0;
        for(int w=0;w<20;w++)
        {
            if(obraz.obraz[w][k])
            {
                czarne++;
            }
        }
        if(czarne%2==0 and obraz.b_wiersz[k]==1 or czarne%2!=0 and obraz.b_wiersz[k]==0)
        {
            zle_k++;
        }
    }
    return zle_k;
}

int indeks_zlego_bitu_wiersz(const Obraz& obraz)
{
    int zle_w=0;
    for(int w=0; w<20 ;w++)//wiersz
    {
        int czarne=0;
        for(int k=0;k<20;k++)
        {
            if(obraz.obraz[w][k])
            {
                czarne++;
            }
        }
        if(czarne%2==0 and obraz.b_kolumna[w]==1 or czarne%2!=0 and obraz.b_kolumna[w]==0)
        {
            return w;
        }
    }
    return -1;
}

int indeks_zlego_bitu_kolumna(const Obraz& obraz)
{
    int zle_k=0;
    for(int k=0; k<20 ;k++)//wiersz
    {
        int czarne=0;
        for(int w=0;w<20;w++)
        {
            if(obraz.obraz[w][k])
            {
                czarne++;
            }
        }
        if(czarne%2==0 and obraz.b_wiersz[k]==1 or czarne%2!=0 and obraz.b_wiersz[k]==0)
        {
           return k;
        }
    }
    return -1;
}

bool czy_naprawialny(const Obraz& obraz)
{
    int zle_w = ile_zlych_bitow_wiersz(obraz);
    int zle_k = ile_zlych_bitow_kolumna(obraz);
    if((zle_w==0 and zle_k==1)or(zle_w==1 and(zle_k==1 or zle_k==0)))
    {
        return true;
    }
    return false;

}
bool czy_poprawny(const Obraz& obraz)
{
    int zle_w = ile_zlych_bitow_wiersz(obraz);
    int zle_k = ile_zlych_bitow_kolumna(obraz);
    if(zle_w==0 and zle_k==0)
    {
        return true;
    }
    return false;
}

vector<string> zad4 (const vector<Obraz>& obrazy)
{
    vector<string> odp;
    odp.push_back("zadanie 4:");
    odp.push_back("obrazy naprawialne: (numer obrazu, wiesz , kolumna) ");
    for(int i= 0;i<obrazy.size();i++)
    {
        if(czy_naprawialny(obrazy[i]))
        {
           int id_wiersz=indeks_zlego_bitu_wiersz(obrazy[i]);
           int id_kolumna=indeks_zlego_bitu_kolumna(obrazy[i]);
           if(id_kolumna>=0 and id_wiersz>=0)
           {
                odp.push_back("(" + to_string(i+1) + "," + to_string(id_wiersz+1) + "," + to_string(id_kolumna+1) + ")");
           }
           else if(id_kolumna>=0 and id_wiersz==-1)
           {
               odp.push_back("(" + to_string(i+1) + "," + "," + to_string(id_kolumna+1) + ")");
           }
           else
           {
               odp.push_back("(" + to_string(i+1) + "," + to_string(id_wiersz+1) + "," + ")");
           }

        }
    }
    return odp;
}

int main ()
{

    vector<Obraz> dane = wczytaj("dane_obrazki.txt");
    vector<string> odp;
    odp.push_back(zad1(dane));
    vector<string> zad2_odp = zad2(dane);
    vector<string> zad3_odp = zad3(dane);
    vector<string> zad4_odp = zad4(dane);
    odp.insert(odp.end(),zad2_odp.begin(),zad2_odp.end());
    odp.insert(odp.end(),zad3_odp.begin(),zad3_odp.end());
    odp.insert(odp.end(),zad4_odp.begin(),zad4_odp.end());



    zapisz("wyniki.txt",odp);
}
