#include"Input.h"
#include<string>
#include<iostream>
using namespace std;
string Input::mask()
{
    string name;
    cout << "������� ����� ��� ������: ";
    cin >> name;
    return name;
}
string Input::name(string param)
{
    string name;
    cout << "������� ��� " << param << ": ";
    cin >> name;
    return name;
}

string Input::path()
{
    string p;
    cout << "������� ���� ��� ��� �����/�����: ";
    cin >> p;
    return p;
}

string Input::path(string s)
{
    string p;
    cout << "������� ���� " << s << ": ";
    cin >> p;
    return p;
}