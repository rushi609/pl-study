
#include <iostream>
#include <string>
#include <exception>
using namespace std;

class NegativeBalanceException : public exception {
public:
    const char* what() const noexcept override {
        return "Balance cannot be negative!";
    }
};

class InsufficientFundsException : public exception {
public:
    const char* what() const noexcept override {
        return "Insufficient funds for withdrawal!";
    }
};

class InvalidAmountException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid amount! Amount must be positive.";
    }
};

class DivideByZeroException : public exception {
public:
    const char* what() const noexcept override {
        return "Division by zero is not allowed!";
    }
};

class BankAccount {
private:
    string accountHolder;
    int accountNumber;
    double balance;

public:
    BankAccount(string holder, int number, double initialBalance) {
        accountHolder = holder;
        accountNumber = number;

        if (initialBalance < 0) {
            throw NegativeBalanceException();
        }

        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }

        balance += amount;
        cout << "Deposited: " << amount
             << ". New balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }

        if (amount > balance) {
            throw InsufficientFundsException();
        }

        balance -= amount;
        cout << "Withdrawn: " << amount
             << ". Remaining balance: " << balance << endl;
    }

    double getBalance() const {
        return balance;
    }

    void displayAccount() const {
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

double divideNumbers(double numerator, double denominator) {
    if (denominator == 0) {
        throw DivideByZeroException();
    }

    return numerator / denominator;
}

void processBankTransaction(BankAccount& account,
                            double amount, int transactionType) {
    try {
        if (transactionType == 1) {
            account.deposit(amount);
        } else if (transactionType == 2) {
            account.withdraw(amount);
        } else {
            cout << "Invalid transaction type!" << endl;
        }
    } catch (const InvalidAmountException& e) {
        cerr << "Amount Error: " << e.what() << endl;
    } catch (const InsufficientFundsException& e) {
        cerr << "Funds Error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }
}

int main() {
    cout << "=== Division by Zero ===" << endl;

    try {
        cout << "10 / 2 = " << divideNumbers(10, 2) << endl;
        cout << "10 / 0 = ";
        cout << divideNumbers(10, 0) << endl;
    } catch (const DivideByZeroException& e) {
        cerr << "Division Error: " << e.what() << endl;
    }

    cout << "\n=== Bank Account - Multiple Exceptions ===" << endl;

    try {
        BankAccount account1("John Doe", 1001, 1000);
        account1.displayAccount();
        account1.deposit(500);
        account1.withdraw(2000);
    } catch (const InsufficientFundsException& e) {
        cerr << "Transaction Error: " << e.what() << endl;
    } catch (const NegativeBalanceException& e) {
        cerr << "Account Creation Error: " << e.what() << endl;
    } catch (const InvalidAmountException& e) {
        cerr << "Amount Error: " << e.what() << endl;
    }

    cout << "\n=== Multiple Catch Blocks ===" << endl;

    try {
        BankAccount account2("Jane Smith", 1002, 500);
        account2.deposit(-100);
    } catch (const InvalidAmountException& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    cout << "\n=== Complete Transaction Processing ===" << endl;

    try {
        BankAccount account3("Alice Johnson", 1003, 2000);
        account3.displayAccount();
        processBankTransaction(account3, 500, 1);
        processBankTransaction(account3, 3000, 2);
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
    }

    return 0;
}
