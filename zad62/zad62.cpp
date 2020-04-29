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

vector<int> wczytaj2(const string& nazwa)
{
    vector<int> liczby;
    int temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input>>oct>>temp)
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
string zad1(const vector<int>& liczby)
{
    stringstream odp;
    odp << "zad1: ";
    int min_l=liczby[0];
    int max_l=liczby[0];
    for(const auto& liczba:liczby)
    {
        if(liczba>max_l)
        {
            max_l=liczba;
        }
        if(liczba<min_l)
        {
            min_l=liczba;
        }
    }
    odp << "najmniejsza liczba : " << min_l << " maksymalna liczba: "<< max_l;
    return odp.str();
}

string zad2 (const vector<int>& liczby)
{
    stringstream odp;
    odp << "zad2: ";
    vector<int> temp,maks;
    for(int i=0;i<liczby.size()-1;i++)
    {
        temp.push_back(liczby[i]);
        if(liczby[i]>liczby[i+1])
        {
            if(maks.size()<temp.size())
            {
                maks=temp;
            }
            temp.clear();
        }
    }
    odp << maks[0] << " "<< maks.size();
    return odp.str();
}

int convert_to_dec (long long liczba,int podstawa_sys)
{
    int dec_val = 0;
    int base = 1;
    long long temp = liczba;
    while (temp)
    {
     long long last= temp%10;
     temp = temp/10;
     dec_val += last * base;
     base = base *podstawa_sys;
    }
    return dec_val;
}

string zad3(const vector<int>& osemkowe,const vector<int>& dziesietne)
{
    int licznik_a=0;
    int licznik_b=0;
    stringstream odp;
    odp <<"zad3: \n";
    for(int i=0;i<osemkowe.size();i++)
    {
        if(osemkowe[i]==dziesietne[i])
        {
            licznik_a++;
        }
        if(osemkowe[i]>dziesietne[i])
        {
            licznik_b++;
        }
    }
    odp <<"odp a): "<<licznik_a <<"\n odp b): " << licznik_b;
    return odp.str();
}

string zad4(const vector<int>& dziesietne)
{
    stringstream odp;
    odp << "zad4: \n";
    int licznik1 =0;
    int licznik2 =0;
    vector<string> s_dzies;
    for(auto liczba: dziesietne)
    {
        s_dzies.push_back(to_string(liczba));
    }
    for(auto wyraz:s_dzies)
    {
        for(auto znak:wyraz)
        {
            if(znak=='6')
                licznik1++; //a done
        }
    }

    vector<string> s_oct_dzies;
    for(auto liczba: dziesietne)
    {
        stringstream oct_;
        oct_ << oct <<liczba;
        s_oct_dzies.push_back(oct_.str());
    }
    for(auto wyraz:s_oct_dzies)
    {
        for(auto znak:wyraz)
        {
            if(znak=='6')
                licznik2++; //b done
        }
    }
    odp << licznik1 <<" "<< licznik2;
    return odp.str();

}
main()
{
    auto dane_osemkowe = wczytaj2("liczby1.txt");
    auto dane_dziesietne = wczytaj("liczby2.txt");
    zapisz("wyniki.txt",{zad1(dane_osemkowe),zad2(dane_dziesietne),zad3(dane_osemkowe,dane_dziesietne),zad4(dane_dziesietne)});
}
