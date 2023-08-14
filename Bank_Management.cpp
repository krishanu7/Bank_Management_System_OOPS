#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Account
{
private:
    string name, userName, pin;
    int age;
    long contactNumber;
    int accountNumber;
    int balance;
    int lastTransaction;

public:
    Account(string n, int a, long c, string u, string p, int accNum)
    {
        name = n;
        age = a;
        contactNumber = c;
        userName = u;
        pin = p;
        accountNumber = accNum;
        balance = 0;
        lastTransaction = 0;
    }

    string getName()
    {
        return name;
    }

    int getAge()
    {
        return age;
    }

    long getContactNumber()
    {
        return contactNumber;
    }

    string getUserName()
    {
        return userName;
    }

    string getPin()
    {
        return pin;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    int getBalance()
    {
        return balance;
    }

    int getLastTransaction()
    {
        return lastTransaction;
    }

    void deposit(int amount)
    {
        if (amount > 0)
        {
            balance += amount;
            lastTransaction = amount;
        }
    }

    bool withdraw(int amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            lastTransaction = -amount;
            return true;
        }
        return false;
    }

    bool transfer(Account &toAccount, int amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            lastTransaction = -amount;
            toAccount.deposit(amount);
            toAccount.setLastTransaction(amount);
            return true;
        }
        return false;
    }

    void setLastTransaction(int amount)
    {
        lastTransaction = amount;
    }
};

class Bank
{
private:
    vector<Account> accounts;
    int accountCounter;

public:
    Bank()
    {
        srand(static_cast<unsigned int>(time(0)));
        accountCounter = 1;
    }

    bool newAccount(string name, int age, long contactNumber, string userName, string pin)
    {
        if (age >= 18 && contactNumber >= 1000000000 && contactNumber <= 9999999999 && pin.length() == 4)
        {
            Account newAcc(name, age, contactNumber, userName, pin, accountCounter);
            accounts.push_back(newAcc);
            accountCounter++;
            return true;
        }
        return false;
    }
    Account *findAccountByUsernameAndPin(const string &userName, const string &pin)
    {
        for (Account &acc : accounts)
        {
            if (acc.getUserName() == userName && acc.getPin() == pin)
            {
                return &acc;
            }
        }
        return nullptr; // Account not found
    }
    string getAccountDetails(string userName, string pin)
    {
        for (Account &acc : accounts)
        {
            if (acc.getUserName() == userName && acc.getPin() == pin)
            {
                string details = "Name             : " + acc.getName() + "\n";
                details += "Age              : " + to_string(acc.getAge()) + "\n";
                details += "Contact Number   : " + to_string(acc.getContactNumber()) + "\n";
                details += "Account Number   : " + to_string(acc.getAccountNumber()) + "\n";
                details += "Account Balance  : " + to_string(acc.getBalance()) + "\n";
                if (acc.getLastTransaction() > 0)
                {
                    details += "Last Transaction : Deposit of " + to_string(acc.getLastTransaction()) + "\n";
                }
                else if (acc.getLastTransaction() < 0)
                {
                    details += "Last Transaction : Withdrawal of " + to_string(0 - acc.getLastTransaction()) + "\n";
                }
                else
                {
                    details += "Last Transaction : No recent transactions\n";
                }
                return details;
            }
        }
        return ""; // Account not found
    }

    bool deposit(string userName, string pin, int depositAmount)
    {
        for (Account &acc : accounts)
        {
            if (acc.getUserName() == userName && acc.getPin() == pin)
            {
                acc.deposit(depositAmount);
                return true;
            }
        }
        return false; // Account not found
    }

    bool withdraw(string userName, string pin, int withdrawalAmount)
    {
        for (Account &acc : accounts)
        {
            if (acc.getUserName() == userName && acc.getPin() == pin)
            {
                return acc.withdraw(withdrawalAmount);
            }
        }
        return false; // Account not found
    }

    bool transferToUser(string userName1, string pin1, string userName2, int transferAmount)
    {
        Account *acc1 = nullptr;
        Account *acc2 = nullptr;

        for (Account &acc : accounts)
        {
            if (acc.getUserName() == userName1 && acc.getPin() == pin1)
            {
                acc1 = &acc;
            }
            else if (acc.getUserName() == userName2)
            {
                acc2 = &acc;
            }
        }

        if (acc1 && acc2)
        {
            return acc1->transfer(*acc2, transferAmount);
        }

        return false; // One or both accounts not found
    }
};

int main()
{
    string name, userName, pin, userName2;
    int age, amount;
    long contactNumber;
    bool isValidUser = false;

    Bank BANK;

    cout << "========== BANK OF PROGRAMMERS ==========\n"
         << endl;

    while (true)
    {
        cout << "BOT : How can I assist you?" << endl;
        cout << "\t1. Create new account" << endl;
        cout << "\t2. View details of existing account" << endl;
        cout << "\t3. Deposit money" << endl;
        cout << "\t4. Withdraw money" << endl;
        cout << "\t5. Transfer money to another user\n      [Enter the numerical value of the corresponding action you want to perform]\n"
             << endl;
        cout << "USER : ";
        Account *userAccount;
        int userInput;
        cin >> userInput;

        while (userInput < 1 || userInput > 5)
        {
            cout << "\nBOT : Invalid input. Try again\n"
                 << endl;
            cout << "USER : ";
            cin >> userInput;
        }

        switch (userInput)
        {
        case 1:
            cout << "---------- CREATING NEW ACCOUNT ----------\n"
                 << endl;
            cout << "BOT : Enter your full name\n"
                 << endl;
            cout << "USER : ";
            cin.ignore();
            getline(cin, name);
            cout << "\nBOT : Enter your age\n"
                 << endl;
            cout << "USER : ";
            cin >> age;

            if (age < 18)
            {
                cout << "\nBOT : Sorry, your age should be greater than or equal to 18 in order to create an account\n"
                     << endl;
                cout << "--------------------" << endl;
                break;
            }

            cout << "\nBOT : Enter your contact number(it should be of 10 digits)\n"
                 << endl;
            cout << "USER : ";
            cin >> contactNumber;
            cout << "\nBOT : Enter a valid username\n"
                 << endl;
            cout << "USER : ";
            cin >> userName;
            cout << "\nBOT : Enter a valid 4-digit PIN\n"
                 << endl;
            cout << "USER : ";
            cin >> pin;

            cout << "--------------------" << endl;

            if (BANK.newAccount(name, age, contactNumber, userName, pin))
            {
                cout << "\nBOT : ACCOUNT SUCCESSFULLY CREATED\n"
                     << endl;
            }

            else
            {
                cout << "\nBOT : ERROR_AccountNotCreated\n"
                     << endl;
            }

            cout << "--------------------" << endl;

            break;

        case 2:
            cout << "---------- VIEWING THE DETAILS OF AN EXISTING ACCOUNT ----------\n"
                 << endl;
            cout << "BOT : Enter your username\n"
                 << endl;
            cout << "USER : ";
            cin >> userName;
            cout << "\nBOT : Enter your PIN\n"
                 << endl;
            cout << "USER : ";
            cin >> pin;

            if (BANK.getAccountDetails(userName, pin) == "")
            {
                cout << "\nBOT : ERROR_AccountNotFound(There is no user with username - " << userName << endl;
            }

            else
            {
                cout << "\nBOT : Details - " << endl;
                cout << BANK.getAccountDetails(userName, pin) << endl;
            }

            break;

        case 3:
            cout << "---------- DEPOSITING MONEY ----------\n"
                 << endl;
            cout << "BOT : Enter your username\n"
                 << endl;
            cout << "USER : ";
            cin >> userName;
            cout << "\nBOT : Enter your PIN\n"
                 << endl;
            cout << "USER : ";
            cin >> pin;

            userAccount = BANK.findAccountByUsernameAndPin(userName, pin);

            if (userAccount)
            {
                cout << "\nBOT : Enter the amount you want to deposit\n"
                     << endl;
                cout << "USER : ";
                cin >> amount;

                if (BANK.deposit(userName, pin, amount))
                {
                    cout << "\nBOT : " << to_string(amount) << " SUCCESSFULLY DEPOSITED\n"
                         << endl;
                }
                else
                {
                    cout << "\nBOT : ERROR_AmountNotDeposited\n"
                         << endl;
                }
            }
            else
            {
                cout << "\nBOT : ERROR_WrongUsernameOrPassword\n"
                     << endl;
            }

            break;

        case 4:
            cout << "---------- WITHDRAWING MONEY ----------\n"
                 << endl;
            cout << "BOT : Enter your username\n"
                 << endl;
            cout << "USER : ";
            cin >> userName;
            cout << "\nBOT : Enter your PIN\n"
                 << endl;
            cout << "USER : ";
            cin >> pin;

            userAccount = BANK.findAccountByUsernameAndPin(userName, pin);

            if (userAccount)
            {
                cout << "\nBOT : Enter the amount you want to withdraw\n"
                     << endl;
                cout << "USER : ";
                cin >> amount;

                if (BANK.withdraw(userName, pin, amount))
                {
                    cout << "\nBOT : " << to_string(amount) << " SUCCESSFULLY WITHDRAWN\n"
                         << endl;
                }
                else
                {
                    cout << "\nBOT : ERROR_AmountNotWithdrawn(Make sure your account has sufficient balance)\n"
                         << endl;
                }
            }
            else
            {
                cout << "\nBOT : ERROR_WrongUsernameOrPassword\n"
                     << endl;
            }

            break;

        case 5:
            cout << "---------- TRANSFERRING MONEY ----------\n"
                 << endl;
            cout << "BOT : Enter your username\n"
                 << endl;
            cout << "USER : ";
            cin >> userName;
            cout << "\nBOT : Enter your PIN\n"
                 << endl;
            cout << "USER : ";
            cin >> pin;
            cout << "\nBOT : Enter the username of the user you want to transfer the money to\n"
                 << endl;
            cout << "USER : ";
            cin >> userName2;
            cout << "\nBOT : Enter the amount you want to transfer\n"
                 << endl;
            cout << "USER : ";
            cin >> amount;

            if (BANK.transferToUser(userName, pin, userName2, amount))
            {
                cout << "\nBOT : " << to_string(amount) << " SUCCESSFULLY TRANSFERRED\n"
                     << endl;
            }

            else
            {
                cout << "\nBOT : ERROR_AmountNotTransferred(Make sure your account has sufficient balance)\n"
                     << endl;
            }

            break;
        }

        cout << "--------------------\n"
             << endl;
        cout << "BOT : Is there anything else which I can help you with?(y/n)\n"
             << endl;
        char userIn;
        cout << "USER : ";
        cin >> userIn;

        while (userIn != 'y' && userIn != 'n')
        {
            cout << "USER : ";
            cin >> userIn;
        }

        if (userIn == 'n')
        {
            break;
        }
    }

    cout << "\n--------------------" << endl;
    cout << "BOT : Thank you for using our bank" << endl;
    cout << "--------------------" << endl;

    return 0;
}
