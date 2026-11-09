#include <bits/stdc++.h>

int main() {
    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for(int i = 0; i < N; ++i)
        std::cin >> A[i];

    int mejor = N;  
    for(int x = 1; x <= N; ++x) {
        int cambios = 0;
        int anterior = -1;   

        for(int i = 0; i < N; ++i) {
            if(A[i] == x) continue;   
            if(anterior != -1 && A[i] != anterior)
                ++cambios;
            anterior = A[i];
        }
      
        if(cambios < mejor)
            mejor = cambios;
    }
  
    std::cout << mejor << "\n";
    return 0;
}
