#include <iostream>
#include <cstring>
using namespace std;

int main(){
    cout << "What year was your house build?\n";
    int year;
    cin >> year;

    cout << "What is its street address?\n";
    char address[50];
    cin.get();
    cin.getline(address, 50);

    cout << "Your house build in " << year << " and its address : " << address << endl;

    return 0;
}