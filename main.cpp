//Rene Rodriguez 09/13/25  Lab Activities: Objects and Classes I
//Challenge: Bank Account Management System
#include<iostream>
#include<vector>
#include <string>
#include<limits>
using namespace std;

double userDouble;
int userInt;
string userString;
//BankAccount class
class BankAccount {
    public:
        BankAccount(){
            accountNumber = "000000";
            accountHolderName = "Unknown";
            balance = 0.0;
        }
        BankAccount(string accNum, string holderName, double bal){
            accountNumber = accNum;
            accountHolderName = holderName;
            balance = bal;
            
        }
        string GetAccNum() const;
        string GetAccHolder() const;
        double GetBalance() const;
        void SetAccHolder(string holderName);
        void Deposit(double depositAmount);
        void Withdraw(double withdrawAmount);

    private:
        string accountNumber;
        string accountHolderName;
        double balance;
};
//Out of class definition
string BankAccount::GetAccNum() const {
    return accountNumber;
}
string BankAccount::GetAccHolder() const {
    return accountHolderName;
}
double BankAccount::GetBalance() const {
    return balance;
}
void BankAccount::SetAccHolder(string holderName){
    accountHolderName = holderName;
}
void BankAccount::Deposit(double depositAmount){
    balance += depositAmount;
}
void BankAccount::Withdraw(double withdrawAmount){
    if (withdrawAmount > balance){
        cout << "Insufficient funds." << endl;
    } else {
        balance -= withdrawAmount;
    }
}
//Prompting user
void promptUser(){
    cout << "What would you like to do?" << endl;
    cout << "\t 1. Create account" << endl;
    cout << "\t 2. List all accounts" << endl;
    cout << "\t 3. Change account holder name" << endl;
    cout << "\t 4. Deposit" << endl;
    cout << "\t 5. Withdraw" << endl;
    cout << "\t 0. Quit" << endl;
}
/*I differentiated against double input and integer input*/
double getdoubleInput(){
    double input;
    cin >> input;
    while(input < 0 || cin.fail()){
        if (cin.fail()) {
            cout << "Invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        if(input < 0){
            cout << "Enter a positive number" << endl; 
        }
        cin >> input;

    }
    cout << "You entered " << input << endl;
    return input;
}
int getIntInput(){
    int input;
    cin >> input;
    while(input < 0 || cin.fail()){
        if (cin.fail()) {
            cout << "Invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        if(input < 0){
            cout << "Enter a positive number" << endl; 
        }
        cin >> input;

    }
    cout << "You entered " << input << endl;
    return input;
}
//Creates an account and adds it to a vector of type BankAccount
void createAccount(vector<BankAccount>& bankVect){
    BankAccount currAccount;
    cout << "Enter bank account number." << endl;
    //Repeatedly prompts user if they inputted an already existing Account Number
    do {
        userInt = getIntInput();
        for (int i = 0; i < bankVect.size(); ++i){
            currAccount = bankVect.at(i);
            if (currAccount.GetAccNum() == to_string(userInt)){
                cout << "Account number already exists." << endl
                << "Enter new number." << endl;
                break;
            }
        }
    } while (currAccount.GetAccNum() == to_string(userInt));
    cout << "Enter Name" << endl;
    //Usef getline to get user name but I needed to use a cin.ignore first
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, userString);
    //Creating a new BankAccount with userInput and I put it into the vector
    BankAccount newAccount = BankAccount(to_string(userInt), userString, 0.0);
    bankVect.push_back(newAccount);
}
void listAccounts(vector<BankAccount>& bankVect){
    BankAccount currAccount;
    if (bankVect.size() == 0){
        cout << "No accounts" << endl;
    } else {
        for (int i = 0; i < bankVect.size(); ++i){
            currAccount = bankVect.at(i);
            cout << "Account Number: " << currAccount.GetAccNum() << endl
            << "Account Holder: " << currAccount.GetAccHolder() << endl
            << "Account Balance: " << currAccount.GetBalance() << endl;
        }
    }
}
void changeAccountName(vector<BankAccount>& bankVect){
    BankAccount currAcc;
    bool notFound = true;
    //Handles if there is nothing in vector
    if (bankVect.size() == 0){
        cout << "No accounts available." << endl;
    } else {
        //Prompts user repeatedly if account number can't be found
        while(notFound){
            cout << "Enter Account Number you would like to change name of." << endl;
            userInt = getIntInput();
            for (int i = 0; i < bankVect.size(); ++i){
                currAcc = bankVect.at(i);
                //Had to convert userInt to string to compare
                if(currAcc.GetAccNum() == to_string(userInt)){
                    notFound = false;
                    cout << "Enter new name" << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, userString);
                    //I used brackets so I could access the actual object within the vector and not a copy
                    bankVect[i].SetAccHolder(userString);
                    break;
                }
            }
            if(notFound){
                cout << "Account Number not found. Try Again." << endl;
            }
        }
    }
}
void depositAmount(vector<BankAccount>& bankVect){
    BankAccount currAcc;
    bool notFound = true;
    if(bankVect.size() == 0){
        cout << "No accounts available." << endl;
    } else {
        while(notFound){
            cout << "Enter Account Number you would like to deposit money." << endl;
            userInt = getIntInput();
            for (int i = 0; i < bankVect.size(); ++i){
                currAcc = bankVect.at(i);
                if(currAcc.GetAccNum() == to_string(userInt)){
                    notFound = false;
                    cout << "Enter deposit amount" << endl;
                    userDouble = getdoubleInput();
                    bankVect[i].Deposit(userDouble);
                    break;
                }
            }
            if(notFound){
            cout << "Account Number not found. Try Again." << endl;
            }
        }
    }
}
void withdrawAmount(vector<BankAccount>& bankVect){
    BankAccount currAcc;
    bool notFound = true;
    bool tooMuch = true;
    if(bankVect.size() == 0){
        cout << "No accounts available." << endl;
    } else {
        //repeatedly prompts user if the account number can't be found or if withdrawn amount is too much
        while(notFound || tooMuch){
            cout << "Enter Account Number you would like to withdraw money from." << endl;
            userInt = getIntInput();
            for (int i = 0; i < bankVect.size(); ++i){
                currAcc = bankVect.at(i);
                if(currAcc.GetAccNum() == to_string(userInt)){
                    notFound = false;
                    cout << "Enter withdrawal amount" << endl;
                    userDouble = getdoubleInput();
                    //Checks if there is sufficient funds
                    if (bankVect[i].GetBalance() >= userDouble){
                        bankVect[i].Withdraw(userDouble);
                        tooMuch = false;
                    } else {
                        cout << "Insufficient funds." << endl;
                    }
                    break;
                }
            }
            if(notFound){
            cout << "Account Number not found. Try Again." << endl;
            }
        }
    }
}
int main()
{
    vector<BankAccount> accounts;
    //While + Switch combo that will return 0 if user enters 0 which will cause program to exit while loop
    while (true) {
        promptUser();
        userInt = getIntInput();
        switch (userInt) {
            case 1:
                createAccount(accounts);
                break;
            case 2:
                listAccounts(accounts);
                break;
            case 3:
                changeAccountName(accounts);
                break;
            case 4:
                depositAmount(accounts);
                break;
            case 5:
                withdrawAmount(accounts);
                break;
            case 0:
                cout << "Goodbye!" << endl;
                return 0;
        }
    }
    
    return 0;
}