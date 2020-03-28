#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;

vector<string> wczytaj (const string& name)
{
    vector<string> odp;
    string temp;
    ifstream input(name);
    if(input.is_open())
    {
        while(input>>temp)
        {
            odp.push_back(temp);
        }
    }
    input.close();
    return odp;
}
vector<pair<string,string>> wczytaj_probki (const string& name)
{
    vector<pair<string,string>> odp;
    string jawny;
    string zaszyfrowany;
    ifstream input(name);
    if(input.is_open())
    {
        while(input>>jawny and input>>zaszyfrowany)
        {
            odp.push_back(pair<string,string>{jawny,zaszyfrowany});
        }
    }
    input.close();
    return odp;
}

void zapisz (const string& name, const vector<string>& odp)
{
    string temp;
    ofstream output(name);//ios::app
    if(output.is_open())
    {
        for(auto s:odp)
        {
            output << s << endl;
        }
    }
    output.close();
}

string szyfruj (const string& slowo,const int& a,const int& b)
{
    string slowo_t = slowo;
    for(char& znak:slowo_t) //znak=d
    {
        int s_znak = znak - 'a';
        s_znak = s_znak*a+b;
        if(s_znak>25)
        {
            s_znak=s_znak%26;
        }
        znak=s_znak + 'a';
    }
    return slowo_t;
}

string zad1 (const vector<string>& tekst)
{
    stringstream odp;
    odp<<"zad1:"<<endl;
    for(const string& slowo:tekst)
    {
        if(*slowo.begin()==*slowo.rbegin() and *slowo.begin()=='d')
        {
            odp<<slowo<<endl;
        }
    }
    return odp.str();
}
string zad2 (const vector<string>& tekst)
{
    stringstream odp;
    odp<<"zad2:"<<endl;
    for(const string& slowo:tekst)
    {
        if(slowo.size()>=10)
        {
            string zaszyfrowany = szyfruj(slowo,5,2);
            odp<<zaszyfrowany<<endl;
        }
    }
    return odp.str();
}

string zad3 (const vector<pair<string,string>>& probka)
{
    stringstream odp;
    odp<<"zad3:"<<endl;
    for(const pair<string,string>& para:probka)
    {
        for(int a=0;a<26;a++)
        {
            for(int b=0;b<26;b++)
            {
                if(szyfruj(para.first,a,b)==para.second)
                    odp<<"kod szyfrujacy dla "<<para.first<<" "<<para.second<<" : ("<<a<<","<<b<<")"<<endl;
                if(szyfruj(para.second,a,b)==para.first)
                    odp<<"kod deszyfrujacy dla "<<para.first<<" "<<para.second<<" : ("<<a<<","<<b<<")"<<endl;
            }
        }
    }
    return odp.str();

}

int main ()
{
    vector<pair<string,string>> probka = wczytaj_probki("probka.txt");
    vector<string> tekst = wczytaj("tekst.txt");
    vector<string> odp{zad1(tekst),zad2(tekst),zad3(probka)};
    zapisz("wyniki.txt",odp);
}
