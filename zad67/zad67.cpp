#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void zapisz (const string& name, const vector<string>& odp)
{
    string temp;
    ofstream output(name);
    if(output.is_open())
    {
        for(auto s:odp)
        {
            output << s << endl;
        }
    }
    output.close();
}

void zapisz_fraktal (const string& name, const vector<string>& odp)
{
    string temp;
    ofstream output(name);
    if(output.is_open())
    {
        for(auto s:odp)
        {
            for(auto c:s)
            {
                output << c << " ";
            }
            output << endl;

        }
    }
    output.close();
}

int fib (const int& n)
{
    if(n==1 or n==2)
        return 1;
    else
        return fib(n-1)+fib(n-2);
}

bool czy_pierwsza (const int& a)
{
    if(a>1)
    {
        for(int n=2;n<(a/2);n++)
        {
            if(a%n==0)
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> zad1 ()
{
    vector<string> odp;
    odp.push_back("zad1:");
    int jeden = fib(10);
    int dwa = fib(20);
    int trzy =fib(30);
    int cztery =fib(40);
    odp.push_back("fib(10)= "+ to_string(jeden));
    odp.push_back("fib(20)= "+ to_string(dwa));
    odp.push_back("fib(30)= "+ to_string(trzy));
    odp.push_back("fib(40)= "+ to_string(cztery));
    return odp;
}

vector<string> zad2()
{
    vector<string> odp;
    odp.push_back("zad2:");
    for(int i=1;i<=40;i++)
    {
        int tempf = fib(i);
        if(czy_pierwsza(tempf))
        {
            odp.push_back("fib(" + to_string(i) + ")= " + to_string(tempf));
        }
    }
    return odp;
}
string dec_to_bin(int liczba)
{
    string bin;
    while(liczba>0)
    {
        if(liczba%2)
        {
            bin.push_back('1');
        }
        else
        {
            bin.push_back('0');
        }
        liczba = liczba/2;
    }
    string odp{bin.rbegin(),bin.rend()};
    return odp;
}

vector<string> zad3()
{
    vector<string> odp;
    string maksf = dec_to_bin(fib(40));

    for(int i=1;i<=40;i++)
    {
        int tempf = fib(i);
        string bin_f = dec_to_bin(tempf);
        string f;
        for(int i=0;i<maksf.size()-bin_f.size();i++)
        {
            f.push_back('0');
        }
        f.insert(f.end(),bin_f.begin(),bin_f.end());
        odp.push_back(f);
    }
    return odp;
}

vector<string> zad4()
{
    vector<string> odp;
    odp.push_back("zad4: ");
    for(int i=1;i<=40;i++)
    {
        int tempf = fib(i);
        string bin_f = dec_to_bin(tempf);
        int licznik=0;
        for(const auto& c:bin_f)
        {
            if(c=='1')
            {
                licznik++;
            }
        }
        if(count(bin_f.begin(),bin_f.end(),'1')==6)
        {
            odp.push_back(bin_f);
        }
    }
    return odp;
}

int main ()
{
    vector<string> odp;
    vector<string> zadanie1 = zad1();
    vector<string> zadanie2 = zad2();
    vector<string> zadanie3 = zad3();
    vector<string> zadanie4 = zad4();

    odp.insert(odp.end(),zadanie1.begin(),zadanie1.end());
    odp.insert(odp.end(),zadanie2.begin(),zadanie2.end());
    odp.push_back("zad3:");
    odp.insert(odp.end(),zadanie3.begin(),zadanie3.end());
    odp.insert(odp.end(),zadanie4.begin(),zadanie4.end());
    zapisz_fraktal("fraktal.ods",zad3());
    zapisz("wyniki.txt",odp);

}
