#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

vector<int> wczytaj(const string& nazwa)
{
    vector<int> liczby;
    int liczba;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> liczba)
        {
            liczby.push_back(liczba);
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
bool czy_prostokatne(const int& a,const int& b,const int& c)
{
    if(c>a and c>b)
    {
        cout<<a<<" "<<b<<" "<<c<<endl;
        cout<<"dupa1"<<endl;
        if(c*c==b*b + a*a)
        {
            cout<<"dupaaaaa"<<endl;
            cout<<a<<" "<<b<<" "<<c<<endl;
            return true;
        }
    }
    if(b>a and b>c)
    {

        if(pow(b,2)==pow(c,2)+pow(a,2))
        {
            return true;
        }
    }
    if(a>c and a>b)
    {

        if(pow(a,2)==pow(b,2)+pow(c,2))
        {
            return true;
        }
    }
    return false;
}


vector<string> zad1 (const vector<int>& liczby)
{
    vector<string> odp;
    odp.push_back("zad1:");
    for(int i=0;i<liczby.size()-2;i++)
    {
        if(czy_prostokatne(liczby[i],liczby[i+1],liczby[i+2]))
        {
            odp.push_back(to_string(liczby[i])+","+to_string(liczby[i+1])+","+to_string(liczby[i+2]));
        }
    }
    return odp;
}
bool czy_trojkat (const int& a,const int& b,const int& c)
{
    if(c>a and c>b and c<b+a)
    {
        return true;
    }
    if(b>a and b>c and b<a+c)
    {
        return true;
    }
    if(a>c and a>b and a<b+c)
    {
        return true;
    }
    return false;
}



string zad2 (const vector<int>& liczby)
{
    int maks_obw =0;
    for(int i=0;i<liczby.size()-2;i++)
    {
        for(int k=i+1;k<liczby.size()-1;k++)
        {
            for(int l=k+1;l<liczby.size();l++)
            {
                if(czy_trojkat(liczby[i],liczby[k],liczby[l]))
                {
                    int obw = liczby[i]+liczby[k]+liczby[l];
                    if(obw>maks_obw)
                    {
                        maks_obw=obw;
                    }
                }
            }
        }
    }
    return "zad2:\n" +to_string(maks_obw);
}
string zad3 (const vector<int>& liczby)
{
    int licznik=0;
    for(int i=0;i<liczby.size()-2;i++)
    {
        for(int k=i+1;k<liczby.size()-1;k++)
        {
            for(int l=k+1;l<liczby.size();l++)
            {
                if(czy_trojkat(liczby[i],liczby[k],liczby[l]))
                {
                    licznik++;
                }
            }
        }
    }
    return "zad3:\n" + to_string(licznik);
}

int main ()
{
    vector<string> odp;
    vector<int> dane = wczytaj("dane_trojkaty.txt");
    vector<string> zad1_dane = zad1(dane);
    odp.insert(odp.end(),zad1_dane.begin(),zad1_dane.end());
    odp.push_back(zad2(dane));
    odp.push_back(zad3(dane));
    zapisz("trojkaty_wymiki.txt",odp);

}
