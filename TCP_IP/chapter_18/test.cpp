#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int addMinimum(string word) {
    if (word.size() == 1)   return 2;
    int res = 0;
    if (word[0] == 'b') res++;
    else if (word[0] == 'c') res += 2;
        
    for (int i = 1; i < word.size(); i++){
         if ((word[i] == 'b' && word[i-1] == 'a') || (word[i] == 'c' && word[i-1] == 'b') || (word[i] == 'a' && word[i-1] == 'c'))
            continue;

        if (word[i] == 'a'){
            if (word[i-1] == 'a') res += 2;
            else if (word[i-1] = 'b') res += 1;

        }else if (word[i] == 'b'){
            if (word[i-1] == 'b') res += 2;
            else if (word[i-1] == 'c')  res += 1;

        }else if (word[i] == 'c'){
            if (word[i-1] == 'c')   res += 2;
            else if (word[i-1] == 'a')  res += 1;
        }
        // cout << i << " " << res << endl;
    }
        
    if (word.back() == 'a')
        res += 2;
    else   if (word.back() == 'b')
        res++;
        
    return res;
}

int main(){
    string str = "ac";
    cout << addMinimum(str) << endl;
    return 0;
}