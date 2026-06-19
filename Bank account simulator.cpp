#include <iostream>
#include <string>
#include <chrono>
#include <thread> // Used in main to simulate time passing

using namespace std;

// Base Class: Account
class Account {
protected:
    string accountHolder;
    double balance;
    chrono::time_point<chrono::system_clock> lastUpdated;

public:
    Account(string name, double initialBalance) {
        accountHolder = name;
        balance = initialBalance;
        lastUpdated = chrono::system_clock::now(); // Timestamp at creation
    }

    virtual ~Account() {} // Virtual destructor for safe polymorphism

    // Encapsulation: Getter for balance
    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            updateAccount(); // Apply any pending interest/fees before modifying balance
            balance += amount;
            cout << "Deposited $" << amount << ". New Balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    virtual void withdraw(double amount) {
        updateAccount();
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << ". New Balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds or invalid amount." << endl;
        }
    }

    // Pure virtual/Virtual method to handle time-based changes
    virtual void updateAccount() = 0; 

    void display() {
        updateAccount();
        cout << "Account Holder: " << accountHolder << " | Balance: $" << balance << endl;
    }
};

// Derived Class: Savings Account (Earns Interest over time)
class SavingsAccount : public Account {
private:
    double interestRate; // Annual rate (e.g., 0.05 for 5%)

public:
    SavingsAccount(string name, double initialBalance, double rate) 
        : Account(name, initialBalance), interestRate(rate) {}

    // Upgraded feature: Calculates interest based on seconds elapsed (simulating daily/yearly scaling)
    void updateAccount() override {
        auto now = chrono::system_clock::now();
        // Calculate elapsed time in seconds
        chrono::duration<double> elapsedSeconds = now - lastUpdated;
        
        if (elapsedSeconds.count() > 0) {
            // For simulation purposes, we treat 1 second as 1 "day" of interest
            // Formula: Balance * Rate * (Days / 365)
            double interestEarned = balance * interestRate * (elapsedSeconds.count() / 365.0);
            
            if (interestEarned > 0) {
                balance += interestEarned;
                cout << "\n[Interest Alert] Earned $" << interestEarned << " over " << elapsedSeconds.count() << " seconds." << endl;
            }
        }
        lastUpdated = now; // Reset login/update time
    }
};

// Derived Class: Checking Account (Has a transaction limit fee)
class CheckingAccount : public Account {
private:
    const double TRANSACTION_FEE = 1.50;

public:
    CheckingAccount(string name, double initialBalance) 
        : Account(name, initialBalance) {}

    void updateAccount() override {
        // Checking account doesn't accumulate interest over time, 
        // but still updates the timestamp.
        lastUpdated = chrono::system_clock::now();
    }

    // Polymorphism: Overriding withdraw to include a transaction fee
    void withdraw(double amount) override {
        updateAccount();
        double totalDeduction = amount + TRANSACTION_FEE;
        
        if (amount > 0 && totalDeduction <= balance) {
            balance -= totalDeduction;
            cout << "Withdrew $" << amount << " (+$" << TRANSACTION_FEE << " fee). New Balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds to cover withdrawal and fee." << endl;
        }
    }
};

// Main function to demonstrate Polymorphism and Chrono tracking
int main() {
    cout << "=== Creating Accounts ===" << endl;
    // Using base class pointers to achieve Polymorphism
    Account* mySavings = new SavingsAccount("Zafir", 1000.0, 0.05); // 5% interest rate
    Account* myChecking = new CheckingAccount("Zafir", 500.0);

    mySavings->display();
    myChecking->display();

    // Simulate time passage (e.g., waiting 5 seconds)
    cout << "\n--- Simulating real-time gap (Waiting 5 seconds...) ---" << endl;
    this_thread::sleep_for(chrono::seconds(5));

    cout << "\n=== Interacting with Savings Account ===" << endl;
    // The updateAccount() triggers inside deposit, calculating interest for the 5-second gap
    mySavings->deposit(200.0); 

    cout << "\n=== Interacting with Checking Account ===" << endl;
    myChecking->withdraw(50.0);

    // Clean up memory
    delete mySavings;
    delete myChecking;

    return 0;
}