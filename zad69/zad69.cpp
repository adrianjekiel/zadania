#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <map>

using namespace std;

vector<string> wczytaj (const string& name)
{
    vector<string> genotypy;
    string temp;
    ifstream input(name);
    if(input.is_open())
    {
        while(input >> temp)
        {
            genotypy.push_back(temp);
        }
    }
    input.close();
    return genotypy;
}

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

vector<string> zad1 (const vector<string>& genotypy)
{
    map<int,int> gatunki; //dlugos , ilosc
    for(const auto& genotyp: genotypy)
    {
        gatunki[genotyp.size()]++;
    }
    int licznik=0;
    int maks_ilosc=0;
    for(const auto& gatunek:gatunki)
    {
        licznik++;
        if(maks_ilosc<gatunek.second)
        {
            maks_ilosc=gatunek.second;
        }
    }
    vector<string> odp;
    odp.push_back("Zad1:");
    odp.push_back("ilosc gatunkow: " + to_string(licznik));
    odp.push_back("najwieksza ilosc osobnikow tego samego gatunku: " + to_string(maks_ilosc));
    return odp;
}
vector<string> znajdz_geny(const string& genotyp)
{
    vector<string> geny;
    for(int i=1; i<genotyp.size();i++)
    {
        if(genotyp[i-1]=='A' and genotyp[i]=='A')
        {
            if(genotyp.find("BB", i)!= std::string::npos)
            {
               int id_bb = genotyp.find("BB", i);
               string gen = genotyp.substr(i-1,id_bb+1);
               cout << gen<< endl;
               geny.push_back(gen);
               i=id_bb+1;
            }
        }
    }
    return geny;
}


bool czy_mutacja(const string& gen)
{
    return false;
}


vector<string> zad2 (const vector<string>& genotypy)
{
    int licznik=0;
    for(auto const& genotyp: genotypy)
    {
        vector<string> geny = znajdz_geny(genotyp);
        for(auto const& gen:geny)
        {
            if(czy_mutacja(gen))
            {
                licznik++;
                break;
            }
        }
    }
    return {};
}



int main ()
{
    vector<string> dane = wczytaj("geny.txt");
    vector<string> odp;
    vector<string> z2 = zad2(dane);
    vector<string> z1 = zad1(dane);
    odp.insert(odp.end(),z1.begin(),z1.end());
    zapisz("wyniki.txt",odp);

}
