#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

vector<vector<double>> wczytaj (const string& name)
{
    vector<vector<double>> wspol;
    double temp;
    ifstream input(name);
    if(input.is_open())
    {
        for(int k=0;k<5;k++)
        {
            vector<double> temp_wiersz;
            for(int i=0;i<4;i++)
            {
                input>>temp;
                temp_wiersz.push_back(temp);
            }
            wspol.push_back(temp_wiersz);
        }
    }
    input.close();
    return wspol;
}

void zapisz (const string& name, const vector<string>& odp)
{
    string temp;
    ofstream output(name,ios::app);
    if(output.is_open())
    {
        for(auto s:odp)
        {
            output << s << endl;
        }
    }
    output.close();
}
double fun (const vector<double>& wspol ,const double& x)
{
    return wspol[0] + (wspol[1]*x) +(wspol[2]*(pow(x,2))) + (wspol[3]*(pow(x,3)));
}

double funkcja (double x, vector<vector<double>> wspolczynniki)
{
    if(x>=0.0 and x<1.0)
    {
        return fun(wspolczynniki[0],x);
    }
    if(x>=1.0 and x<2.0)
    {
        return fun(wspolczynniki[1],x);
    }
    if(x>=2.0 and x<3.0)
    {
        return fun(wspolczynniki[2],x);
    }
    if(x>=3.0 and x<4.0)
    {
        return fun(wspolczynniki[3],x);
    }
    if(x>=4.0 and x<5.0)
    {
        return fun(wspolczynniki[4],x);
    }
}

string zad2 (vector<vector<double>> wspolczynniki)
{
    stringstream odp;
    double wynik_maks=0;
    double argument=0;
    for(double x=4.0;x<5.0;x+=0.001)
    {
        double wynik= funkcja(x,wspolczynniki);
        if(wynik_maks<wynik)
        {
            argument=x;
            wynik_maks=wynik;
        }
    }
    odp << "Zad 2:" << endl;
    odp << "x= " << setprecision(4) << argument << endl;
    odp << "f(x)= " << setprecision(6) << wynik_maks << endl;
    return odp.str();
}

double bisekcja(double left,double right,const vector<vector<double>>& wspolczynniki)
{
    double midx = ((right-left)/2.0)+left;

    double fl = funkcja(left, wspolczynniki);
    double fmid = funkcja(midx, wspolczynniki);
    if(abs(fmid)<0.00001)
    {
        return ((right-left)/2.0)+left;
    }
    else
    {
        if(fl*fmid<0.0)
        {
            bisekcja(left,midx,wspolczynniki);
        }
        else
        {
            bisekcja(midx,right,wspolczynniki);
        }
    }
}

string zad3 (const vector<vector<double>>& wspolczynniki)
{
    stringstream odp;
    odp << "Zad3:" << endl;
    odp << "m[0] : " << bisekcja(0.0,1.0,wspolczynniki) << endl;
    odp << "m[1] : " << bisekcja(2.0,3.0,wspolczynniki) << endl;
    odp << "m[2] : " << bisekcja(3.0,4.0,wspolczynniki) << endl;
    odp << "m[3] : " << bisekcja(4.0,5.0,wspolczynniki) << endl;
    return odp.str();
}

string zad1(const vector<vector<double>>& wspolczynniki)
{
    stringstream odp;
    odp << "Zad1:" << endl;
    odp << "f(1.5) = " << setprecision(6) << funkcja(1.5,wspolczynniki) << endl;
    return odp.str();
}


int main ()
{
    vector<vector<double>> wspolczynniki = wczytaj("funkcja.txt");
    vector<string> odp{zad1(wspolczynniki), zad2(wspolczynniki), zad3(wspolczynniki)};
    zapisz("wyniki.txt",odp);
}
