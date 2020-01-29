#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct okrag
{
double x;
double y;
double r;
};


vector<okrag> wczytaj (const string& nazwa)
{
    vector<okrag> okregi;
    okrag temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        for(int i=0;i<2000;i++)
        {
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

int main ()
{
    vector<string> odp;
    vector<okrag> dane = wczytaj("okregi.txt");
    vector<string> zad1_odp = zad1(dane);
    odp.insert(odp.end(),zad1_odp.begin(),zad1_odp.end());
    zapisz("wyniki.txt",odp);




}
