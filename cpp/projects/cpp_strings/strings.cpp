#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

int main() {
    char first_name[20];
    char last_name[20];
    char full_name[50];
    char temp[50];


    cout << "What is your full name? "; 
    cin >> first_name >> last_name;

    // concatenate first_name and last_name inside full_name
    strcpy(full_name, first_name);
    strcat(full_name, " ");
    strcat(full_name, last_name);
    
    cout << endl << "Hello, " << full_name << endl;
    cout << "Your name is " << strlen(first_name) + strlen(last_name) << " characters long" << endl;

    


    return 0;
}