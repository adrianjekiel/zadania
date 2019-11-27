
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<string> wczytaj (const string& nazwa)
{
    vector<string> Ciagi;
    string temp_ciag;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> temp_ciag)
        {
            Ciagi.push_back(temp_ciag);
        }
        input.close();
    }
    return Ciagi;
}

void zapisz (const string& nazwa, const vector<string>& string_vec)
{
    ofstream output(nazwa);
    if(output.is_open())
    {
        for(auto s : string_vec)
        {
            output << s <<endl;
        }
        output.close();
    }

}
string zad1(const vector<string> ciagi)
{
    int licznik=0;
    for(auto s :ciagi)
    {
        string s1,s2;
        s1.insert(s1.begin(),s.begin(), s.end()-(s.size()/2));
        s2.insert(s2.begin(),s.end()-(s.size()/2), s.end());
        if(s1==s2)
            licznik++;
    }
    return "zad1: " + to_string(licznik);
}

int main()
{
    vector<string> dane = wczytaj("ciagi.txt");
    string odp1 = zad1(dane);
    vector<string> wyniki;
    wyniki.push_back(odp1);
    zapisz("wyniki_liczby.txt",wyniki);
}
