#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>

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
            for(int i=0;i<4;i++)
            {
                input>>temp;
                wspol[k].push_back(temp);
            }
        }
    }
    input.close();
    return wspol;
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

double fun_help (double x, vector<vector<double>> wspolczynniki)
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

int main ()
{

    vector<vector<double>> wspolczynniki = wczytaj("funkcja.txt");
    double haha = fun_help(1.5,wspolczynniki);
    cout << haha;
    //zapisz("wyniki.txt",odp);

}
