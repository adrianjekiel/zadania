
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

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
vector<string> zad1(const vector<string> ciagi)
{
    vector<string> odp1;
    odp1.push_back("zad1:");
    for(auto s :ciagi)
    {
        if(s.size()%2==0)
        {
            string s1,s2;
            s1.insert(s1.begin(),s.begin(), s.end()-(s.size()/2));
            s2.insert(s2.begin(),s.end()-(s.size()/2), s.end());
            if(s1==s2)
                odp1.push_back(s);
        }

//        lub
//        if(s.size()%2==0)
//        {
//           int i,j;
//           bool czydwucykliczny = true;//flaga
//            for(i=0, j=s.size()/2;j<s.size();i++, j++)
//            {
//                if(s[i]!=s[j])
//                {
//                    czydwucykliczny = false;
//                    break;
//                }
//            }
//            if(czydwucykliczny)
//                odp1.push_back(s);
//        }

    }
    return odp1;
}

string zad2(const vector<string> ciagi)
{
    int licznik=0;
    for(auto s:ciagi)
    {
        bool czy11 = false;
        for(int i=1;i<s.size();i++)
        {
            if(s[i-1]=='1' and s[i]==s[i-1])
            {
                czy11 = true;
                break;
            }
        }
        if(!czy11)
            licznik++;
    }
    return "zad2: " +to_string(licznik);
}
int bin_to_dec (string ciag)
{
    int suma=0;
    int i;
    int l;
    for(i=ciag.size()-1, l=0;i>=0;i--,l++)
    {
        suma = suma + (ciag[i]-48)*pow(2,l);
    }
    return suma;
}
vector<int> convert(const vector<string> ciagi)
{
    vector<int> liczby;
    for(auto s:ciagi) //11011
    {
        liczby.push_back(bin_to_dec(s));
    }
    return liczby;
}
vector<int> czynniki (int liczba)
{
    vector<int> czn;
    int aktuany_czynnik=2;
    while(liczba!=1)
    {
        if(liczba%aktuany_czynnik==0)
        {
            czn.push_back(aktuany_czynnik);
            liczba = liczba/aktuany_czynnik;
        }
        else
        {
            aktuany_czynnik++;
        }
    }
    return czn;
}


bool czypierwsza(int liczba)
{
    if(liczba < 2)
        return false;
    else
    {
      for(int dzielnik = 2; dzielnik < liczba;dzielnik++)
      {
        if(liczba%dzielnik==0)
          return false;
      }
    return true;
    }

}

bool verify_czn (vector<int> czn)
{
    if(czn.size()!=2)
        return false;
    else
    {
        for(int liczba:czn)
        {
            if(czypierwsza(liczba))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}


//czypierwsza, czy ilosc czynników jest rowna dwa, jesli tak to czy pierwsze, push licvzb do vectora polpierweszych, licznik polpierwszch
vector<string> zad3 (const vector<int> ciagi)
{
    vector<string> odp;
    int licznik=0;
    vector<int> polpierwsze;
    for(auto ciag:ciagi)
    {
        if(verify_czn(czynniki(ciag)))
        {
            polpierwsze.push_back(ciag);
            licznik++;
        }
    }
    odp.push_back("zad3:");
    string pierwsze = "liczb polpierwszych jest " + to_string(licznik);
    odp.push_back(pierwsze);
    sort(polpierwsze.begin(),polpierwsze.end());
    string dwa = "najmiejsza liczba polpierwsza: "+ to_string(polpierwsze.front());
    string trzy = "najwieksza liczba polpierwsza: "+ to_string(polpierwsze.back());
    odp.push_back(dwa);
    odp.push_back(trzy);
    return odp;
}

int main()
{
    vector<string> dane = wczytaj("ciagi.txt");
    vector<string> odp1 = zad1(dane);
    vector<string> wyniki;
    wyniki.insert(wyniki.end(),odp1.begin(),odp1.end());
    wyniki.push_back(zad2(dane));
    vector<string> odp3 = zad3(convert(dane));
    wyniki.insert(wyniki.end(),odp3.begin(),odp3.end());
    zapisz("wyniki_liczby.txt",wyniki);
}
