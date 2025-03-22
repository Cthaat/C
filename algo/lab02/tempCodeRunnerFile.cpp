#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // 用于 INT_MAX

using namespace std;

int coinChange(vector<int>& coins, int amount) {
    // 创建动态规划数组
    vector<int> dp(amount + 1, amount + 1); // 初始化为 amount + 1，表示无法凑成

    // 初始化 dp[0]
    dp[0] = 0;

    // 遍历所有金额
    for (int i = 1; i <= amount; ++i) {
        // 遍历所有硬币
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    // 返回结果
    return dp[amount] > amount ? -1 : dp[amount];
}

int main() {
    // 示例 1
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    int result1 = coinChange(coins1, amount1);
    cout << "示例 1：coins=[1, 2, 5], amount=11, 输出=" << result1 << endl;

    // 示例 2
    vector<int> coins2 = {2};
    int amount2 = 3;
    int result2 = coinChange(coins2, amount2);
    cout << "示例 2：coins=[2], amount=3, 输出=" << result2 << endl;

    return 0;
}