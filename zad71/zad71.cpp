#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
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
    double funkcja;
    double a0 = wspol[0];
    double a1 = wspol[1];
    double a2 = wspol[2];
    double a3 = wspol[3];
    funkcja = a0 + (a1*x) +(a2*(pow(x,2))) + (a3*(pow(x,3)));
    return funkcja;
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
double zaokragli (const int& dokladnosc, const double& liczba)
{
    double wynik = liczba;
    wynik = round(wynik*pow(double(10),dokladnosc))/pow(double(10),dokladnosc);
    return wynik;
}

vector<string> zad2 (vector<vector<double>> wspolczynniki)
{
    vector<string> odp;
    double wynik_maks=0;
    double argument=0;
    for(double x=4.0;x<5.0;x+=0.001)
    {
        double wynik= zaokragli(5,funkcja(x,wspolczynniki));
        if(wynik_maks<wynik)
        {
            argument=x;
            wynik_maks=wynik;
        }
    }
    odp.push_back("zad2:");
    odp.push_back("x="+to_string(argument));
    odp.push_back("f(x)=" +to_string(wynik_maks));
    return odp;
}
double bisekcja(double left,double right,const vector<vector<double>>& wspolczynniki)
{
    double midx = ((right-left)/2.0)+left;

    double fl = funkcja(left, wspolczynniki);
    double fmid = funkcja(midx, wspolczynniki);
    double fr = funkcja(right, wspolczynniki);
    cout<<midx<<" "<<fmid<<" "<<fl<<" "<<fr<<endl;
    if(abs(fmid)<0.00001)
    {
        cout<<"zwracam"<<endl;
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

vector<string> zad3 (vector<vector<double>> wspolczynniki)
{
    double m0 = bisekcja(0.0,1.0,wspolczynniki);
    //double m1 = bisekcja(2.0,3.0,wspolczynniki);
    //double m2 = bisekcja(3.0,4.0,wspolczynniki);
    //double m3 = bisekcja(4.0,5.0,wspolczynniki);
    cout<<m0<<endl;
    //cout<<m1<<endl;
    //cout<<m2<<endl;
    //cout<<m3<<endl;
}


int main ()
{
    vector<vector<double>> wspolczynniki = wczytaj("funkcja.txt");
    vector<string> odp;
    vector<string> z2 = zad2(wspolczynniki);
    vector<string> z3 = zad3(wspolczynniki);
    odp.push_back("zad1:");
    odp.push_back("f(1.5)=" + to_string(zaokragli(5,funkcja(1.5,wspolczynniki))));
    odp.insert(odp.end(),z2.begin(),z2.end());
    zapisz("wyniki.txt",odp);

}
