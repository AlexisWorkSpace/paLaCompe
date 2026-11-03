#include <bits/stdc++.h>
 
struct Mountain {
    int h; 
    int left; 
    int cover; 
};
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int n;
    std::cin >> n;
 
    std::vector<int> h(n + 1);
    for (int i = 0; i < n; i++) std::cin >> h[i];
    h[n] = std::numeric_limits<int>::max(); 
 
    std::stack<Mountain> st;
    int ans = 0;
 
    for (int i = 0; i <= n; i++) {
        int cur = 0;
 
        while (!st.empty() && st.top().h < h[i]) {
            Mountain e = st.top();
            st.pop();
            int d = 1 + std::max(e.left, cur);
            ans = std::max(ans, d);
            cur = std::max({cur, d, e.cover});
        }
 
        int left = cur, cover = cur;
 
        if (!st.empty() && st.top().h == h[i]) {
            Mountain e = st.top();
            st.pop();
            int d = 1 + std::max(e.left, cur);
            ans = std::max(ans, d);
            cover = std::max({cur, d, e.cover});
        }
 
        if (i < n) st.push({h[i], left, cover});
    }
 
    std::cout << ans << "\n";
    return 0;
