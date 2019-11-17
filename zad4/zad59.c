
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Time_temp // zawsze z duzêj
{
    long long time;
    int temp;
};

void licz_binarnie (long long liczba, int podstawa_systemu, string & wynik)
{
    if(liczba<0)
    {
       wynik.push_back('-');
       liczba = abs(liczba);
    }
  if (liczba / podstawa_systemu == 0)
    {
      string temp = std::to_string (liczba % podstawa_systemu);
      wynik.insert (wynik.end (), temp.begin (), temp.end ());
    }
  else
    {
      licz_binarnie (liczba/podstawa_systemu, podstawa_systemu,wynik);
      string temp = std::to_string (liczba % podstawa_systemu);
      wynik.insert (wynik.end (), temp.begin (), temp.end ());
    }
}


vector<Time_temp> wczytaj (const string& nazwa)
{
    vector<Time_temp> czasy_temperataury;
    long long temp_time;
    int temp_temp;
    ifstream input(nazwa);
    if(input.is_open())
    {
        while(input >> temp_time and input >> temp_temp)
        {
            czasy_temperataury.push_back(Time_temp{temp_time, temp_temp});
        }
        input.close();
    }
    return czasy_temperataury;
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

int convert (long long bi,int magic_number)
{
    int dec_val = 0;
    int base = 1;
    long long temp = bi;
    while (temp) {

     long long last= temp%10;
     temp = temp/10;
     dec_val += last * base;
     base = base *magic_number;

    }
    return dec_val;
}



vector<Time_temp> converted_to_decimal (const vector<Time_temp> dane,const int magic_number)
{
    long long temp_time, temp_temp;
    vector<Time_temp> temp_vec;
    for(auto time_temp: dane)
    {
        temp_time = convert(time_temp.time,magic_number);
        temp_temp = convert(time_temp.temp,magic_number);
        temp_vec.push_back(Time_temp{temp_time,temp_temp});
    }
    return temp_vec;
}
string licz_min_temp (const vector<Time_temp> stacja)
{
    string wynik;
    int stacja_min=stacja[0].temp;
    for(auto time_temp: stacja)
    {
        if(time_temp.temp<stacja_min)
            stacja_min=time_temp.temp;
    }
    licz_binarnie (stacja_min, 2, wynik);
    return wynik;
}

vector<string> zad1 (const vector<Time_temp> stacja1,const vector<Time_temp> stacja2,const vector<Time_temp> stacja3)
{
    vector<string> odp;
    odp.push_back("zad1:");
    odp.push_back("stacja1 \n" + licz_min_temp(stacja1));

    odp.push_back("stacja2 \n" + licz_min_temp(stacja2));

    odp.push_back("stacja3 \n" + licz_min_temp(stacja3));
    return odp;
}

string zad2 (const vector<Time_temp> stacja1,const vector<Time_temp> stacja2,const vector<Time_temp> stacja3)
{
    int licznik=0;
    for(int i = 1; i<stacja1.size(); i++)
    {
        if((stacja1[i].time-stacja1[0].time)%24!=0 and (stacja2[i].time-stacja2[0].time)%24!=0 and (stacja3[i].time-stacja3[0].time)%24!=0)
        {
            licznik++;
        }
    }
    return "zad2: " + to_string(licznik);
}

string zad3 (const vector<Time_temp> stacja1,const vector<Time_temp> stacja2,const vector<Time_temp> stacja3)
{
    int licznik=1; // pierwszy pomiar zawsze rekordowy.
    int max_1 = stacja1[0].temp;
    int max_2 = stacja2[0].temp;
    int max_3 = stacja3[0].temp;
    //petla
    for(int i = 1; i<stacja1.size(); i++)
    {
        if(stacja1[i].temp > max_1 or stacja2[i].temp > max_2 or stacja3[i].temp > max_3)
        {
            licznik++;
        }
        // no ale musimy maxy zmienic
        if(stacja1[i].temp > max_1)
        {
            max_1 = stacja1[i].temp;
        }
         if(stacja2[i].temp > max_2)
        {
            max_2 = stacja2[i].temp;
        }
         if(stacja3[i].temp > max_3)
        {
            max_3 = stacja3[i].temp;
        }

    }
    return "zad3: " + to_string(licznik);

}


string zad4 (const vector<Time_temp> stacja1)
{
    int skokmax = 0;

    for( int i = 0;i<stacja1.size()-1; i++)
    {
        for(int j = i+1; j<stacja1.size(); j++)
        {
            double currentjump = ceil(double(pow(double(stacja1[i].temp) - double(stacja1[j].temp),2)/abs(i-j)));
            if(currentjump > skokmax)
               skokmax = currentjump;
        }
    }
    return "zad4 : " + to_string(skokmax);
}

int main()
{
    vector<Time_temp> stacjadane1 = wczytaj("dane_systemy1.txt");
    vector<Time_temp> stacja1 = converted_to_decimal(stacjadane1,2);
    vector<Time_temp> stacjadane2 = wczytaj("dane_systemy2.txt");
    vector<Time_temp> stacja2 = converted_to_decimal(stacjadane2,4);
    vector<Time_temp> stacjadane3 = wczytaj("dane_systemy3.txt");
    vector<Time_temp> stacja3 = converted_to_decimal(stacjadane3,8);
    vector<string> wynik_zad1 = zad1(stacja1, stacja2, stacja3);
    vector<string> wyniki; //{wynik_zad1,zad2(dane),zad3(dane)};
    wyniki.insert(wyniki.end(),wynik_zad1.begin(),wynik_zad1.end());
    wyniki.push_back(zad2(stacja1,stacja2,stacja3)); //182 or to 1018;
    wyniki.push_back(zad3(stacja1,stacja2,stacja3));
    wyniki.push_back(zad4(stacja1));
    zapisz("dupa.txt",wyniki);
}
