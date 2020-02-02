#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct okrag //nazwy structur duza litera
{
double x;
double y;
double r;
};


vector<okrag> wczytaj (const string& nazwa)
{
    vector<okrag> okregi;
    ifstream input(nazwa);
    if(input.is_open())
    {
        for(int i=0;i<2000;i++)
        {
            okrag temp;
            input>>temp.x;
            input>>temp.y;
            input>>temp.r;
            okregi.push_back(temp);
        }
    }
    input.close();
    return okregi;
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


vector<string> zad1 (const vector<okrag> okregi)
{
    vector<string> odp;
    int Icw=0;
    int IIcw=0;
    int IIIcw=0;
    int IVcw=0;
    int zadna=0;
    for(okrag temp:okregi)
    {
        if(temp.x>0 and temp.y >0) //Icw
        {
            if((temp.x-temp.r)>0 and (temp.y-temp.r)>0)
            {
                Icw++;
            }
            else
            {
                zadna++;
            }
        }
        if(temp.x<0 and temp.y>0)//IIcw
        {
            if(((temp.x*-1)-temp.r)>0 and (temp.y-temp.r)>0)
            {
                IIcw++;
            }
            else
            {
                zadna++;
            }
        }
        if(temp.x<0 and temp.y<0)//IIIcw
        {
            if(((temp.x*-1)-temp.r)>0 and ((temp.y*-1)-temp.r)>0)
            {
                IIIcw++;
            }
            else
            {
                zadna++;
            }
        }
        if(temp.x>0 and temp.y<0)//IVcw
        {
             if((temp.x-temp.r)>0 and ((temp.y*-1)-temp.r)>0)
            {
                IVcw++;
            }
            else
            {
                zadna++;
            }
        }
    }
    odp.push_back("zad1:");
    odp.push_back("liczba okregow I cwartki: " + to_string(Icw));
    odp.push_back("liczba okregow II cwartki: " + to_string(IIcw));
    odp.push_back("liczba okregow III cwartki: " + to_string(IIIcw));
    odp.push_back("liczba okregow IV cwartki: " + to_string(IVcw));
    odp.push_back("liczba okregow, ktore nie zawieraja sie w zadnej cwiartce: " + to_string(zadna));

    return odp;
}
bool czy_odbicie (const okrag& o1,const okrag& o2)
{
    if(o1.r==o2.r)
    {
        if(o1.x == o2.x and o1.y == -o2.y or o1.x ==-o2.x and o1.y == o2.y)
        {
            return true;
        }
    }
    return false;
}

string zad2 (const vector<okrag>& okregi)
{
    int pary=0;
    for(int i=1;i<okregi.size();i++)
    {
        for(int l=0;l<i;l++)
        {
            if(czy_odbicie(okregi[i],okregi[l]))
            {
                pary++;
            }
        }
    }
    return "zad2: liczba lustrzanych par: " + to_string(pary);
}

bool czy_prostopadle(const okrag& o1, const okrag& o2)
{
    if(o1.r==o2.r)
    {
        if(o1.x == o2.y and o1.y == -o2.x or o1.x ==-o2.y and o1.y == o2.x)
        {
            return true;
        }
    }
    return false;
}
string zad3 (const vector<okrag>& okregi)
{
    int pary_90=0;
    for(int i=1;i<okregi.size();i++)
    {
        for(int l=0;l<i;l++)
        {
            if(czy_prostopadle(okregi[i],okregi[l]))
            {
                    pary_90++;
            }
        }
    }
    return "zad3: liczba prostopadlych par: " + to_string(pary_90);
}
bool czy_przeciecie(const okrag& o1, const okrag& o2)
{
    double s1s2 = sqrt(pow((o2.x-o1.x),2)+pow(o2.y-o1.y,2));
    double ro = abs(o1.r-o2.r);
    double so = o1.r+o2.r;
    if(ro<=s1s2 and s1s2<=so)
    {
        return true;
    }
    return false;
}

vector<string> zad4 (const vector<okrag>& okregi)
{
    vector<string> odp;
    int max_dl=0;
    int dl_lancuch=1;
    for(int i=0; i<999 ;i++)
    {
        if(czy_przeciecie(okregi[i],okregi[i+1]))
        {
            dl_lancuch++;
            if(i==998)
            {
                odp.push_back("dlugosc kojenego lancucha: " + to_string(dl_lancuch));
            }
        }
        else
        {
            odp.push_back("dlugosc kojenego lancucha: " + to_string(dl_lancuch));
            dl_lancuch=1;
        }
        if(max_dl<dl_lancuch)
        {
            max_dl=dl_lancuch;
        }
    }
    odp.push_back("dlugosc najdluzszego lancucha: " + to_string(max_dl));
    return odp;

}

int main ()
{
    vector<string> odp;
    vector<okrag> dane = wczytaj("okregi.txt");
    vector<string> zad1_odp = zad1(dane);
    string zad2_odp = zad2(dane);
    string zad3_odp = zad3(dane);
    vector<string> zad4_odp = zad4(dane);
    odp.insert(odp.end(),zad1_odp.begin(),zad1_odp.end());
    odp.push_back(zad2_odp);
    odp.push_back(zad3_odp);
    odp.insert(odp.end(),zad4_odp.begin(),zad4_odp.end());
    zapisz("wyniki.txt",odp);




}
