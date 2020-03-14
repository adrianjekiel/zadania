#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

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
            int id_bb = genotyp.find("BB", i);
            if(genotyp.find("BB", i)!= std::string::npos)
            {
                int begin = i-1;
                int end = (id_bb +1 -(i-1)+1);
                string gen = genotyp.substr(begin,end);
                geny.push_back(gen);
                i=id_bb+1;
            }
        }
    }
    return geny;
}


bool czy_mutacja(const string& gen)
{
    if(gen.find("BCDDC")!=std::string::npos)
    {
        return true;
    }
    else
    {
     return false;
    }

}


vector<string> zad2 (const vector<string>& genotypy)
{
    vector<string> odp;
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
    odp.push_back("zad2: ilosc osobnikow z dana mutacja: "+ to_string(licznik));
    return odp;
}

vector<string> zad3 (const vector<string>& genotypy)
{
    vector<string> odp;
    int maks_licznik=0;
    int maks_gen=0;
    for(auto const& genotyp: genotypy)
    {
        int licznik=0;
        vector<string> geny = znajdz_geny(genotyp);
        for(auto const& gen:geny)
        {
            licznik++;
            if(maks_gen<gen.size())
            {
                maks_gen=gen.size();
            }
        }

        if(maks_licznik<licznik)
        {
            maks_licznik=licznik;
        }
    }

    odp.push_back("zad3: ");
    odp.push_back("najwieksza ilosc genow jednego osobnika:" + to_string(maks_licznik));
    odp.push_back("najwieksza dlugosc genu zapisanego w calym pliku" + to_string(maks_gen));
    return odp;
}
bool czy_palindrom (const string& genotyp)
{
    int dl=genotyp.size();
    for(int i=0;i<dl/2;i++)
    {
        if(genotyp[i]!=genotyp[dl-i-1])
        {
            return false;
        }
    }
    return true;
}
bool czy_odporny (const string& genotyp)
{
    vector<string> geny_LP = znajdz_geny(genotyp);
    string giga_s;
    for(auto gen:geny_LP)
    {
        giga_s+=gen;
    }
    string genotyp_r{genotyp.rbegin(),genotyp.rend()};//pamietac
    vector<string> geny_PL = znajdz_geny(genotyp_r);
    string giga_s2;
    for(auto gen:geny_PL)
    {
        giga_s2+=gen;
    }
    if(giga_s==giga_s2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> zad4 (const vector<string>& genotypy)
{
    int odporne=0;
    int s_odporne=0;
    vector<string> odp;
    for(auto const& genotyp: genotypy)
    {
        if(czy_palindrom(genotyp))
        {
            s_odporne++;
        }
        if(czy_odporny(genotyp))
        {
            odporne++;
        }
    }
    odp.push_back("zad4:");
    odp.push_back("Liczba genotypow odpornych: "+to_string(odporne));
    odp.push_back("Liczba genotypow silnie odpornych: "+to_string(s_odporne));
    return odp;
}


int main ()
{
    vector<string> dane = wczytaj("geny.txt");
    vector<string> odp;
    vector<string> z2 = zad2(dane);
    vector<string> z1 = zad1(dane);
    vector<string> z3 = zad3(dane);
    vector<string> z4 = zad4(dane);
    odp.insert(odp.end(),z1.begin(),z1.end());
    odp.insert(odp.end(),z2.begin(),z2.end());
    odp.insert(odp.end(),z3.begin(),z3.end());
    odp.insert(odp.end(),z4.begin(),z4.end());
    zapisz("wyniki.txt",odp);

}
