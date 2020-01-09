#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>


using namespace std;

vector<string> wczytaj (const string& nazwa)
{
    vector<string> slowa;
    string temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> temp)
        {
            slowa.push_back(temp);
        }
        input.close();
    }
    return slowa;
}

void zapisz (const string& nazwa, const vector<string>& odpowiedz)
{
    ofstream output(nazwa);
    if(output.is_open())
    {
        for(auto s : odpowiedz)
        {
            output << s << endl;
        }
        output.close();
    }
}

string zad1 (const vector<string> slowa)
{
    int licznik=0;
    for(string s:slowa)
    {
        for(int i=1; i<s.size();i++)
        {
           // if(s[i]==s[i-1])
            {
                licznik++;
                break;
            }
        }
    }
    return  "zad1: " + to_string(licznik);
}
vector<string> zad2 (const vector<string> slowa)
{
    int wszystkie=0;
    vector<string> odp;
    std::map<char,int> litera_ilosc;
    for(string s:slowa)
    {
        for(char a:s)
        {
            litera_ilosc[a]++;
            wszystkie++;
        }
    }
    for(auto elem : litera_ilosc) //mapa std::pair<int, vector<int>>
    {
        int procent = (elem.second/wszystkie)*100;
        odp.push_back(elem.first + ": " + to_string(elem.second) + " ("
                      + to_string(procent) + "%)");
    }
    return odp;


}

int main()
{
    vector<string> dane = wczytaj("tekst.txt");
    string odp_zad1 = zad1(dane);
    vector<string> odp_zad2 = zad2(dane);
    vector<string> odp;
    odp.push_back(odp_zad1);
    odp.insert(odp.end(),odp_zad2.begin(),odp_zad2.end());

    zapisz("wyniki.txt",odp);



}
