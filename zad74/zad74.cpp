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


string zad1 (const vector<string>& hasla)
{
    int licznik=0;
    for(const auto& haslo:hasla) //const referencja
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
//bool find_my(const vector<string>& hasla  ,const string& haslo)
//{
//    for(const string& h: hasla)
//    {
//        if(h==haslo)
//        {
//            return true;
//        }
//    }
//    return false;
//}

vector<string> zad2 (const vector<string>& hasla)
{
    vector<string> odp;
    odp.push_back("zad2:");
    vector<string> doubled_passwords;
    for(int i=0;i<hasla.size();i++)
    {
        for(int k=i+1;k<hasla.size();k++)
        {
            if(hasla[i]==hasla[k])
            {
                doubled_passwords.push_back(hasla[k]);// moge uzyc std::find(vectoer.begin(), vector.end(), co szukamy)
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
bool czy_cztery_kolejne(string& ciag)
{
    sort(ciag.begin(),ciag.end());
    if(ciag[0]+1==ciag[1] and ciag[1]+1==ciag[2] and ciag[2]+1==ciag[3])
    {
        return true;
    }
    else
    {
        return false;
    }
}

string zad3 (const vector<string>& hasla)
{
    int licznik=0;
    for(const string& haslo:hasla)
    {
        if(haslo.size()>3)
        {
            for(int i=0; i<haslo.size()-3;i++)
            {
                string temp;
                temp += haslo[i];
                temp += haslo[i+1];
                temp += haslo[i+2];
                temp += haslo[i+3];

                if(czy_cztery_kolejne(temp))
                {
                    licznik++;
                    break;
                }
            }
        }

    }
    return "zad3: liczba hasel z fragmentem zlozonym z czterech znakow ASCII : " + to_string(licznik);
}
string zad4(const vector<string>& hasla)
{
    int licznik=0;
    for(const string& haslo:hasla)
    {
        bool numer = false;
        bool mala = false;
        bool duzo = false;
        for(const char& znak: haslo)
        {
            if(znak>='0' and znak<='9')
            {
                numer = true;
            }
            else if(znak>='a' and znak<='z')
            {
                mala = true;
            }
            else if(znak>='A' and znak<='Z')
            {
                duzo = true;
            }

        }
        if(numer and mala and duzo)
        {
            licznik++;
        }
    }
    return "zad4: liczba hasel spelniajce warunki: " +to_string(licznik);
}

int main ()
{
    vector<string> odp;
    vector<string> dane = wczytaj("hasla.txt");
    string zad1_odp = zad1(dane);
    string zad3_odp = zad3(dane);
    string zad4_odp = zad4(dane);

    vector<string> zad2_odp = zad2(dane);
    odp.push_back(zad1_odp);
    odp.insert(odp.end(),zad2_odp.begin(),zad2_odp.end());
    odp.push_back(zad3_odp);
    odp.push_back(zad4_odp);
    zapisz("wyniki.txt",odp);

}
