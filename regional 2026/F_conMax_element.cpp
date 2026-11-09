#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> trabajos;
    for(int i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        if(trabajos.empty() || trabajos.back() != a)
            trabajos.push_back(a);
    }

    int L = trabajos.size();
    int cambios = L - 1;

    std::vector<int> ahorro(N + 1, 0);
    for(int i = 0; i < L; ++i)
        if(i > 0 && i < L - 1) 
            ahorro[trabajos[i]] += (trabajos[i - 1] == trabajos[i + 1]) ? 2 : 1;
        else if(L > 1)
            ahorro[trabajos[i]] += 1;

    std::cout << cambios - *std::max_element(ahorro.begin(), ahorro.end()) << "\n";

    return 0;
}

