#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

vector<string> wczytaj(const string& nazwa)
{
    vector<string> hasla;
    string slowo;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> slowo)
        {
            hasla.push_back(slowo);
        }
    }
    input.close();
    return hasla;
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


string zad1 (const vector<string> hasla)
{
    int licznik=0;
    for(auto haslo:hasla)
    {
        bool same_cyfry = true;
        for(char znak:haslo)
        {
            if(znak<'0' or znak>'9')
            {
                same_cyfry = false;
            }
        }
        if(same_cyfry)
        {
            licznik++;
        }
    }
    return "zad1: \n Ilosc hasel zlozonych z samych cyfr : " + to_string(licznik);
}
vector<string> zad2 (const vector<string>& hasla)
{
    vector<string> odp;
    odp.push_back("zad2:");
    vector<string> doubled_passwords;
    for(int i=0;i<200;i++)
    {
        for(int k=i+1;k<200;k++)
        {
            if(hasla[i]==hasla[k])
            {
                doubled_passwords.push_back(hasla[k]);
                break;
            }
        }
    }//mamy wsztskie powtorzone sa kopie
    sort(doubled_passwords.begin(),doubled_passwords.end());
    doubled_passwords.erase(unique(doubled_passwords.begin(),doubled_passwords.end()),doubled_passwords.end());
    for(auto hasla: doubled_passwords)
    {
        odp.push_back(hasla);
    }
    return odp;

}



int main ()
{
    vector<string> odp;
    vector<string> dane = wczytaj("hasla.txt");
    string zad1_odp = zad1(dane);
    vector<string> zad2_odp = zad2(dane);
    odp.push_back(zad1_odp);
    odp.insert(odp.end(),zad2_odp.begin(),zad2_odp.end());
    zapisz("wyniki.txt",odp);

}
