#include <string>
#include <iostream>

using namespace std;

int main()
{
    string first_name = "Jahed";
    string last_name {"Hossain"};
    string full_name = first_name + " " + last_name;

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string subset {alphabet, 0, 4};

    cout << "Hello, " << full_name << endl; 
    cout << "Character at index 0: " << full_name.at(0) << endl; 
    cout << "Jahed < jahed: " << (first_name < "jahed") << endl; 
    cout << "full_name.find('x'): " << full_name.find('h') << endl; 
    cout << "Alphabet? , " << subset << endl; 
    
    return 0;
}