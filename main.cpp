/* Banking System Designed by Arnold Arinda */ 

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct bank_users {
    string name;
    string password;
    float account_balance;

    friend istream & operator >> (istream & is, bank_users & usr) {
        // skip whitespace
        is >> ws;
        getline(is, usr.name);
        is >> usr.password;
        is >> usr.account_balance;
        return is;
    }
};

// Initialise Prototype Functions for Deposit, Registration of new user and
// Password reset to use later
void admin_login();
void normal_login();

void deposit();

// register is a reserved word in C++, which is why we use the function name
// "registr"
void registr();
void admin_password_reset();
void check_balance();

// The functions declared before this point are just Prototypes, and order
// doesn't matter.

int main() {
    int option;

    // Program's Main Page
    cout << "*****\tWELCOME TO REPLCRAZY E-CASH SERVICES\t*****" << endl;
    cout << "1. Normal User Login" << endl;
    cout << "2. Administrator Login" << endl;
    cout << endl;
    cout << "Choose an option to proceed: ";
    cin >> option;
    cout << endl;

    switch (option) {
    case 1:
        normal_login();
        break;
    case 2:
        admin_login();
        break;
        // Return the user to the Main Page incase of a false selection.
    default:
        cout << "Please select one of the two options indicated and try again!" <<
            endl;
        cout << endl;
        main();
    }
}

void
registr() {
    float initial_balance;
    string UserName, UserPass;

    cout << "Enter Client username: ";
    cin >> UserName;
    cout << endl;
    cout << "\nEnter the password: ";
    cin >> UserPass;
    cout << "Opening Credit: " << endl;
    cin >> initial_balance;

    fstream registration;
    registration.open("UsersDB.txt", ios::app);
    if (registration.is_open()) {
        registration << UserName << "\n" << UserPass << "\n" << initial_balance <<
            "\n" << endl;
        registration.close();
    }
    cout << "\nRegistration Successful! \n";
    main();
}

void
deposit() {
    auto file = ifstream("UsersDB.txt");

    vector < bank_users > v;

    for (bank_users info; file >> info;) // keep reading until we run out
    {
        // we only get here if the read succeeded
        v.push_back(info);
    }

    string usrnme;
    double deposit_amt;

    cout << "Enter the Client Username: ";

    cin.ignore();
    getline(cin, usrnme);

    for (auto & usr: v) {
        if (usrnme == usr.name) {
            cout << "Enter deposit amount: ";
            cin >> deposit_amt;
            usr.account_balance = usr.account_balance + deposit_amt;
            cout << "New Balance is: " << usr.account_balance << endl;
        }
    }
}

// admin Login
void
admin_login() {
    string admName, admPass, an, ap;
    //int count;

    cout << "Welcome to the Registration and Deposit page\n";
    cout << "Enter administrator username and password.\n";
    cout << "Enter username: ";
    cin >> admName;
    cout << "Enter password: ";
    cin >> admPass;
    cout << endl;

    fstream input("admin.txt");
    while (input >> an >> ap) {
        if (an == admName && ap == admPass) {
            input.close();
            int option;
            cout << "\nWelcome " << admName << endl;
            cout << "1. Deposit money for Client \n" <<
                "2. Register new Client \n" <<
                "3. Reset your Password \n";
            cout << "Enter option to Proceed: ";
            cin >> option;
            if (option == 1) {
                deposit();
            } else if (option == 2) {
                registr();
            } else if (option == 3) {
                admin_password_reset();
            } else {
                cout << "Invalid option, please try again!" << endl;
                main();
            }
        } else {
            cout << "Wrong Credentials, try again! " << endl;
            main();
        }
    }
}

void
normal_login() {
    cout << "Welcome to the Normal Login! " << endl;

    fstream file;
    file.open("UsersDB.txt");

    vector < bank_users > v;

    for (bank_users info; file >> info;) // keep reading until we run out
    {
        // we only get here if the read succeeded
        v.push_back(info);
    }

    string usrnme;
    string usrpass;

    cout << "Please enter your username..." << endl;
    cin.ignore();
    getline(cin, usrnme);

    for (auto & usr: v) {
        if (usrnme == usr.name) {
            cout << "Please Enter your Password: ";
            cin >> usrpass;

            if (usrpass == usr.password) {
                int option;
                cout << "\nWelcome " << usr.name << endl;
                cout << "1. Withdraw \n" <<
                    "2. Check Balance \n" <<
                    "3. Reset your Password \n";
                cout << "Enter option to Proceed: ";
                cin >> option;
                if (option == 1) {
                    double withdraw_amt;
                    cout << "Please enter the amount you wish to Withdraw: ";
                    cin >> withdraw_amt;

                    usr.account_balance = usr.account_balance - withdraw_amt;
                    cout << "Your balance is, " << usr.account_balance << endl;
                } else if (option == 2) {
                    cout << "You account balance is: " << usr.account_balance << endl;
                } else if (option == 3) {
                    // password_reset();
                    string new_pass;
                    cout << "Please enter the new password: ";
                    cin >> new_pass;
                    usr.password = new_pass;
                    cout << new_pass << endl;
                    cout << "Password Reset Successful!" << endl;
                } else {
                    cout << "Invalid option, please try again!" << endl;
                    main();
                }
            } else {
                cout << "Incorrect Password. Please try again! " << endl;
            }
        }
    }
}

void
admin_password_reset() {
    ofstream changes;
    changes.open("admin.txt");

    if (changes.is_open()) {
        string admName, new_pass;
        cout << "Please enter the admin username: ";
        cin >> admName;
        cout << "Please enter the new password: ";
        cin >> new_pass;
        changes << admName << "\n" << new_pass;
        changes.close();
        main();
    }
}
