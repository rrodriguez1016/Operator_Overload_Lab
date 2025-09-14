#include<iostream>
#include<vector>
#include <string>
#include<limits>
using namespace std;

double userDouble;
int userInt;
string userString;
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
void promptUser(){
    cout << "What would you like to do?" << endl;
    cout << "\t 1. Create account" << endl;
    cout << "\t 2. List all accounts" << endl;
    cout << "\t 3. Change account holder name" << endl;
    cout << "\t 4. Deposit" << endl;
    cout << "\t 5. Withdraw" << endl;
    cout << "\t 0. Quit" << endl;
}
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
void createAccount(vector<BankAccount>& bankVect){
    BankAccount currAccount;
    cout << "Enter bank account number." << endl;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, userString);
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
    if (bankVect.size() == 0){
        cout << "No accounts available." << endl;
    } else {
        while(notFound){
            cout << "Enter Account Number you would like to change name of." << endl;
            userInt = getIntInput();
            for (int i = 0; i < bankVect.size(); ++i){
                currAcc = bankVect.at(i);
                if(currAcc.GetAccNum() == to_string(userInt)){
                    notFound = false;
                    cout << "Enter new name" << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, userString);
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
        while(notFound || tooMuch){
            cout << "Enter Account Number you would like to withdraw money from." << endl;
            userInt = getIntInput();
            for (int i = 0; i < bankVect.size(); ++i){
                currAcc = bankVect.at(i);
                if(currAcc.GetAccNum() == to_string(userInt)){
                    notFound = false;
                    cout << "Enter withdrawal amount" << endl;
                    userDouble = getdoubleInput();
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
    BankAccount currAccount;
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