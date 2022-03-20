#pragma once
#include <iostream>
#include <conio.h>
using namespace std;
class Account
{
private:
    string name;
    string username;
    string password;
public:
    Account();
    Account(string, string, string);

    void setValues(string, string, string);
    void read();
    void write();

    void operator=(Account&);

    string getName();
    string getUsername();
    string getPassword();
};
