#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
using namespace std;

#define MIN_BALANCE 500

class InsufficientFundsException {};

class Account {
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;

public:
    Account() {}
    Account(string fname, string lname, float balance);
    
    long getAccountNumber() const { return accountNumber; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    float getBalance() const { return balance; }
    
    void deposit(float amount);
    void withdraw(float amount);
    
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();
    
    friend ofstream& operator<<(ofstream& ofs, const Account& acc); 
    friend ifstream& operator>>(ifstream& ifs, Account& acc);
    friend ostream& operator<<(ostream& os, const Account& acc); 
};

long Account::NextAccountNumber = 0;

class Bank {
private:
    map<long, Account> accounts;

public:
    Bank();
    
    Account openAccount(string fname, string lname, float balance);
    Account balanceEnquiry(long accountNumber);
    Account deposit(long accountNumber, float amount);
    Account withdraw(long accountNumber, float amount);
    void closeAccount(long accountNumber);
    void showAllAccounts();
    
    ~Bank();
};

int main() {
    Bank bank;
    Account account;
    int choice;
    string fname, lname;
    long accountNumber;
    float balance, amount;

    cout << "***Banking System***" << endl;
    do {
        cout << "\n\tSelect an option:";
        cout << "\n\t1. Open an Account";
        cout << "\n\t2. Balance Enquiry";
        cout << "\n\t3. Deposit";
        cout << "\n\t4. Withdrawal";
        cout << "\n\t5. Close an Account";
        cout << "\n\t6. Show All Accounts";
        cout << "\n\t7. Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter First Name: ";
                cin >> fname;
                cout << "Enter Last Name: ";
                cin >> lname;
                cout << "Enter Initial Balance: ";
                cin >> balance;
                account = bank.openAccount(fname, lname, balance);
                cout << "\nCongratulations! Account Created" << endl;
                cout << account;
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                account = bank.balanceEnquiry(accountNumber);
                cout << "\nYour Account Details" << endl;
                cout << account;
                break;
                
            case 3:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount: ";
                cin >> amount;
                account = bank.deposit(accountNumber, amount);
                cout << "\nAmount Deposited" << endl;
                cout << account;
                break;
                
            case 4:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount: ";
                cin >> amount;
                try {
                    account = bank.withdraw(accountNumber, amount);
                    cout << "\nAmount Withdrawn" << endl;
                    cout << account;
                } catch (InsufficientFundsException&) {
                    cout << "\nError: Insufficient funds for withdrawal!" << endl;
                }
                break;
                
            case 5:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                bank.closeAccount(accountNumber);
                cout << "\nAccount Closed" << endl;
                break;

            case 6:
                bank.showAllAccounts();
                break;

            case 7:
                break;

            default:
                cout << "\nInvalid choice, please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

Account::Account(string fname, string lname, float balance)
    : firstName(fname), lastName(lname), balance(balance) {
    accountNumber = ++NextAccountNumber;
}

void Account::deposit(float amount) {
    balance += amount;
}

void Account::withdraw(float amount) {
    if (balance - amount < 0)  // Ensures the balance never goes negative
        throw InsufficientFundsException();
    balance -= amount;
}

void Account::setLastAccountNumber(long accountNumber) {
    NextAccountNumber = accountNumber;
}

long Account::getLastAccountNumber() {
    return NextAccountNumber;
}

ofstream& operator<<(ofstream& ofs, const Account& acc) {
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Account& acc) {
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}

ostream& operator<<(ostream& os, const Account& acc) {
    os << "First Name: " << acc.getFirstName() << endl;
    os << "Last Name: " << acc.getLastName() << endl;
    os << "Account Number: " << acc.getAccountNumber() << endl;
    os << "Balance: " << acc.getBalance() << endl;
    return os;
}

Bank::Bank() {
    ifstream infile("Bank.data");
    if (!infile) return;

    Account account;
    while (infile >> account) {
        accounts.insert({ account.getAccountNumber(), account });
    }
    Account::setLastAccountNumber(account.getAccountNumber());
}

Account Bank::openAccount(string fname, string lname, float balance) {
    Account account(fname, lname, balance);
    accounts.insert({ account.getAccountNumber(), account });

    ofstream outfile("Bank.data", ios::trunc);
    for (const auto& pair : accounts) {
        outfile << pair.second;
    }
    return account;
}

Account Bank::balanceEnquiry(long accountNumber) {
    return accounts.at(accountNumber);
}

Account Bank::deposit(long accountNumber, float amount) {
    accounts.at(accountNumber).deposit(amount);
    return accounts.at(accountNumber);
}

Account Bank::withdraw(long accountNumber, float amount) {
    accounts.at(accountNumber).withdraw(amount);
    return accounts.at(accountNumber);
}

void Bank::closeAccount(long accountNumber) {
    cout << "Account Deleted: " << accounts.at(accountNumber);
    accounts.erase(accountNumber);
}

void Bank::showAllAccounts() {
    for (const auto& pair : accounts) {
        cout << "Account " << pair.first << endl << pair.second << endl;
    }
}

Bank::~Bank() {
    ofstream outfile("Bank.data", ios::trunc);
    for (const auto& pair : accounts) {
        outfile << pair.second;
    }
}
