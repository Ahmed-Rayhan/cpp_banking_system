# Banking System Application in C++ 
Author: AHMED RAYHAN

This C++ program is a simple console-based banking system that allows users to perform various operations such as opening an account, making deposits, withdrawals, checking account balances, and more.

## Table of Contents
- [Overview](#overview)
- [Classes and Data Members](#classes-and-data-members)
  - [Account Class](#account-class)
  - [Bank Class](#bank-class)
  - [Exceptions](#exceptions)
- [Member Functions](#member-functions)
  - [Account Class Member Functions](#account-class-member-functions)
  - [Bank Class Member Functions](#bank-class-member-functions)
- [Overloaded Operators](#overloaded-operators)
- [Main Function](#main-function)
- [Data Persistence](#data-persistence)
- [Usage](#usage)
- [Conclusion](#conclusion)

## Overview

The program simulates a simple banking system where users can:
1. Open new bank accounts.
2. Deposit money into accounts.
3. Withdraw money from accounts.
4. Check the balance of an account.
5. Close an account.
6. View details of all accounts.

The program handles the account details and balances in memory and persists data to a file (`Bank.data`) to maintain account information between sessions.

## Classes and Data Members

### Account Class

The `Account` class represents a single bank account with the following private data members:
- `long accountNumber`: Stores the unique account number.
- `string firstName`: Stores the first name of the account holder.
- `string lastName`: Stores the last name of the account holder.
- `float balance`: Stores the balance of the account.

Additionally, there is a static data member:
- `static long NextAccountNumber`: Keeps track of the next available account number.

### Bank Class

The `Bank` class manages a collection of `Account` objects using a `map`:
- `map<long, Account> accounts`: Stores the bank's accounts, where the key is the account number.

### Exceptions

The program defines a custom exception class:
- `class InsufficientFundsException`: Thrown when a withdrawal attempt would result in a balance less than zero.

## Member Functions

### Account Class Member Functions

- **Constructor**: Initializes an account with the account holder's name and starting balance, assigning it a unique account number.
- **getAccountNumber, getFirstName, getLastName, getBalance**: Accessor functions for the account's private members.
- **deposit(float amount)**: Increases the account balance by the specified amount.
- **withdraw(float amount)**: Decreases the account balance by the specified amount, if sufficient funds are available.
- **setLastAccountNumber, getLastAccountNumber**: Static functions to manage the static account number tracker.

### Bank Class Member Functions

- **Bank()**: Constructor that loads existing accounts from a data file.
- **openAccount(string fname, string lname, float balance)**: Creates a new account and stores it in the `accounts` map.
- **balanceEnquiry(long accountNumber)**: Returns account details for a specific account number.
- **deposit(long accountNumber, float amount)**: Deposits an amount into the specified account.
- **withdraw(long accountNumber, float amount)**: Withdraws an amount from the specified account, ensuring sufficient funds.
- **closeAccount(long accountNumber)**: Removes the specified account from the `accounts` map.
- **showAllAccounts()**: Displays details of all accounts.
- **~Bank()**: Destructor that saves all account data to a file upon program termination.

## Overloaded Operators

The program overloads several operators to streamline input and output operations:
- **ofstream& operator<<(ofstream& ofs, const Account& acc)**: Writes account details to an output file stream.
- **ifstream& operator>>(ifstream& ifs, Account& acc)**: Reads account details from an input file stream.
- **ostream& operator<<(ostream& os, const Account& acc)**: Outputs account details to the console.

## Main Function

The `main` function provides a menu-driven interface that allows the user to interact with the banking system. Users can choose from several options to perform different banking operations. The program will run in a loop until the user selects the option to quit.

## Data Persistence

Account data is saved in a file (`Bank.data`) whenever changes are made (e.g., opening or closing an account). When the program starts, it loads account information from this file to maintain continuity between sessions.

## Usage

To use the banking system, follow these steps:
1. Compile and run the program.
2. Choose an option from the menu to open an account, deposit money, withdraw money, check balances, etc.
3. Follow the prompts to enter necessary information, such as account numbers and amounts.
4. The program will save any changes made to the accounts when you exit.

## Conclusion

This program demonstrates basic object-oriented programming principles in C++, such as encapsulation, data hiding, and the use of static members. It also provides a simple example of file I/O operations for data persistence and the use of exception handling to manage error conditions like insufficient funds during withdrawals.
