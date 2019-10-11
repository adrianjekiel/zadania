#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> wczytaj(const string& nazwa)
{
    vector<int> dane;
    ifstream input(nazwa);
    if(input.is_open())
    {
        int chwilowka;
        while(input >> chwilowka)
        {
            dane.push_back(chwilowka);
        }
    input.close();
    }
    return dane;
}

string zad1(const vector<int>& dane)
{
    int licznik=0;
    int dzien=1;
    for(int i=1 ;i<dane.size();i++)
    {
        if(dane[i-1]<dane[i])//terazniejszy mniejszy od nastepnego czyli ok
        {
            dzien++;
        }
        else
        {
            if(dzien > 3)
            {
                licznik++;
            }
            dzien = 1; // przegrany dzien moze byc poczatkiem nowej passy xD
        }
    }
    return "zad1: \nilosc serii z dobra passa: " + std::to_string(licznik);
}

string zad2(const vector<int>& dane)
{
    int minint=0;
    int maxint=0;
    int maxskok=dane[0];
    int minskok=dane[0];
    for(int i=1; i<dane.size();i++)
    {
        if(maxskok>dane[i])
        {
            maxskok = dane[i];
            maxint = i+1; // elementy w tablicy od 0 ale nie ma zerowego skoku, wiec +1 powinno byc
        }
        if(minskok<dane[i])
        {
            minskok = dane[i];
            minint = i+1; // elementy w tablicy od 0 ale nie ma zerowego skoku, wiec +1 powinno byc
        }
    }

    return "zad 2: \nnajdluzszy skok = " + std::to_string(maxskok) + " jest to " + std::to_string(maxint) + " skok z kolei"
            "\nnajkrotszy skok =  " + std::to_string(minskok) + " jest to " + std::to_string(minint) + " skok z kolei";
}
string zad3(const vector<int>& dane)
{
    vector<int> temp_vec, max_vec;
    temp_vec.push_back(dane[0]); // bo pierwszy skok moze byc poczatkiem dobrej passy
    for(int i=1 ;i<dane.size();i++) // od 1 spoko, ale czemu size-1?
    {
        if(dane[i-1]<dane[i])//terazniejszy mniejszy od nastepnego czyli ok A: w zadaniu 1 zrobiles dobrze a tutaj taka skucha xD
        {
            temp_vec.push_back(dane[i]);
        }
        else
        {
            if(temp_vec.size()>max_vec.size())
            {
                max_vec = temp_vec;
//                temp_vec.clear(); // po co dwa razy? nizej tez clearujesz, jeden jest zbedny xd
            }
            temp_vec.clear();
            temp_vec.push_back(dane[i]); //bo to co przerwalo dobra passe jest poczatkiem nowej passy skokow
        }

    }
    int delta = max_vec.back()-max_vec.front();
    return "zad3: \ndlugosc = " + std::to_string(max_vec.size()) + " roznica = "+ std::to_string(delta);
}
void zapisz(const string& nazwa, const vector<string>& string_vec)
{
    ofstream output(nazwa);
    if(output.is_open())
    {
        for(auto s : string_vec)
        {
            cout << s << endl;
            output << s <<endl;
        }
        output.close();
    }
}

int main()
{
    vector<int> dane = wczytaj("dziennik.txt");
    vector<string> wyniki{zad1(dane), zad2(dane), zad3(dane)};
    zapisz("Wyniki.txt",wyniki);

    return 0;
}
