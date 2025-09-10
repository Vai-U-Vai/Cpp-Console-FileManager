#include"Input.h"
#include<string>
#include<iostream>
using namespace std;
string Input::mask()
{
    string name;
    cout << "¬ведите маску дл€ поиска: ";
    cin >> name;
    return name;
}
string Input::name(string param)
{
    string name;
    cout << "¬ведите им€ " << param << ": ";
    cin >> name;
    return name;
}

string Input::path()
{
    string p;
    cout << "¬ведите путь или им€ файла/папки: ";
    cin >> p;
    return p;
}

string Input::path(string s)
{
    string p;
    cout << "¬ведите путь " << s << ": ";
    cin >> p;
    return p;
}