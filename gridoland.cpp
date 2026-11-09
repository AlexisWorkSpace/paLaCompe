#include <bits/stdc++.h>

const long long INF = 4000000000000000000LL; 

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, P;
    long long k;
    std::cin >> N >> M >> P >> k;

    std::vector<std::vector<long long>> c(N, std::vector<long long>(M));
    std::vector<std::vector<long long>> r(N, std::vector<long long>(M));

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            std:: cin >> c[i][j];

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            std:: cin >> r[i][j];

    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> cables;

    for(int i = 0; i < P; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        cables.push_back( {
            { x1, y1 },
            { x2, y2 }
        });
    }

    std::vector<std::vector<bool>> cableDerecha(N, std::vector<bool>(M, false));
    std::vector<std::vector<bool>> cableAbajo(N, std::vector<bool>(M, false));
    for (auto [a, b] : cables) {
        int i1 = a.first - 1, j1 = a.second - 1;
        int i2 = b.first - 1, j2 = b.second - 1;
        if (i1 > i2 || j1 > j2) { std::swap(i1, i2); std::swap(j1, j2); }
        if (i1 == i2) cableDerecha[i1][j1] = true;
        else          cableAbajo[i1][j1] = true;
    }

    int numEsquinas = (N + 1) * (M + 1);
    auto esquina = [&](int f, int col) { return f * (M + 1) + col; };
    auto bloque  = [&](int i, int j) { return numEsquinas + i * M + j; };

    std::vector<long long> dist(numEsquinas + N * M);
    std::vector<long long> pend(numEsquinas + N * M); 

    auto corteMinimo = [&](long long t) -> std::pair<long long, long long> {
        std::fill(dist.begin(), dist.end(), INF);
        std::priority_queue<std::pair<long long, int>,
                            std::vector<std::pair<long long, int>>,
                            std::greater<std::pair<long long, int>>> pq;

        auto relajar = [&](int v, long long d, long long p) {
            if (d < dist[v]) { dist[v] = d; pend[v] = p; pq.push({d, v}); }
        };

        for (int col = 1; col <= M; ++col) relajar(esquina(0, col), 0, 0);
        for (int f = 1; f <= N - 1; ++f)   relajar(esquina(f, M), 0, 0);

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;

            if (u >= numEsquinas) {
                int i = (u - numEsquinas) / M, j = (u - numEsquinas) % M;
                relajar(esquina(i, j),         d, pend[u]);
                relajar(esquina(i, j + 1),     d, pend[u]);
                relajar(esquina(i + 1, j),     d, pend[u]);
                relajar(esquina(i + 1, j + 1), d, pend[u]);
                continue;
            }

            int f = u / (M + 1), col = u % (M + 1);

            if ((col == 0 && f >= 1) || (f == N && col <= M - 1)) return {d, pend[u]};

            for (int i = f - 1; i <= f; ++i)
                for (int j = col - 1; j <= col; ++j)
                    if (i >= 0 && i < N && j >= 0 && j < M)
                        relajar(bloque(i, j), d + c[i][j] + t * r[i][j], pend[u] + r[i][j]);

            bool colInterior = (col >= 1 && col <= M - 1);
            bool filInterior = (f >= 1 && f <= N - 1);
            if (colInterior && f < N && !cableDerecha[f][col - 1])      relajar(esquina(f + 1, col), d, pend[u]); // abajo
            if (colInterior && f > 0 && !cableDerecha[f - 1][col - 1])  relajar(esquina(f - 1, col), d, pend[u]); // arriba
            if (filInterior && col < M && !cableAbajo[f - 1][col])      relajar(esquina(f, col + 1), d, pend[u]); // derecha
            if (filInterior && col > 0 && !cableAbajo[f - 1][col - 1])  relajar(esquina(f, col - 1), d, pend[u]); // izquierda
        }
        return {INF, 0};
    };

    long long lo = 0, hi = k, mejor = 0;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        auto [valor, pendiente] = corteMinimo(mid);
        mejor = std::max(mejor, valor);
        if (pendiente > 0)      lo = mid + 1;
        else if (pendiente < 0) hi = mid - 1;
        else break;
    }

    std::cout << mejor << "\n";
    return 0;
}
