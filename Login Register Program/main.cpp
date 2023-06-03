#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unistd.h>

using namespace std;

string takeUserMenuInput() {
        string userChoice;
        cout << "Welcome in our code! \n [1]: LOGIN   [2]: SIGN UP" << endl;
        do{
            getline(cin, userChoice);
            if (userChoice == "1" || userChoice == "2") {
                cout << "Right on! Processing option..." << endl;
                break;
            } else {
                cout << "Invalid input! Please choose between inputting 1 and 2 into the console! \n Welcome in our code! \n [1]: LOGIN   [2]: SIGN UP" << endl;
            }
        }while(userChoice != "1" && userChoice != "2");

    if(userChoice == "2") {
        return "SIGNUP";
    } else {
        return "LOGIN";
    }

}

bool verifyInput(string userInput){
  for(char letter : userInput){
    if(isspace(letter)){
      return false;
    }
  }
  if(userInput.empty()){
        return false;
    }
  return true;
}

void returnUsernamesList(list<string>& usernamesList){
    ifstream usernamesFile("usernamesList.txt");

    string usernameInput;
    if (usernamesFile.is_open()){
        string line;
        while(getline(usernamesFile, line)) {
            usernamesList.push_back(line);
        }
        usernamesFile.close();
    }else{
        cout << "Error in opening the file!" << endl;
    }
}

void returnPasswordsList(list<string>& passwordsList){
    ifstream passwordsFile("passwordsList.txt");

    if (passwordsFile.is_open()){
        string line;
        while (getline(passwordsFile, line)) {
            passwordsList.push_back(line);
        }
        passwordsFile.close();
    }else{
        cout << "Error in opening the file!" << endl;
    }
}

bool checkListForElement(list<string> listOfElements, string elementToSearch){
    for(string tempStr : listOfElements){
        if(tempStr == elementToSearch){
            return true;
        }
    }
    return false;
}

bool verifyLoginData(string username, string password){
  list<string> usernamesList;
  list<string> passwordsList;

  returnUsernamesList(usernamesList);
  returnPasswordsList(passwordsList);

  int usernameIndex = 0;
  int usernameExists = -1;

  int passwordExists = -1;
  int passwordIndex = 0;

  for(string user : usernamesList){
    usernameIndex++;
    if(user == username){
      usernameExists = 0;
      break;
    }
  }
  for(string pass : passwordsList){
    passwordIndex++;
    if(pass == password){
      passwordExists = 0;
      break;
    }
  }

  if(usernameIndex == passwordIndex && usernameExists == passwordExists && usernameExists == 0){
    return true;
  }else{
    return false;
  }
}

bool verifySignupData(string username, string password) {
    list<string> usernamesList;
    list<string> passwordsList;

    returnUsernamesList(usernamesList);
    returnPasswordsList(passwordsList);

    if(verifyInput(username) && verifyInput(password)){

        for (string user : usernamesList) {
            if (user == username) {
                return false;
            }
        }

        for(string pass : passwordsList){
            if(pass == password){
                return false;
            }
        }
        if(verifyInput(username) && verifyInput(password)){
            return true;
        }
    }
    return false;
}

void loginPage(){
    string usernameInput;
    string passwordInput;
    cout << "Welcome to the login page! \n\n Please input your username and password: " << endl;
    cout << "Username: ";
    getline(cin, usernameInput);
    cout << "Password: ";
    getline(cin, passwordInput);

    if(verifyInput(usernameInput) && verifyInput(passwordInput) && verifyLoginData(usernameInput, passwordInput)){
        cout << "Welcome, " << usernameInput << "! Loading the home page..." << endl;
    }else{
      cout << "Incorrect login data/improper input! Please try again!" << endl;
      loginPage();
    }
}

void registerPage() {
    string usernameInput;
    string passwordInput;
    string confirmation;

    ofstream usernamesWriter("usernamesList.txt", ofstream::app);
    ofstream passwordsWriter("passwordsList.txt", ofstream::app);

    do {
        cout << "Welcome to the register page! \n\n Please input your username and password: " << endl;
        cout << "Username: ";
        getline(cin, usernameInput);
        cout << "Password: ";
        getline(cin, passwordInput);

        if (verifySignupData(usernameInput, passwordInput)) {
            cout << "Confirm your password: ";
            getline(cin, confirmation);

            if (confirmation == passwordInput) {
                if (usernamesWriter.is_open()) {
                    usernamesWriter << usernameInput << endl;
                }
                if (passwordsWriter.is_open()) {
                    passwordsWriter << passwordInput << endl;
                }

                usernamesWriter.close();
                passwordsWriter.close();

                cout << "Account has been successfully registered! Sending you to the login page now..." << endl;
                sleep(3);
                loginPage();
            }
        } else {
            cout << "Improper sign up data! Please don't use spaces or try a different username/password!" << endl;
        }
    } while (confirmation != passwordInput);
}

int main() {
    cout << "Hello world!" << endl;
    string input = takeUserMenuInput();
    if(input == "LOGIN"){
        loginPage();
    }else{
        registerPage();
    }
    return 0;
}