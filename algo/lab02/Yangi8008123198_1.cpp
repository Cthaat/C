#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long long binom(int n, int k) {
    // 使用一维数组进行滚动更新
    vector<long long> dp(k + 1, 0);
    dp[0] = 1;  // C(n, 0) = 1
    for (int i = 1; i <= n; i++) {
        // j从min(i, k)开始递减，确保更新时用到的是上一行的值
        for (int j = min(i, k); j > 0; j--) {
            dp[j] = dp[j] + dp[j - 1];
        }
    }
    return dp[k];
}

int main() {
    int n, k;
    cout << "请输入 n 和 k: ";
    cin >> n >> k;
    cout << "C(" << n << ", " << k << ") = " << binom(n, k) << endl;
    return 0;
}
