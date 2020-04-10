#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

struct Wierzcholek
{
    int x;
    int y;
};

vector<vector<Wierzcholek>> wczytaj(const string& nazwa)
{
    vector<vector<Wierzcholek>> dane;
    int x_temp;
    int y_temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        for(int l=0;l<100;l++)
        {
            vector<Wierzcholek> punkty;
            for(int i=0;i<3;i++)
            {zad1(dane),zad2(dane),zad3(danetr),zad4(danetr)
                input >> x_temp >> y_temp;
                punkty.push_back({x_temp,y_temp});
            }
            dane.push_back(punkty);
        }
    }
    input.close();
    return dane;
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

bool czy_dodatnie (const Wierzcholek& wierzcholek)
{
    return wierzcholek.x >0 and wierzcholek.y >0;
}

string zad1(const vector<vector<Wierzcholek>>& dane)
{
    int licznik=0;
    for(const auto& wiersz : dane)
    {
        if(all_of(wiersz.begin(),wiersz.end(),czy_dodatnie)) //nakladam na kazdy element w przedziale
        {
            licznik++;
        }
    }
    return "zad1: " + to_string(licznik);
}
double dlugosc (const Wierzcholek& a, const Wierzcholek& b)
{
    return  sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
}

double dlugosc_potega (const Wierzcholek& a, const Wierzcholek& b)
{
    return  (pow((b.x-a.x),2)+pow((b.y-a.y),2));
}

string zad2 (const vector<vector<Wierzcholek>>& dane)
{
    int licznik=0;
    for(const auto& wiersz : dane)
    {
        if((wiersz[1].y-wiersz[0].y)*(wiersz[2].x -wiersz[1].x)== (wiersz[2].y-wiersz[1].y)*(wiersz[1].x -wiersz[0].x))
        licznik++;
    }
    return "zad2: " + to_string(licznik);
}

string zad3 (const vector<vector<Wierzcholek>>& dane)
{
    vector<Wierzcholek> trojkat_maks = dane[0];
    double maks_ob =0.0;
    for(const auto& wiersz : dane)
    {
        double ob = double(dlugosc(wiersz[0],wiersz[1])) + double(dlugosc(wiersz[1],wiersz[2])) + double(dlugosc(wiersz[0],wiersz[2]));
        if(ob>maks_ob)
        {
            trojkat_maks = wiersz;
            maks_ob=ob;
        }
    }
    stringstream str;
    str << setprecision(5) << maks_ob;
    str >> maks_ob;
    string odp {"A:("+ to_string(trojkat_maks[0].x) + "," +to_string(trojkat_maks[0].y) + ") B:("+ to_string(trojkat_maks[1].x) + "," +to_string(trojkat_maks[1].y) + ") C:(" + to_string(trojkat_maks[2].x) + "," + to_string(trojkat_maks[2].y) +")"};
    return "zad3: " + odp + to_string(maks_ob);

}
bool czy_prostokatny(const vector<Wierzcholek>& wiersz)
{
    double AB = dlugosc_potega(wiersz[0],wiersz[1]);
    double BC = dlugosc_potega(wiersz[1],wiersz[2]);
    double AC = dlugosc_potega(wiersz[0],wiersz[2]);
    if(AB+BC==AC or BC+AC==AB or AB+AC==BC)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string zad4 (const vector<vector<Wierzcholek>>& dane)
{
    int licznik=0;
    for(const auto& wiersz : dane)
    {
        if(czy_prostokatny(wiersz))
            licznik++;
    }
    return "zad4: " + to_string(licznik);
}


vector<string> zad5 (const vector<vector<Wierzcholek>>& dane)
{
    vector<string> odp;
    odp.push_back("zad5:");
    for(const auto& wiersz : dane)
    {
        //ze wzoru na srodek odcinka xc+xa=xb+xd -> xd=xa+xc-xd
        int x_d =wiersz[0].x+wiersz[2].x-wiersz[1].x;
        int y_d =wiersz[0].y+wiersz[2].y-wiersz[1].y;
        if(x_d==y_d)
        {
            odp.push_back("("+to_string(wiersz[0].x)+","+to_string(wiersz[0].y)+"), ("+
                          to_string(wiersz[1].x)+","+to_string(wiersz[1].y)+"), ("+
                          to_string(wiersz[2].x)+","+to_string(wiersz[2].y)+"), ("+
                          to_string(x_d)+","+to_string(y_d)+")");
        }
    }
    return odp;
}


main()
{
    auto dane = wczytaj("wspolrzedne.txt");
    auto danetr = wczytaj("wspolrzedneTR.txt");
    vector<string> odp {zad1(dane),zad2(dane),zad3(danetr),zad4(danetr)};
    vector<string> zad5odp = zad5(danetr);
    odp.insert(odp.end(),zad5odp.begin(),zad5odp.end());
    zapisz("wyniki.txt",odp);
}
