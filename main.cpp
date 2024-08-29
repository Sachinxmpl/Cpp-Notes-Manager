#include <iostream>
#include <fstream>   // For file operations
#include <sstream>   // For stringstream
#include <cstdlib>   // For cleaning screen
#include <windows.h> // For sleep
#include <limits>

using namespace std;
bool validatePassword(const string &);
bool validateUserName(const string &);

// User Class
class user
{
private:
    string name, userName, password;

public:
    user(string Name = "", string UserName = "", string Password = "")
    {
        name = Name;
        userName = UserName;
        password = Password;
    }

    // To Register User
    int registerUser()
    {
        bool retry = true;
        while (retry)
        {
            system("cls"); // Clears Screen

            cout << "Please Enter Your Details " << endl;

            cout << "Enter Name: ";
            cin >> ws;          // Clears leading whitespace
            getline(cin, name); // Reads full name including spaces

            cout << "Enter UserName: ";
            cin >> userName;

            cout << "Enter Password: ";
            cin >> ws; // Clears leading whitespace
            getline(cin, password);

            ofstream credentialsFile("users.dat", ios::binary | ios::app);

            if (credentialsFile.is_open()) // To check if file is open or not
            {
                bool registrationSuccessful = false;
                if (validatePassword(password) && !validateUserName(userName))
                {
                    credentialsFile << name << "|" << userName << "|" << password << endl;
                    registrationSuccessful = true;
                }
                else
                {
                    cout <<  endl <<  "Registration Error!!" << endl;
                    if (validateUserName(userName))
                    {
                        cout << "User With This Username Already Exists." << endl;
                    }
                    if (!validatePassword(password))
                    {
                        cout << "Password Must Contain A Uppercase Letter, A Lowercase Letter And A Number! " << endl;
                    }

                    char choice;
                    cout << endl << "Try again? (y/n): ";
                    cin >> choice;
                    if (choice != 'y' && choice != 'Y')
                    {
                        retry = false;
                    }
                    system("cls");
                    continue;
                }
                credentialsFile.close(); // Closes the opened file
                cout << endl << "User Registration Successful! " << endl;
                Sleep(2000);
                system("cls");
                return 0;
            }
            else
            {
                cout << "Error opening file!" << endl;
            }
        }
    }

    int loginUser(string &name)
    {
        bool retry = true;

        while (retry)
        {
            system("cls");
            cout << "Please Enter Your Details " << endl;
            string storedName, storedUserName, storedPassword;
            string userName, password;

            cout << "Enter Your Username: ";
            cin >> userName;
            cout << "Enter Your Password: ";
            cin >> password;

            ifstream credentialsFile("users.dat", ios::binary);
            if (credentialsFile.is_open())
            {
                string line;
                bool loginSuccessful = false;

                while (getline(credentialsFile, line))
                {
                    stringstream ss(line);

                    getline(ss, storedName, '|');
                    getline(ss, storedUserName, '|');
                    getline(ss, storedPassword, '|');

                    name = storedName;

                    if (userName == storedUserName && password == storedPassword)
                    {
                        loginSuccessful = true;
                        break; // Exit the inner loop
                    }
                }

                credentialsFile.close();

                if (loginSuccessful)
                {
                    cout << endl << "Login Successful! " << endl;
                    Sleep(2000);
                    return 0;
                }
                else
                {
                    cout << endl << "Login failed: Invalid username or password." << endl;
                    char choice;
                    cout << endl << "Try again? (y/n): ";
                    cin >> choice;
                    if (choice != 'y' && choice != 'Y')
                    {
                        retry = false;
                    }
                    system("cls");
                }
            }
            else
            {
                cout << "Error opening file!" << endl;
                return -1; // Exit with an error code
            }
        }
    }
    int postLogin(string name)
    {
        system("cls");
        cout << "Welcome " << name << endl;
    }
};

bool validatePassword(const string &password)
{
    if (password.length() < 8)
    {
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : password)
    {
        if (isdigit(c))
            hasDigit = true;
        else if (isupper(c))
            hasUpper = true;
        else if (islower(c))
            hasLower = true;
    }
    return hasUpper && hasLower && hasDigit;
}

bool validateUserName(const string &userName)
{
    ifstream credentialsFile("users.dat", ios::binary);
    if (credentialsFile.is_open())
    {
        string line;
        while (getline(credentialsFile, line))
        {
            stringstream ss(line);
            string storedName, storedUserName, storedPassword;
            getline(ss, storedName, '|');
            getline(ss, storedUserName, '|');
            getline(ss, storedPassword, '|');

            if (userName == storedUserName)
            {
                credentialsFile.close();
                return true;
            }
        }
        credentialsFile.close();
    }
    return false;
}

int main()
{
    while (1)
    {
        cout << "Welcome To Notes Manager" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        string choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1")
        {
            user u1;
            u1.registerUser();
        }
        else if (choice == "2")
        {
            string name;
            user u1;
            int loginSuccess = u1.loginUser(name);
            if (!loginSuccess)
            {
                u1.postLogin(name);
            }
        }
        else if (choice == "3")
        {
            break;
        }
        else
        {
            cout << endl
                 << "Invalid Choice " << endl;
            cout << "Plese Enter A Valid Choice: " << endl;
            Sleep(1000);
            system("cls");
            continue;
        }
    }
    return 0;
}