#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

stack<int> nums;
stack<char> oper;
unordered_map<char, int> mp;

void calculate(stack<int> &nums, stack<char> &ops) {
    if(nums.size() < 2 || ops.empty())
        return;

    int y = nums.top(); nums.pop();
    int x = nums.top(); nums.pop();
    char oper = ops.top(); ops.pop();

    if (oper == '+')
        nums.push(x + y);
    else if (oper == '-')
        nums.push(x - y);
    else if (oper == '*')
        nums.push(x * y);
    else if (oper == '/')
        nums.push(x / y);
}

void change(string str){
    for (int i = 0, j = i; j < str.size(); j++){
        while (j < str.size() && str[j] >= '0' && str[j] <= '9')
            j++;
        nums.push(stoi(str.substr(i, j-i)));
        cout << str.substr(i, j-i) << endl;
        if (j < str.size()){
            while (oper.size() && mp[oper.top()] >= mp[str[j]]){
                calculate(nums, oper);
            }
            oper.push(str[j]);
        }
        i = j+1;
    }
    while (oper.size())
        calculate(nums, oper);
}

int main(){
    mp['+'] = mp['-'] = 1;
    mp['*'] = mp['/'] = 2;

    string str;
    getline(cin, str);

    change(str);
    // calculate();
    cout << "res : " << nums.top() << endl;

    return 0;
}