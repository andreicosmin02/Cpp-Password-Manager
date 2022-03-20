#include "Account.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;


void startupMessage();
int option();
void writeAccounts(Account*, int);
int searchAccount(Account*, string, int);
void writeFile(fstream&, Account*, int);
void deleteAccount(Account*, int&, int);
int wrongOption();
string encrypt(Account*, int);
double* RSA_Algorithm();
int findCoprime(int);


int main()
{
    Account* accounts;
    Account* accountsCopy;
    int n = 1; // number of accounts
    int i = 0; //index
    int accountIndex = 0; //used in search functions
    int ok = 1;
    string search;
    string encrypt = "";

    accounts = new Account[n];

    int choice;
    startupMessage();
    fstream filetxt;
    filetxt.open("accounts", ios::in);

    string name;
    string username;
    string password;
    while (filetxt >> name)
    {
        filetxt >> username >> password;

        accounts[n - 1].setValues(name, username, password);

        n++;

        Account* accountsCopy = new Account[n];

        for (i = 0; i < n - 1; i++)
        {
            accountsCopy[i] = accounts[i];
        }
        delete[]accounts;

        accounts = accountsCopy;
     
    }

    filetxt.close();
    
readChoice:
    choice = option();

    switch (choice)
    {
    case 1:
    {
        //add an account
        cout << "Add an account:\n\n";
        accounts[n - 1].read();

        writeFile(filetxt, accounts, n);

        n++;
        Account* accountsCopy = new Account[n];
        for (i = 0; i < n - 1; i++)
        {
            accountsCopy[i] = accounts[i];
        }
        delete[]accounts;
        accounts = accountsCopy;
        break;
    }
    case 2:
    {
        //show all
        //writeAccounts(accounts, n);
        for (i = 0; i < n-1; i++)
        {
            cout << "\n\n" << i + 1;
            accounts[i].write();
        }
        break;
    }
    case 3:
    {
        //search
        do
        { 
            ok = 1;
            cout << "Enter the name you want to search for:\n"
                << "Name: ";
            cin >> search;

            accountIndex = searchAccount(accounts, search, n-1);
            if (accountIndex != -1)
            {
                accounts[accountIndex].write();
            }
            else
            {
                ok = wrongOption();
            }

        } while (ok == 0);

        break;
    }
    case 4:
    {
        //search and edit
        do
        {
            cout << "Enter the name of the account you want to EDIT:\n"
                << "Name: ";
            cin >> search;

            accountIndex = searchAccount(accounts, search, n - 1);
            if (accountIndex != -1)
            {
                cout << "\nEdit your account:\n";
                accounts[accountIndex].read();
                writeFile(filetxt, accounts, n);

            }
            else
            {
                ok = wrongOption();
            }

        } while (ok == 0);

        break;
    }   
    case 5:
    {
        //search and delete
        do
        {
            cout << "Enter the name of the account you want to DELETE:\n"
                << "Name: ";
            cin >> search;

            accountIndex = searchAccount(accounts, search, n - 1);
            if (accountIndex != -1)
            {
                cout << "\nAre you sure you want to DELETE your " << search << " account?\n"
                    << "Select your option:\n"
                    << "1 - YES\n"
                    << "2 - NO\n";
                int sure = 0;
                cin >> sure;

                if (sure == 1)
                {
                    deleteAccount(accounts, n, accountIndex);
                    writeFile(filetxt, accounts, n);
                    cout << "Your " << search << " account has been deleted\n";
                }
            }
            else
            {
                ok = wrongOption();
            }
        } while (ok == 0);
        break;
    }
    case 6:
    {
        //generate password

        break;
    }
    case 7:
    {
        //exit

        return 0;
    }
    }
    if (choice != 7)
    {
        cout << "\n\nPress enter to continue...";
        (void)_getch();
        system("cls");
        goto readChoice;
    }

    filetxt.close();

    delete[]accounts;

    return 0;
}

void startupMessage()
{
    cout << "PASSWORD MANAGER\n\n";
    cout << "Press enter to continue...";
    (void)_getch();
    system("cls");
}   

int option()
{
    string choice = "";
    int ok = 1;
    cout << "\n------------------------------\n"
        << "1 - Add\n"
        << "2 - Show all\n"
        << "3 - Search\n"
        << "4 - Search and Edit\n"
        << "5 - Search and Delete\n"
        << "6 - Generate password\n"
        << "7 - EXIT\n"
        << "------------------------------\n";

    do
    {
        cout << "Select your option:\n";
        ok = 1;
        cin >> choice;
        if (!(choice == "1" || 
            choice == "2" || 
            choice == "3" || 
            choice == "4" || 
            choice == "5" || 
            choice == "6" || 
            choice == "7"))
        {
            cout << "Your option does not exist\n";
            ok = 0;
        }
    } while (!ok);

    system("cls");
    return (choice[0] - '0');
}

void writeAccounts(Account* acc, int n)
{
    for (int i = 0; i < n; i++)
    {
        acc[i].write();
    }
}

int searchAccount(Account* accounts, string search, int size)
{
    int i = 0;

    for (i = 0; i < size; i++)
    {
        if (search == accounts[i].getName())
        {
            return i;
        }
    }

    return -1;
}

void writeFile(fstream& file, Account *accounts, int size)
{
    file.open("accounts", ios::out);
    if (file.is_open())
    {
        file << encrypt(accounts, size);
    }
    file.close();
}

void deleteAccount(Account *accounts, int &size, int index)
{
    int i;
    for (i = index; i < size-1; i++)
    {
        accounts[i] = accounts[i + 1];
    }
    size--;
}

int wrongOption()
{
    cout << "\nThis account does not exit!\n"
        << "Maybe you mistyped the name.\n"
        << "\nDo you want to type it again?\n"
        << "1 - YES\n"
        << "2 - NO\n"
        << "Select your option:\n";

    string c;
    do
    {
        cin >> c;
        if (c != "1" && c != "2")
        {
            cout << "This option does not exist!\n"
                << "\nSelect your option:\n"
                << "1 - YES\n"
                << "2 - NO\n";
        }
    } while (c != "1" && c != "2");
    if (c == "1")
    {
        system("cls");
        return 0;
    }
    else if (c == "2")
    {
        return 1;
    }
}

string encrypt(Account* accounts, int size)
{
    string enc = "";
    unsigned long long int ascii;
    int i = 0;
    for (i = 0; i < size; i++)
    {
        enc += accounts[i].getName() + "\n";
        enc += accounts[i].getUsername() + "\n";
        enc += accounts[i].getPassword() + "\n\n";
    }

    double* public_key;
    double* private_key;
    public_key = new double[2];
    private_key = new double[2];
    public_key[0] = RSA_Algorithm()[0];
    public_key[1] = RSA_Algorithm()[1];

    private_key[0] = RSA_Algorithm()[2];
    private_key[1] = RSA_Algorithm()[3];



    cout << public_key[0] << " " << public_key[1];

    for (i = 0; i < enc.length(); i++)
    {
        ascii = (unsigned long long int)pow(enc[i], public_key[0]);
        ascii = fmod(ascii, public_key[1]);
        enc[i] = (char)ascii;
    }

    cout << endl;
    cout << enc;
    cout << endl;
    
    for (i = 0; i < enc.length(); i++)
    {
        ascii = (unsigned long long int)pow(enc[i], private_key[0]);
        ascii = fmod(ascii, private_key[1]);
        enc[i] = (char)ascii;
    }
    cout << enc;
    cout << endl;

    delete[]public_key;
    delete[]private_key;
    return enc;
}

double* RSA_Algorithm()
{
    double x = 3, y = 7;
    double n = x * y;
    

    double phi = (x - 1) * (y - 1);

    double e = findCoprime(phi);

    int k = 2;
    double d = (1.0 + (k * phi)) / e;

    double* keys;
    keys = new double[4];
    keys[0] = e;
    keys[1] = n;
    keys[2] = d;
    keys[3] = n;
    return keys;
}

int findCoprime(int n)
{
    for (int i = 2; i < n; i++)
    {
        int a, b, c;
        a = i;
        b = n;

        while (b != 0)
        {
            c = a % b;
            a = b;
            b = c;
        }
        if (a == 1)
        {
            return i;
        }
    }
}