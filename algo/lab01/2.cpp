#include <iostream>

using namespace std;

const int MAX_N = 1024; // 允许最大棋盘 1024x1024 (2^10)
int board[MAX_N][MAX_N]; // 棋盘
int tile = 0; // 记录 L 形骨牌编号

// 使用分治法进行棋盘覆盖
void cover(int tr, int tc, int dr, int dc, int size) {
    if (size == 1) return; // 递归终止条件

    int t = ++tile; // 当前 L 形骨牌编号
    int s = size / 2; // 当前棋盘划分的大小

    // 处理 4 个小棋盘，寻找特殊格子所在区域
    if (dr < tr + s && dc < tc + s) {
        // 特殊格子在左上角
        cover(tr, tc, dr, dc, s);
    } else {
        // 在中心放置 L 形骨牌
        board[tr + s - 1][tc + s - 1] = t;
        cover(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    if (dr < tr + s && dc >= tc + s) {
        // 特殊格子在右上角
        cover(tr, tc + s, dr, dc, s);
    } else {
        board[tr + s - 1][tc + s] = t;
        cover(tr, tc + s, tr + s - 1, tc + s, s);
    }

    if (dr >= tr + s && dc < tc + s) {
        // 特殊格子在左下角
        cover(tr + s, tc, dr, dc, s);
    } else {
        board[tr + s][tc + s - 1] = t;
        cover(tr + s, tc, tr + s, tc + s - 1, s);
    }

    if (dr >= tr + s && dc >= tc + s) {
        // 特殊格子在右下角
        cover(tr + s, tc + s, dr, dc, s);
    } else {
        board[tr + s][tc + s] = t;
        cover(tr + s, tc + s, tr + s, tc + s, s);
    }
}

// 打印棋盘
void printBoard(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int k, dr, dc;
    cout << "输入 k";
    cin >> k;
    int n = (1 << k); // 计算棋盘大小 2^k
    cout << "输入特殊方块坐标";
    cin >> dr >> dc;

    // 初始化棋盘
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    // 开始棋盘覆盖
    cover(0, 0, dr, dc, n);

    // 输出最终结果
    cout << "棋盘覆盖结果：" << endl;
    printBoard(n);

    return 0;
}
