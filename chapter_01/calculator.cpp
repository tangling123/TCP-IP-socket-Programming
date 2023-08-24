#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

map<int, vector<int>> mp;
 
int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0, idx = 1; i < n; i++){
        int x;
        cin >> x;
        mp[x].push_back(idx++);
    }

    int g, k = 1;
    cin >> g;
    for (int i = 0; i < g; i++){
        int fi, ai, nai, pai, paai, paari;
        cin >> fi >> ai >> nai >> pai >> paai >> paari;

        vector<int> f(fi, 0);
        for (int j = 0; j < fi; j++){
            if (mp.find(nai) != mp.end() && k <= n) f[j] = k++;
        }
        for (int j = 0; j < fi; j++){
            cout << f[j];
            j == fi-1 ? cout << endl : cout << " ";
        }
    }

    return 0;
}