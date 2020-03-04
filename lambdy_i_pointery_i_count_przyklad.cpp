#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cmath>

bool wieksze_niz_10(const int& liczba)
{
    return liczba > 10 ? true : false;
}

using namespace std;
int main()
{
    vector<int> liczby{1,22,14,2,5,6,123,67,84,52,21,23,78,94, 1};
    int licznik = 0;
    for(const auto& liczba : liczby)
    {
        if(liczba > 10)
            licznik++;
    }
    cout << "Licznik klasycznie : " << licznik << endl;
    
    auto wynik = count_if(liczby.begin(), liczby.end(), wieksze_niz_10);
    cout << "count_if z funkcja : " << wynik << endl;
    
    cout << "zwykly count : " << count(liczby.begin(), liczby.end(), 1) << endl;
        
    auto wynik2 = count_if(liczby.begin(), liczby.end(), [](const auto& liczba){ return liczba > 10 ? true : false; } ); // auto w lambdzie od wersji c++ 14, są to "generic lambda's", dla c++  11 trzeba podac dokladny typ
    cout << "count_if z lambda : " << wynik2 << endl;
            
    bool (*porownywator_pointer)(const int&) = &wieksze_niz_10; // rowniez mozna prezypisac  [](const auto& liczba){ return liczba > 10 ? true : false; };
    std::function<bool(const int&)> porownywator_lambda = [](const auto& liczba){ return liczba > 10 ? true : false; }; // ale tez mozna wpisac do szablonu funkcji z std
    
    cout << "wskaznik na funkcje : " << boolalpha << porownywator_pointer(15) << endl;
    cout << "szablon funkcji : " << boolalpha << porownywator_pointer(5) << endl;
    
    cout << "z pointerem na funkcjie : " << count_if(liczby.begin(), liczby.end(), porownywator_pointer) << endl;
    cout << "z szablonem funkcji : " << count_if(liczby.begin(), liczby.end(), porownywator_lambda) << endl;
}
