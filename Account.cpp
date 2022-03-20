#include "Account.h"

Account::Account()
{
    name = "";
    username = "";
    password = "";
}
Account::Account(string name, string username, string password)
{
    this->name = name;
    this->username = username;
    this->password = password;
}

void Account::setValues(string name, string username, string password)
{
    this->name = name;
    this->username = username;
    this->password = password;
}


void Account::read()
{
    int i;
    cout << "Name: ";
    cin >> name;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    password = "";

    for (i = 0; i < 100; i++)
    {
        char c;
        c = _getch();

        switch (c)
        {
            case 8: //backspace
            {
                if (!password.empty())
                {
                    cout << "\b \b";
                    password.pop_back();
                }
                break;
            }
            case ' ':
            {
                break;
            }
            case 13: //enter
            {
                goto exit_loop;
                break;
            }
            default:
            {
                password.push_back(c);
                cout << "*";
            }
        }
    }
exit_loop:
    return;
}

void Account::write()
{
    cout << "\n------------------------------\n"
        << "name: " << name << "\n"
        << "username: " << username << "\n"
        << "password: " << password << "\n"
        << "------------------------------\n";
}

void Account::operator=(Account& acc)
{
    name = acc.name;
    username = acc.username;
    password = acc.password;
}

string Account::getName()
{
    return name;
}
string Account::getUsername()
{
    return username;
}
string Account::getPassword()
{
    return password;
}