#include <bits/stdc++.h>   

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
  
    std::vector<int> p(n + 1, 0), hijos(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        std::cin >> p[i];        
        hijos[p[i]]++;      
    }

    if (n == 1) {
        std::cout << 0 << "\n";
        return 0;
    }


    std::vector<std::vector<int>> pend(n + 1);
    std::vector<int> e(n + 1, 0);

    for (int v = n; v >= 1; v--) {
        if (hijos[v] == 0)
            pend[v].push_back(v);
        else if (v != 1 && pend[v].size() >= 2) {
            int hoja = pend[v].back();  
            e[hoja] = v;                
            pend[v].pop_back();         
        }
        if (v == 1) break;
        int padre = p[v];
        if (pend[padre].size() < pend[v].size()) {
            swap(pend[padre], pend[v]);
        }
        for (int x : pend[v]) {
            pend[padre].push_back(x);
        }
        pend[v].clear();
        pend[v].shrink_to_fit();
    }

    if (pend[1].size() != 1) {
        std::cout << "*\n";
        return 0;
    }
    e[pend[1][0]] = 1;
    for (int v = 1; v <= n; v++)
        std::cout << e[v] << (v == n ? "\n" : " ");
  
    return 0;
}
