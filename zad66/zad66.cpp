#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;


vector<vector<int>> wczytaj(const string& nazwa)
{
    vector<vector<int>> trojki;
    vector<int> temp_vec;
    ifstream input(nazwa);
    if(input.is_open())
    {
        for(int j=0;j<1000;j++)
        {
            for(int i=0;i<3;i++)
            {
                int temp;
                input >> temp;
                temp_vec.push_back(temp);
            }
            trojki.push_back(temp_vec);
            temp_vec.clear();
        }
    }
    input.close();
    return trojki;
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
int zad1a (const int& a, const int& b)
{
    string a_s = to_string(a);
    string b_s = to_string(b);
    int suma=0;
    for(const char& znak:a_s)
    {
        int liczba;
        stringstream temp;
        temp << znak;
        temp >> liczba;
        suma=suma+liczba;
    }
     for(const char& znak:b_s)
    {
        int liczba;
        stringstream temp;
        temp << znak;
        temp >> liczba;
        suma=suma+liczba;
    }
    return suma;
}

string zad1 (const vector<vector<int>>& trojki)
{
    stringstream odp;
    odp << "zad1:\n";
    for(const auto& trojka : trojki)
    {
        if(zad1a(trojka[0],trojka[1])==trojka[2])
        {
            odp << trojka[0] << " "<<trojka[1] << " "<<trojka[2] <<"\n";
        }
    }
    return odp.str();
}

bool czy_pierwsza (const int& liczba)
{
    for(int n=2;n<liczba/2;n++)
    {
        if(liczba%n==0)
            return false;
    }
    return true;
}

string zad2 (const vector<vector<int>>& trojki)
{
    stringstream odp;
    odp << "zad2:\n";
    for(const auto& trojka : trojki)
    {
        if(czy_pierwsza(trojka[0]) and czy_pierwsza(trojka[1]) and trojka[0]*trojka[1]==trojka[2])
        {
            odp << trojka[0] << " "<<trojka[1] << " "<<trojka[2] <<"\n";
        }
    }
    return odp.str();
}

string zad3 (const vector<vector<int>>& trojki)
{
    stringstream odp;
    odp << "zad3:\n";

    for(const vector<int>& trojka : trojki)
    {
        long long a = trojka[0];
        long long b = trojka[1];
        long long c = trojka[2];
        vector<long long> temp = {a,b,c};
        sort(temp.begin(),temp.end());
        long long suma_kw = (pow(temp[0],2)+pow(temp[1],2))/100;
        long long wynik = pow(temp[2],2)/100;
        if(suma_kw==wynik)
        {
            odp << trojka[0] << " "<<trojka[1] << " "<<trojka[2] <<"\n";
        }
        temp.clear();
    }
    return odp.str();
}
string zad4 (const vector<vector<int>>& trojki)
{
    stringstream odp;
    odp << "zad4:\n";
    int licznik =0;
    int dl_c = 0;
    int dl_maks=0;
    bool ciag=false;
    for(vector<int> trojka : trojki)
    {
        sort(trojka.begin(),trojka.end());
        if(trojka[0]+trojka[1]>trojka[2])
        {
            licznik++;
            ciag=true;
        }
        else
        {
            ciag=false;
        }
        if(ciag)
        {
            dl_c++;
        }
        else
        {
            if(dl_maks<dl_c)
            {
                dl_maks=dl_c;
            }
            dl_c=0;
        }
    }
    odp << licznik<<"\n"<<dl_maks;
    return odp.str();
}

main()
{
    vector<vector<int>> trojki = wczytaj("trojki.txt");
    zapisz("wyniki.txt",{zad1(trojki),zad2(trojki),zad3(trojki),zad4(trojki)});
}
