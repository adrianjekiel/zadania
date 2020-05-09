#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Wiersz
{
    string l;
    string p;
};

vector<Wiersz> wczytaj(const string& nazwa)
{
    vector<Wiersz> temp_vec;
    ifstream input(nazwa);
    if(input.is_open())
    {
        Wiersz temp;
        while(input >> temp.l >> temp.p)
        {
            temp_vec.push_back(temp);
        }
    }
    input.close();
    return temp_vec;
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

string zad1 (const vector<Wiersz>& wiersze)
{
    stringstream odp;
    odp << "zad1: \n";
    int licznik=0;
    Wiersz pierwszy;
    for(const Wiersz& wiersz : wiersze)
    {
        if(wiersz.l.size()>=3*wiersz.p.size() or wiersz.p.size()>=3*wiersz.l.size())
        {
            licznik++;
            if(licznik==1)
            {
                pierwszy = wiersz;
            }
        }
    }
    odp<<pierwszy.l<<" "<<pierwszy.p<<"\nilosc wierszy: "<<licznik;
    return odp.str();
}

string reszta_znakow (const string& s_k,const string& s_d)
{
    string temp;
    for(int i=s_k.size();i<s_d.size();i++)
    {
        temp.push_back(s_d[i]);
    }
    return temp;
}

string zad2 (const vector<Wiersz>& wiersze)
{
    stringstream odp;
    odp << "zad2: \n";
    for(const Wiersz& wiersz : wiersze)
    {
        if(wiersz.l<wiersz.p)
        {//lewy krotszy
            if(wiersz.p.find(wiersz.l)==0)//zero symbolizuje pocz¹tek stringa prawego , inaczej npos
            {//lewy zaczyna sie w prawym
                odp<<wiersz.l<<" "<<wiersz.p<<" "<<reszta_znakow(wiersz.l,wiersz.p)<<"\n";
            }
        }
        else
        {//prawy krotszy lub rowny
            if(wiersz.l.find(wiersz.p)==0)//zero symbolizuje pocz¹tek stringa prawego , inaczej npos
            {//lewy zaczyna sie w prawym
                odp<<wiersz.l<<" "<<wiersz.p<<" "<<reszta_znakow(wiersz.p,wiersz.l)<<"\n";
            }
        }
    }
    return odp.str();
}
string zad3 (const vector<Wiersz>& wiersze)
{
    stringstream odp;
    odp << "zad3: \n";
    int maks_dl=0;
    vector<Wiersz> vec_maks_dl;
    for(const Wiersz& wiersz : wiersze)
    {
        cout<<"dupa1";
        string l {wiersz.l.rbegin(),wiersz.l.rend()};
        string p {wiersz.p.rbegin(),wiersz.p.rend()};
        cout<<"dupa2";
        int size = l.size() > p.size() ? p.size() : l.size();
        int t_dl=0;
        for(int i=0;i<size;i++)
        {
            if(l[i]==p[i])
            {
                t_dl++;
            }
            else
            {
                break;
            }
        }
        if(maks_dl<t_dl)
        {
            maks_dl=t_dl;
            vec_maks_dl.clear();
            vec_maks_dl.push_back(wiersz);
        }
        else if(maks_dl==t_dl)
        {
            vec_maks_dl.push_back(wiersz);
        }
    }
    odp << maks_dl<<"\n";
    for(const Wiersz& wiersz:vec_maks_dl)
    {
        odp<<wiersz.l<<" "<<wiersz.p<<endl;
    }
    return odp.str();
}

main()
{
    vector<Wiersz> wiersze = wczytaj("napisy.txt");
    zapisz("wyniki.txt",{zad1(wiersze),zad2(wiersze),zad3(wiersze)});
}
