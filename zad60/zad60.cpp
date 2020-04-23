#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


vector<int> wczytaj(const string& nazwa)
{
    vector<int> liczby;
    int temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input>>temp)
        {
            liczby.push_back(temp);
        }
    }
    input.close();
    return liczby;
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

string zad1 (const vector<int>& liczby)
{
    int licznik=0;
    stringstream odp;
    odp << "zad1:"<<endl;
    for(const int& liczba:liczby)
    {
        if(liczba<1000)
            licznik++;
    }
    odp << "ilosc: " << licznik<<endl;
    int l=0;
    for(int i=liczby.size()-1;i>0;i--)
    {
        if(liczby[i]<1000)
        {
            odp << liczby[i]<< " ";
            l++;
        }
        if(l==2)
            break;
    }
    return odp.str();
}
vector<int> z_dzielniki (const int& liczba)
{
    vector<int> dziel;
    for(int n=1;n<=(liczba/2);n++)
    {
        if(liczba%n==0)
        {
            dziel.push_back(n);
        }
    }
    dziel.push_back(liczba);
    return dziel;
}
vector<int> w_dzielniki (const int& liczba) // dzielniki bez 1 bo zad3 nie dzia³a wtedy
{
    vector<int> dziel;
    for(int n=2;n<=(liczba/2);n++)
    {
        if(liczba%n==0)
        {
            dziel.push_back(n);
        }
    }
    dziel.push_back(liczba);
    return dziel;
}

string zad2 (const vector<int>& liczby)
{
    stringstream odp;
    odp << "zad2"<<endl;
    for(const int& liczba:liczby)
    {
        vector<int> dzielniki = z_dzielniki(liczba);
        if(dzielniki.size()==18)
        {
            odp << "liczba: "<< liczba<<" dzielniki: ";
            for(const int& dzielnik:dzielniki)
            {
                odp << dzielnik <<" ";
            }
            odp << endl;
        }
    }
    return odp.str();
}
bool czy_unikalne_dzielniki(const vector<int>& l_dzielniki, const vector<int>& p_dzielniki)
{
    for (const int l_dzielnik : l_dzielniki) // element z vectora l_dzielniki
    {
        for ( const auto p_dzielnik : p_dzielniki) // elemnt z vectora p_dzielniki
        {
            if (l_dzielnik == p_dzielnik) // jesli znajdziemy takie same liczby w tych dwóch zbiorach to zwracamy false, jako te dwa vectory nie sa wzgledem siebie unikalne
                return false;
        }
    }
    return true;
}


string zad3 (const vector<int>& liczby)
{
    stringstream odp;
    odp << "zad3: ";
    int max_liczba=0; // poczatkowe zmienne
    for (int i = 0; i < liczby.size(); i++) // idziemy po calym zbiorze, potrzebujemy tez znac miejsce sprawdzanej liczby, aby j¹ omin¹æ w dalszym sprawdzaniu
    {
        auto dzielniki_liczba = w_dzielniki(liczby[i]); // wyznaczamy dzielniki sprawdzanej liczby
        bool unikalny_ze_wszystkimi = true; // ustawiamy flage czy dana liczba ma unikalne dzielniki wzglêdem ca³ego zbioru

        for (int j = 0; j < i; j++) // lecimy od poczatku zbioru az do liczby ktora porownujemy
        {
            auto dzielniki_liczba2 = w_dzielniki(liczby[j]); // wyznaczamy dzielniki kolejnej liczby z ktora bedziemy sprawdzac unikalnosc
            if (!czy_unikalne_dzielniki(dzielniki_liczba, dzielniki_liczba2)) // sprawdzamy czy dzielniki sa unikalne, jesli nie, to flaga idzie na false
            {
                unikalny_ze_wszystkimi = false;
            }
        }

        for (int j = i+1; j < liczby.size(); j++) // omijamy liczbe na pozycji "i" i zaczynami od i+1
        {
            auto dzielniki_liczba2 = w_dzielniki(liczby[j]); // wyznaczamy dzielniki kolejnej liczby z ktora bedziemy sprawdzac unikalnosc
            if (!czy_unikalne_dzielniki(dzielniki_liczba, dzielniki_liczba2)) // sprawdzamy czy dzielniki sa unikalne, jesli nie, to flaga idzie na false
            {
                unikalny_ze_wszystkimi = false;
            }
        }

        if (unikalny_ze_wszystkimi and liczby[i] > max_liczba) // jesli liczba ma unikalne dzielniki wzgledem calego zbioru oraz jest najwieksza na tê chwilê to przypisujemy nowe max
        {
            max_liczba = liczby[i];
        }
    }
    odp << max_liczba;
    return odp.str();
}

main()
{
    auto dane = wczytaj("liczby.txt");
    zapisz("wyniki.txt",{zad1(dane),zad2(dane),zad3(dane)});
}
