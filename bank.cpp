#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

class Account
{
    int accNo;
    char name[50];
    float balance;

public:

    void createAccount();
    void showAccount();
    void deposit(float);
    void withdraw(float);

    int getAccNo();
    float getBalance();
};
void Account::createAccount()
{
    cout << "Enter Account Number: ";
    cin >> accNo;

    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(name,50);

    cout << "Enter Initial Balance: ";
    cin >> balance;
}
void Account::showAccount()
{
    cout << "\nAccount Number: " << accNo;
    cout << "\nName: " << name;
    cout << "\nBalance: " << balance;

    cout << "\n-----------------------\n";
}
void Account::deposit(float amount)
{
    balance += amount;
}
void Account::withdraw(float amount)
{
    if(amount <= balance)
    {
        balance -= amount;
        cout << "Withdrawal Successful!\n";
    }
    else
    {
        cout << "Insufficient Balance!\n";
    }
}
int Account::getAccNo()
{
    return accNo;
}

float Account::getBalance()
{
    return balance;
}
void createNewAccount()
{
    Account a;

    ofstream file("bank.dat", ios::binary | ios::app);

    a.createAccount();

    file.write((char*)&a, sizeof(a));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}
void displayAccounts()
{
    Account a;

    ifstream file("bank.dat", ios::binary);

    while(file.read((char*)&a, sizeof(a)))
    {
        a.showAccount();
    }

    file.close();
}
void depositMoney()
{
    Account a;

    int acc;
    float amount;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Account Number: ";
    cin >> acc;

    bool found = false;

    while(file.read((char*)&a, sizeof(a)))
    {
        if(a.getAccNo() == acc)
        {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            a.deposit(amount);

            int pos = -1 * sizeof(a);

            file.seekp(pos, ios::cur);

            file.write((char*)&a, sizeof(a));

            cout << "Deposit Successful!\n";

            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "Account Not Found!\n";
}

void withdrawMoney()
{
    Account a;

    int acc;
    float amount;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Account Number: ";
    cin >> acc;

    bool found = false;

    while(file.read((char*)&a, sizeof(a)))
    {
        if(a.getAccNo() == acc)
        {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            a.withdraw(amount);

            file.seekp(-sizeof(a), ios::cur);

            file.write((char*)&a, sizeof(a));

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "Account Not Found!\n";
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n===== BANK MENU =====\n";

        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                createNewAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                depositMoney();
                break;

            case 4:
                withdrawMoney();
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    }while(choice != 5);

    return 0;
}