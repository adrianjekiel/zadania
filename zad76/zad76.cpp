#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
using namespace std;



pair<vector<string>,vector<int>> wczytaj(const string& nazwa,const int& ilosc_slow, const int& dl_klucza)
{
    vector<string> s_vec;
    vector<int> i_vec;
    ifstream input(nazwa);
    if(input.is_open())
    {
        string temp;
        for(int i=0;i<ilosc_slow;i++)
        {
            input >> temp;
            s_vec.push_back(temp);
        }
        int tempi;
        for(int i=0;i<dl_klucza;i++)
        {
            input >> tempi;
            i_vec.push_back(tempi);
        }
    }
    input.close();
    return std::make_pair(s_vec,i_vec);
}

string szyfruj(string slowo, const vector<int>& klucz)
{
    for(int i=0;i<slowo.size();i++)
    {
        cout<<klucz[i%klucz.size()]<<" ";
        swap(slowo[i],slowo[klucz[i%klucz.size()]-1]);
    }
    return slowo;
}

string zad1 (const pair<vector<string>,vector<int>>& dane)
{
    stringstream odp;
    odp << "zad1: ";
    for(const auto& wiersz:dane.first)
    {
        odp << szyfruj(wiersz,dane.second)<<endl;
    }
    return odp.str();
}

string zad2 (const pair<vector<string>,vector<int>>& dane)
{
    stringstream odp;
    odp << "zad2: ";
    for(const auto& wiersz:dane.first)
    {
        odp << szyfruj(wiersz,dane.second)<<endl;
    }
    return odp.str();
}
string odszyfruj (string slowo, const vector<int>& klucz)
{
    for(int i=slowo.size()-1;i>=0;i--)
    {
        cout<<klucz[i%klucz.size()]<<" ";
        swap(slowo[i],slowo[klucz[i%klucz.size()]-1]);
    }
    return slowo;
}

string zad3 (const vector<string>& slowa, vector<int> klucz = {6,2,4,1,5,3})
{
    stringstream odp;
    odp << "zad3: ";
    odp << odszyfruj(slowa[0],klucz)<<endl;
    return odp.str();
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
    pair<vector<string>,vector<int>> dane1 = wczytaj("szyfr1.txt",6,50);
    pair<vector<string>,vector<int>> dane2 = wczytaj("szyfr2.txt",1,15);
    pair<vector<string>,vector<int>> dane3 = wczytaj("szyfr3.txt",1,0);
    zapisz("wyniki1.txt",{zad1(dane1)});
    zapisz("wyniki2.txt",{zad2(dane2)});
    zapisz("wyniki3.txt",{zad3(dane3.first)});
}
